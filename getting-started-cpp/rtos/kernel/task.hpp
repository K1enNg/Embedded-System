#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <atomic>
#include <memory>
#include <string>

enum class TaskState {Ready, Running, Sleeping, Blocked, Terminated};
using steady_clock = std::chrono::steady_clock;

struct Task;

using TaskFunc = std::function<void(struct TaskAPI&)>;

struct Task {
    int id;
    std::string name;
    int priority;
    TaskState state = TaskState::Ready;
    TaskFunc func;

    //thread simulation primitives
    std::thread thread;
    std::mutex mtx;
    std::condition_variable cv;
    bool should_run = false;
    bool request_stop = false;

    //sleeping
    steady_clock::time_point wake_time = steady_clock::now();

    //last execution timestamp (ms)
    std::atomic<long long> last_exec_ms{0};

    Task(int id_, std::string name_, int prio, TaskFunc f) 
        : id(id_), name(std::move(name_)), priority(prio), func(std::move(f)) {}
}