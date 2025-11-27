#include <iostream>
#include "kernel.hpp"
#include "interface.hpp"
#include "scheduler.hpp"

int main() {
    auto* k = Kernel::get();
    k->setScheduler(new RoundRobinScheduler());

    k->addTask(new Task("SensorTask", 1, 1000, [](){
        static bool on = false;
        on = !on;

        std::cout << "[BlinkTask] LED = " << (on ? "ON" : "OFF") << "\n";
        
        Kernel::get()->sleep(Kernel::get()->currentTask, 500);
    }));

    k->addTask(new Task("LoggerTask", 1, 1500, [](){
        // simulate writing logs
    }));

    k->addTask(new Task("UITask", 1, 100, [](){
        interface::render();
    }));

    while (true) {
        k->tick();
    }
}