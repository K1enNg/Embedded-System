#include once
#include "kernel.cpp"

incline void task_sleep(int ms) {
    auto& k = Kernel::get();
    k.sleep(k.currentTask, ms);
}