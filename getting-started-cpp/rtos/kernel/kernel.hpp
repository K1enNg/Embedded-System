#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include "task.hpp"
#include "scheduler.hpp"
#include "timer.hpp"
#include "queue.hpp"

// forward TaskAPI
#include "api/interface.hpp"

struct KernelSnapshot;

class RTOS {
    std::map<int, std::shared_ptr<Task>> tasks;
    std::unique_ptr<IScheduler> scheduler;
    TimerManager timers;

    std::mutex kernel_mtx;
    std::condition_variable kernel_cv;

    std::atomic<bool> running{false};
    std::thread sched_thread;
    int last_run_task = -1;
    std::atomic<int> next_task_id{1};
    long long start_ms = 0;

    // example queues (string-message)
    MessageQueue<std::string> default_queue;

public:
    RTOS(std::unique_ptr<IScheduler> sch);
    ~RTOS();

    int create_task(const std::string& name, TaskFunc func, int priority = 0);
    void start();
    void stop();

    // called by API
    void do_yield(Task& t);
    void do_sleep(Task& t, int ms);

    // timer helpers
    void set_timer(const std::string& name, int ms_from_now);
    void remove_timer(const std::string& name);

    // queue access
    MessageQueue<std::string>& get_default_queue() { return default_queue; }

    // snapshot for TUI
    long long system_time_ms();
    // assemble snapshot
    void build_snapshot(struct KernelSnapshot& snap);

private:
    void scheduler_loop();
};
