#ifndef TIMER_INCLUDE
#define TIMER_INCLUDE
#include <pebble.h>
#include "main.h"


extern uint8_t dummy_count;
extern void delay_time(int);
extern void timer_subscribe();
extern void timer_unsubscribe();

#endif
