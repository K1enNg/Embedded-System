#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "elevator.h"
#include "input.h"
#include "timer.h"

int main() {
    system("chcp 65001 > nul"); // enable UTF-8
    init_timer();
    elevator_init();

    while(1) {
        elevator_update(); //check for button presses
        input_update(); // check for timer expiry
        sleep_ms(100); // slow down loop
    }
    return 0;
}