#pragma once
#include <string>
#include <functional>

enum class TaskState {
    READY,
    RUNNING, 
    BLOCKED
}

class Task {
    public:
        using TaskFunc = std::function<void>();

        Task(std::string name, int priority, int periodMs, TaskFunc func)
            : name(name), priority(priority), periodMs(periodMs), callback(func) {} // constructor

        std::string name;
        int priority;
        int period; // for periodic tasks
        int lastExec = 0;
        
        TaskState state = TaskState::READY;
        TaskFunc callback;

        int sleepUntil = 0;
}