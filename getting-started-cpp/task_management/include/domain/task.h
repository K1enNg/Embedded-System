#pragma once

#include <string>
#include <chrono>

struct Task {
    int id{};
    std::string title;
    bool completed{false};

    std::chrono::system_clock::time_point create_at;
    std::chrono::system_clock::time_point due_at;
}