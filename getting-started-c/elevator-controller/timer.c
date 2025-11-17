#include <timer.h>
#include <windows.h>
#include "timer.h"

static long long timer_target = 0;
 
void init_timer () {
    timer_target = 0;
}

static long long now_ms() {
    return (long long) GetTickCount64();
}

void set_timer (int ms) {
    timer_target = now_ms() + ms;
}

int timer_expired() {
    if (timer_target == 0) {
        return true; // no-timer => consider expired
    }
    return now_ms() >= timer_target;
}

void sleep_ms(int ms) {
    Sleep(ms);
}