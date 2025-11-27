#pragma once
#include <vector>
#include "task.hpp"

class Scheduler() {
    public:
        virtual Task* selectTask(std::vector<Task*>& task) = 0;
}

class RoundRobinScheduler: public Scheduler{
    private:
        int index = 0;

    public:
        Task* selectTask(std:vector<Task*>& tasks) override {
            if(tasks.empty()) {
                return nullptr;
            }

            index = (index + 1) %  tasks.size();
            return tasks[index];
        }
}