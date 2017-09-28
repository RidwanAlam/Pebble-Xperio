#ifndef BATTERY_INCLUDE
#define BATTERY_INCLUDE
#include <pebble.h>
#include "main.h"


extern BatteryChargeState battery_charge;
extern void battery_subscribe(void);
extern void battery_unsubscribe(void);

#endif

