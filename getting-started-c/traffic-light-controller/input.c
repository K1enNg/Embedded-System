#include <conio.h>
#include <stdlib.h>
#include "input.h"

int ped_request = 0;
int night_mode = 0;

void input_update() {
    if (_kbhit()) {
        char c = _getch();

        if (c == 'p') {
            ped_request = 1;
        } 
        if (c == 'n') {
            night_mode = !night_mode;
        }
        if (c == 'q') {
            exit(0);
        }
    }
}