#include "domain/datetime.cpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace DateTime {
    std::string toISOString(const std::chrono::system_clock::time_point& tp) {
        std::time_t time = std::chrono::system_clock::to_time_t(tp)
        std::tm utc{};
    
    #ifdef _WIN32
        gmtime_s(&utc, &time);
    #else
        gmtime_r(&time, &utc);
    #endif

        std::ostringstream oss;
        oss << std::put_time(&utc, "%Y-%m-%dT%H:%M:%SZ");
        return oss.str();
    }

    std::chrono::system_clock::time_point fromISOString(const std::string& str) {
        std::tm tm{};
        std::istringstream iss(str);
        iss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");

        if (iss.fail()) {
            throw std::runtime_error("Invalid ISO-8601 datetime");
        }
    
    #if defined(_WIN32)
        std::time_t time = _mkgmtime(&tm);
    #else 
        std::time_t time = timegm(&tm);
    #endif

    return std::chrono::system_clock::from_time_t(time);
    }
}