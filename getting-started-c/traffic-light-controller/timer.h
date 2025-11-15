#include <stdbool.h>
#ifndef TIMER_H
#define TIMER_H

void init_timer();
void set_timer(int ms);
bool timer_expired();
void sleep_ms(int ms);

#endif