#pragma once
#include <mutex>
#include <condition_variable>
#include <deque>
#include <optional>

// simple thread-safe queue (not coupled to kernel; tasks can block on it)
template<typename T>
class MessageQueue {
    std::mutex mtx;
    std::condition_variable cv;
    std::deque<T> q;
    size_t capacity = 64;

public:
    MessageQueue(size_t cap = 64) : capacity(cap) {}

    void enqueue(const T& item) {
        std::unique_lock lk(mtx);
        // simple bounded behavior: drop oldest if full
        if (q.size() >= capacity) q.pop_front();
        q.push_back(item);
        lk.unlock();
        cv.notify_one();
    }

    // blocking dequeue with timeout (ms). returns std::nullopt on timeout
    std::optional<T> dequeue_for(int timeout_ms) {
        std::unique_lock lk(mtx);
        if (q.empty()) {
            if (cv.wait_for(lk, std::chrono::milliseconds(timeout_ms)) == std::cv_status::timeout)
                return std::nullopt;
        }
        if (q.empty()) return std::nullopt;
        T v = q.front();
        q.pop_front();
        return v;
    }

    // non-blocking snapshot of contents (copy)
    std::deque<T> snapshot() {
        std::lock_guard lk(mtx);
        return q;
    }
};
