#include <iostream>
#include <windows.h>
#include <iomanip>

#include "cpu.h"
#include "system.h"
#include "memory.h"

void clearScreen() {
    system("cls");
}

std::string bar (double percent) {
    int width = 50;
    int filled = (percent / 100) * width;

    std::string b = "[";
    for (int i = 0; i < width; i++) {
        b += (i < filled) ? "#" : " ";
    }
    b += "]";
    return b;
}

int main () {
    while (true) {
        clearScreen();

        double cpu = getCPUUsage();
        double ram = getRAMUsage();
        unsigned long long uptime = getUpTimeSeconds();

        std::cout << "=== SYSTEM MONITOR ===\n\n";

        std::cout << "CPU Usage: " << std::fixed <<std::setprecision(2)
                  << cpu << "%" << bar(cpu) << "\n";

        std::cout << "RAM Usage: " << std::fixed <<std::setprecision(2)
                  << cpu << "%" << bar(ram) << "\n";

        std::cout << "\nUpTime: " << uptime << " seconds\n";

        Sleep(1000);
    }

    return 0;
}

