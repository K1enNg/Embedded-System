#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "fsm.h"
#include "timer.h"
#include "input.h"

int main() {
    init_timer();
    fsm_init();

    while (1) {
        fsm_update();
        input_update(); // check keyboard
        sleep_ms(100); // 10Hz loop
    }
    return 0;
}