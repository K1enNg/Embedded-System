#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

int requests[6] = {0};

void print_help() {
    printf("\nHELP:\n");
    printf("  Press 1-5 : request elevator to that floor (cabin or external)\n");
    printf("  Press o   : open doors (manual)\n");
    printf("  Press h   : show help\n");
    printf("  Press q   : quit program\n");
    printf("\n");
}

void input_update() {
    if (_kbhit()){
        int c = _getch();
        if (c >= '1' && c <= '5') {
            int f = c - '0';
            requests[f] = 1;
        } else if (c == 'o' || c == 'O') {
            requests[0] = 1;
        } else if (c == 'h' || c == 'H') {
            print_help();
        } else if (c == 'q' || c == 'Q') {
            exit(0);
        }
    }
}
