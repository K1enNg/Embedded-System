#pragma once
#include <vector>
#include "scheduler.hpp"
#include "task.hpp"

class Kernel {
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

        void tick();    
}
