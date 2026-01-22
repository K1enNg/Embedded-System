#include <iostream>
#include <nlohmann/json.hpp>
#include "domain/Task.h"

int main() {
    Task t{
        .id = 1,
        .title = "Finish COEN homework",
        .completed = false,
        .created_at = std::chrono::system_clock::now(),
        .due_at = std::chrono::system_clock::now()
    };

    nlohmann::json j = t;
    std::cout << j.dump(4) << "\n";

    Task restored = j.get<Task>();
    std::cout << restored.title << "\n";
}
