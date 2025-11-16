#ifndef TIMER_H
#define TIMER_H

void init_timer();
void set_timer(int ms);
int timer_expired();
void sleep_ms(int ms);

#endif
