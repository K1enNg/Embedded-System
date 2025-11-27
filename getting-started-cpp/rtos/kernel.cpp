#include "kernel.hpp"
#include <thread>
#include <chrono>

void Kernel::tick() {
    systemTime += 100;

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