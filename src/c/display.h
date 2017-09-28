#ifndef DISPLAY_INCLUDE
#define DISPLAY_INCLUDE
#include <pebble.h>
#include "main.h"

extern TextLayer *s_date_layer;
extern TextLayer *s_time_layer;
extern TextLayer *s_battery_layer;
extern TextLayer *s_text_layer;

extern Window *s_font_window;
extern Window *s_vibe_window;
extern TextLayer *s_msg_layer;
extern TextLayer *s_opt_layer;

extern void display_subscribe();
extern void display_unsubscribe();

#endif
