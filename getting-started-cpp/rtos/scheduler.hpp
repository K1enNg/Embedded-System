#pragma once
#include <vector>
#include "task.hpp"

class Scheduler {
    public:
        virtual Task* selectTask(std::vector<Task*>& tasks) = 0;
};

class RoundRobinScheduler: public Scheduler{
    private:
        int index = -1;

    public:
        Task* selectTask(std::vector<Task*>& tasks) override {
            if(tasks.empty()) {
                return nullptr;
            }

            for (int i = 0; i < tasks.size(); i++) {
                index = (index + 1) % tasks.size();
                if (tasks[index]->state == TaskState::READY)
                    return  tasks[index];
            }
            return nullptr; // all tasks blocked
        }
};