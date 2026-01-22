#pragma once

#include <chrono>
#include <string>

namespace DateTime {
    std::string toISOString(const std::chrono::system_clock::time_point& tp);
    std::chrono::system_clock::time_point fromISOString(const std::string& str);
}