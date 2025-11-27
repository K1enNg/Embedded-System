#pragma once
#include <vector>
#include "scheduler.hpp"
#include "task.hpp"

class Kernel {
    private:
        Kernel() = default; // singleton
        Scheduler* scheduler;

    public:
        Task* currentTask = nullptr;
        static Kernel* get() {
            static Kernel instance;
            return &instance; // get return a pointer
        }

        std::vector<Task*> tasks;
        int systemTime = 0;

        void setScheduler(Scheduler* s) {
            scheduler = s;
        }

        void addTask(Task* t) {
            tasks.push_back(t);
        }

        void tick();    
        void sleep(Task* t, int ms);
};
