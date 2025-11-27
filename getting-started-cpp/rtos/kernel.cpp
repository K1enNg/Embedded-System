#include "kernel.hpp"
#include <thread>
#include <chrono>

void Kernel::tick() {
    systemTime += 100;

    for(auto* t: tasks) {
        if (t->state == TaskState::BLOCKED && systemTime >= t->sleepUntil) {
            t->state = TaskState::READY
        }
    }

    Task* t = scheduler->selectTask(tasks);
    if (!t) {
        return;
    }

    t->state = TaskState::RUNNING;
    t->callback();
    t->lastExec = systemTime;
    t->state = TaskState::READY;

    std::thisThread::sleepFor(std::chrono::milliseconds(100));
}

void Kernel::sleep(Task* t, int ms) {
    t->state = TaskState::BLOCKED;
    t->sleepUntil = systemTime + ms;
}