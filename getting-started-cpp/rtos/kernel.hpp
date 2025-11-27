#pragma once
#include <vector>
#include "scheduler.hpp"
#include "task.hpp"

class Kernel {

    Task* currentTask = nullptr;

    private:
        Kernel() = default; // singleton
        Scheduler* scheduler;

    public:
        static Kernel* get() {
            static Kernel instance;
            return instance;
        }

        std::vector<Task*> tasks;
        int systemTime = 0;

        void setScheduler(Scheduler* s) {
            scheduler = s;
        }

        void addTask(Task* t) {
            tasks.pushBack(t);
        }

        void tick() {
            currentTask = t;
            t->state = TaskState::RUNNING;
            t->callback();
            t->lastExec = systemTime;
            t->state = TaskState::READY;
            currentTask = nullptr;
        };    
        void sleep(Task* t, int ms);
}
