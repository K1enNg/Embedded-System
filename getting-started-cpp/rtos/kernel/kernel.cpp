#include "kernel.hpp"
#include "api/interface.hpp"
#include <chrono>
#include <iostream>

using namespace std::chrono;

RTOS::RTOS(std::unique_ptr<IScheduler> sch)
    : scheduler(std::move(sch)), default_queue(64) {}

RTOS::~RTOS() { stop(); }

int RTOS::create_task(const std::string& name, TaskFunc func, int priority) {
    int id = next_task_id++;
    auto t = std::make_shared<Task>(id, name, priority, std::move(func));
    tasks[id] = t;

    // start thread - it waits until scheduler wakes it
    t->thread = std::thread([this, t]() {
        TaskAPI api(*t, *this);
        // initial wait for first scheduling
        {
            std::unique_lock lk(t->mtx);
            t->cv.wait(lk, [t]() { return t->should_run || t->request_stop; });
        }
        if (!t->request_stop) {
            t->state = TaskState::Running;
            t->last_exec_ms = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
            t->func(api);
        }
        t->state = TaskState::Terminated;
        // wake kernel to handle termination
        kernel_cv.notify_one();
    });

    return id;
}

void RTOS::start() {
    running = true;
    start_ms = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
    sched_thread = std::thread(&RTOS::scheduler_loop, this);
}

void RTOS::stop() {
    if (!running) return;
    running = false;

    // wake all tasks to exit
    for (auto &p : tasks) {
        auto &t = p.second;
        {
            std::lock_guard lk(t->mtx);
            t->request_stop = true;
            t->should_run = true;
        }
        t->cv.notify_one();
    }
    kernel_cv.notify_all();

    if (sched_thread.joinable()) sched_thread.join();
    for (auto &p : tasks) {
        if (p.second->thread.joinable())
            p.second->thread.join();
    }
}

void RTOS::do_yield(Task& t) {
    {
        std::lock_guard lk(t.mtx);
        t.should_run = false;
        if (t.state != TaskState::Terminated) t.state = TaskState::Ready;
        t.last_exec_ms = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
    }
    kernel_cv.notify_one();
    // block until scheduler wakes it
    std::unique_lock lk(t.mtx);
    t.cv.wait(lk, [&t](){ return t.should_run || t.request_stop; });
    if (t.request_stop) return;
    t.state = TaskState::Running;
}

void RTOS::do_sleep(Task& t, int ms) {
    {
        std::lock_guard lk(t.mtx);
        t.should_run = false;
        t.state = TaskState::Sleeping;
        t.wake_time = steady_clock::now() + std::chrono::milliseconds(ms);
        t.last_exec_ms = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
    }
    kernel_cv.notify_one();
    // block until scheduler wakes it
    std::unique_lock lk(t.mtx);
    t.cv.wait(lk, [&t](){ return t.should_run || t.request_stop; });
    if (t.request_stop) return;
    t.state = TaskState::Running;
}

void RTOS::set_timer(const std::string& name, int ms_from_now) {
    timers.set_timer(name, steady_clock::now() + std::chrono::milliseconds(ms_from_now));
}

void RTOS::remove_timer(const std::string& name) {
    timers.remove_timer(name);
}

long long RTOS::system_time_ms() {
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count() - start_ms;
}

void RTOS::build_snapshot(KernelSnapshot& snap) {
    snap.system_ms = system_time_ms();
    snap.tasks.clear();
    for (auto &p : tasks) {
        TaskSnapshot ts;
        ts.id = p.second->id;
        ts.name = p.second->name;
        ts.state = p.second->state;
        ts.priority = p.second->priority;
        ts.last_exec_ms = p.second->last_exec_ms.load();
        snap.tasks.push_back(std::move(ts));
    }

    // single default queue snapshot
    QueueSnapshot qs;
    qs.name = "default";
    auto qcont = default_queue.snapshot();
    for (auto &m : qcont) qs.contents.push_back(m);
    snap.queues.clear();
    snap.queues.push_back(std::move(qs));

    snap.timers = timers.snapshot();
}

void RTOS::scheduler_loop() {
    using namespace std::chrono_literals;
    while (running) {
        // wake sleeping tasks whose wake_time has passed
        auto now = steady_clock::now();
        for (auto &p : tasks) {
            auto &t = p.second;
            if (t->state == TaskState::Sleeping && t->wake_time <= now) {
                std::lock_guard lk(t->mtx);
                t->state = TaskState::Ready;
            }
        }

        // handle expired timers (simple callback simulation: just print)
        auto expired = timers.collect_expired();
        for (auto &name : expired) {
            // for simulation, we just print; real kernel might notify tasks/queues
            std::cout << "[TIMER] " << name << " expired\n";
        }

        // pick next task
        int next = scheduler->pick_next(tasks, last_run_task);
        if (next == -1) {
            // no ready task: wait for event
            std::unique_lock lk(kernel_mtx);
            kernel_cv.wait_for(lk, 10ms);
            continue;
        }

        auto t = tasks[next];
        if (t->state == TaskState::Terminated) { last_run_task = next; continue; }

        // schedule: wake the task
        {
            std::lock_guard lk(t->mtx);
            t->should_run = true;
            t->state = TaskState::Running;
            t->last_exec_ms = system_time_ms();
        }
        t->cv.notify_one();

        // wait until task yields/sleeps/terminates or timeout (time slice)
        std::unique_lock lk(kernel_mtx);
        kernel_cv.wait_for(lk, 50ms); // slice

        // if still running, mark ready (cooperative)
        if (t->state == TaskState::Running) {
            std::lock_guard lk2(t->mtx);
            t->should_run = false;
            if (t->state != TaskState::Terminated)
                t->state = TaskState::Ready;
        }

        last_run_task = next;
    }
}
