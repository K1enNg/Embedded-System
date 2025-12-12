#pragma once
#include <chrono>

struct Task;
class RTOS;

class TaskAPI {
    Task& task;
    RTOS& kernel;

    public:
        TaskAPI(Task& t, RTOS& k);
        // cooperate primitives
        void yield();
        void sleep_for_ms(int ms);
        // meta
        int id() const;
        const char* name() const;
        int priority() const;
}