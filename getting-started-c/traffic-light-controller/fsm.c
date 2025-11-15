#include <stdio.h>
#include "fsm.h"
#include "timer.h"
#include "input.h"

typedef enum {
    STATE_RED,
    STATE_GREEN,
    STATE_YELLOW,
    STATE_PED,
    STATE_NIGHT
} TrafficState;

static TrafficState state;

void fsm_init() {
    state = STATE_RED;
    set_timer(5000); // 5 seconds
}

void print_lights(const char* red, const char* yellow, const char* green, const char* ped) {
    printf("\033[2J\033[H");
    printf("RED     [%s]\n", red);
    printf("YELLOW  [%s]\n", yellow);
    printf("GREEN   [%s]\n", green);
    printf("PED     [%s]\n", ped);
}

void fsm_update() {
    switch (state) {
        case STATE_RED:
            print_lights("●", "○", "○", ped_request ? "●" : "○");
            if (timer_expired()) {
                if (ped_request) {
                    state = STATE_PED;
                    set_timer(4000);
                } else {
                    state = STATE_GREEN;
                    set_timer(5000);
                }
            }
            break;
        case STATE_GREEN:
            print_lights("○", "○", "●", ped_request ? "●" : "○");
            if (timer_expired()) {
                state = STATE_YELLOW;
                set_timer(2000);
            }
            break;
        case STATE_YELLOW:
            print_lights("○", "●", "○", ped_request ? "●" : "○");
            if (timer_expired()) {
                state = STATE_RED;
                set_timer(5000);
            }
            break;
        case STATE_PED:
            print_lights("●", "○", "○", "●");
            if (timer_expired()) {
                state = STATE_RED;
                set_timer(5000);
            }
            break;
        case STATE_NIGHT:
            print_lights("○",(timer_expired() ? "●" : "○"), "○", "○");
            if (timer_expired()) {
                set_timer(500);
            }
            break;
    }
    if (night_mode) {
        state = STATE_NIGHT;
        set_timer(500);
    }
}