#include "kernel.hpp"
#include "scheduler.hpp" // factory in scheduler.cpp (make_round_robin/make_priority)
#include "tui.hpp"
#include <iostream>
#include <thread>

// sample tasks
void sensor_task(TaskAPI& api) {
    auto& q = api.kernel->get_default_queue();
    // We'll instead use a simple loop writing to default queue via global access through TaskAPI helper
}

// To avoid adding kernel pointer into TaskAPI publicly (keeping encapsulation),
// we will implement example tasks using lambda that capture the queue reference directly
int main() {
    // choose scheduler (round robin or priority)
    extern std::unique_ptr<IScheduler> make_round_robin();
    extern std::unique_ptr<IScheduler> make_priority();

    auto sch = make_round_robin();
    RTOS rtos(std::move(sch));

    // access queue reference to capture into tasks
    MessageQueue<std::string>& q = rtos.get_default_queue();

    // SensorTask: produces temperature messages
    rtos.create_task("SensorTask",
        [&q](TaskAPI& api) {
            for (int i = 0; i < 10; ++i) {
                char buf[64];
                snprintf(buf, sizeof(buf), "TEMP: 26.%d C", 3 - (i%3));
                q.enqueue(std::string(buf));
                // simulate work
                std::this_thread::sleep_for(std::chrono::milliseconds(40));
                api.yield();
            }
        }, 2);

    // LoggerTask: consumes from queue
    rtos.create_task("LoggerTask",
        [&q](TaskAPI& api) {
            for (int i = 0; i < 10; ++i) {
                auto msg = q.dequeue_for(200);
                if (msg) {
                    std::cout << "[Logger] " << *msg << "\n";
                } else {
                    // nothing, yield
                }
                api.yield();
            }
        }, 1);

    // UITask: render TUI every 200ms
    rtos.create_task("UITask",
        [&rtos](TaskAPI& api) {
            TUI tui;
            for (int i = 0; i < 50; ++i) {
                KernelSnapshot snap;
                rtos.build_snapshot(snap);
                tui.draw(snap);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                api.yield();
            }
        }, 3);

    rtos.start();

    // run simulation for a few seconds
    std::this_thread::sleep_for(std::chrono::seconds(6));
    rtos.stop();

    std::cout << "RTOS simulation finished\n";
    return 0;
}
