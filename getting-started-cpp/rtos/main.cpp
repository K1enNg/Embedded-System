#include "kernel.hpp"
#include "interface.hpp"
#include "scheduler.hpp"

int main() {
    auto& k = Kernel::get();
    k.setScheduler(new RoundRobinScheduler())

    k.addTask(new Task("SensorTask", 1, 1000, [](){
        // simulate reading sensor
    }));

    k.addTask(new Task("LoggerTask", 1, 1500, [](){
        // simulate writing logs
    }));

    k.addTask(new Task("UITask", 1, 100, [](){
        TUI::render();
    }));

    while (true) {
        k.tick();
    }
}