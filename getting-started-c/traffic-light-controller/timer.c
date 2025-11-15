#include <time.h>
#include <windows.h>
#include "timer.h"

static clock_t start_time;
static int duration_ms = 0;

void init_timer() {
    start_time = clock();
}

void set_timer(int ms) {
    duration_ms = ms;
    start_time = clock();
}

bool timer_expired() {
    clock_t now = clock();
    int elapsed = (int)((now - start_time) * 1000 / CLOCKS_PER_SEC);
    return elapsed >= duration_ms;
}

void sleep_ms(int ms) {
    Sleep(ms);
}