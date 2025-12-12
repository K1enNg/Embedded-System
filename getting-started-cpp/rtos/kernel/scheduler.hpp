#pragma once
#include "task.hpp"
#include <map>
#include <memory>

class IScheduler {
    public: 
        virtual ~IScheduler() = default;
        // choose next runnable task id or -1
        virtual int pick_next(const std::map<int, std::shared_ptr<Task>& tasks, int last_run) = 0;
}