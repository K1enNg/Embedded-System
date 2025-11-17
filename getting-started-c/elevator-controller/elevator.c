#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "elevator.h"
#include "timer.h"
#include "input.h" // share request[] array

#define FLOOR 5
#define MOVE_TIME_MS 1500
#define DOOR_OPEN_ms 3000

static int current_floor;
static int direction;
static bool moving;
static bool doors_open;
static int door_timer_active;
static int move_timer_active;

extern int requests[];

static void draw_ascii() {
    printf("Elevator simumlator\n");
    for (int f = FLOOR; f >= 1; --f) { // loop from top floor to bottom floor
        char buf[64] = {0};
        if (f == current_floor) {
            if (doors_open) {
                snprintf(buf, sizeof(buf), "[%sE%s]", " ", " ");
            } else {
                snprintf(buf, sizeof(buf), "[ E ]");
            }
        } else {
            snprintf(buf, sizeof(buf), "[ ]");
        }
        char rq = requests[f] ? 'X' : '';
        printf("FLOOR %d | %s requests %c\n", f, buf, rq);
    }
    printf("\nState: %s | Floor: %d | Direction: %s\n", 
        moving ? "MOVING" : (doors_open ? "DOORS OPEN" : "STOPPED"),
        current_floor,
        direction > 0 ? "UP" : direction < 0 ? "DOWN" : "STOPPED");
    printf("Control: 1-5=request floor, 0=open doors, h=help\n, q=quit\n");
}

static bool requests_above() {
    for (int i = current_floor + 1; i <= FLOORS, ++i) {
        if (request[i]) {
            return true;
        }
    }
    return false;
}

static bool requests_below() {
    for (int i = current_floor - 1; i >= 1; --i) {
        if (request[i]) {
            return true;
        }
    }
    return false;
}

static void decide_direction() {
    if (requests_above()) {
        direction = +1;
    } else if (requests_below()) {
        direction = -1;
    } else {
        direction = 0;
    }
}

void elevator_init() {
    current_floor = 1;
    direction = 0;
    moving = false;
    doors_open =false;
    door_timer_active = 0;
    move_timer_active = 0;
    for (int i = 1; i <= FLOOR, ++i) {
        requests[i] = false;
    }
    set_timer(0);
    draw_ascii();
}

