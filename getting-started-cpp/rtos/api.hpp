#pragma once
#include "kernel.hpp"

inline void task_sleep(int ms) {
    Kernel* k = Kernel::get();
    k->sleep(k->currentTask, ms);
}