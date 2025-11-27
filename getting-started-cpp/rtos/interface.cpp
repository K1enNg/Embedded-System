#include "interface.hpp"
#include <iostream>

void interface::render() {
    auto& k = Kernel::get();
    system("cls"); // Windows

    std::cout << "=============== MINI RTOS ===============\n";
    std::cout << "System Time: " << k.systemTime << " ms\n\n";

    std::cout << "Tasks:\n";
    std::cout << "------------------------------------------\n";
    std::cout << "| Name   | State   | Priority | LastExec |\n";
    std::cout << "------------------------------------------\n";

    for (auto* t : k.tasks) {
        std::cout << "| " << t->name << " | "
                  << (t->state == TaskState::RUNNING ? "RUNNING" : "READY")
                  << " | " << t->priority 
                  << " | " << t->lastExec << " |\n";
    }
    std::cout << "------------------------------------------\n";
}