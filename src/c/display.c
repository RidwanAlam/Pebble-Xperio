#include <pebble.h>
#include "display.h"


static const GRect BATTERY_POSITIONS =  { { 0,  0 }, { /* width: */ 124, /* height: */  16} };
static const GRect TIME_POSITIONS =     { { 0, 24 }, { /* width: */ 124, /* height: */  56} };
static const GRect DATE_POSITIONS =     { { 0, 96 }, { /* width: */ 124, /* height: */  56} };
static const GRect TEXT_POSITIONS  =    { { 0,152 }, { /* width: */ 124, /* height: */  24} };
// total dimension: 176 (row) x 144 (col)

static const GRect MSG_POSITIONS =         { { 16,  0 }, { /* width: */ 112, /* height: */  144} };
static const GRect OPT_POSITIONS =         { { 16,  144}, { /* width: */ 112, /* height: */  32} };
static const GRect RIGHT_UP_POSITIONS =    { { 128, 0 }, { /* width: */ 16, /* height: */  88} };
static const GRect RIGHT_DOWN_POSITIONS =  { { 128, 88 }, { /* width: */ 16, /* height: */  88} };
static const GRect LEFT_POSITIONS =        { { 0, 0 }, { /* width: */ 16, /* height: */  176} };



static Window *s_main_window;
static ActionBarLayer *s_action_bar_layer;
TextLayer *s_battery_layer;
TextLayer *s_date_layer;
TextLayer *s_time_layer;
TextLayer *s_text_layer;


Window *s_font_window;
static ActionBarLayer *s_font_bar_layer;
Window *s_vibe_window;
static ActionBarLayer *s_vibe_bar_layer;

TextLayer *s_msg_layer;
static TextLayer *s_right_up_layer;
static TextLayer *s_right_down_layer;
static TextLayer *s_left_layer;
TextLayer *s_opt_layer;

// TextLayer *s_haptic_msg_layer;
// static TextLayer *s_haptic_right_up_layer;
// static TextLayer *s_haptic_right_down_layer;
// static TextLayer *s_haptic_left_layer;


void font_window_load(Window *window) {  
  // Create ActionBar
  void *context = "FONT";
  window_set_click_config_provider_with_context(window, config_provider, context);
  /*
  s_response_bar_layer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_response_bar_layer, window);
  action_bar_layer_set_context(s_response_bar_layer, context);
  action_bar_layer_set_click_config_provider(s_response_bar_layer, config_provider);
  */
  
  // Create TextLayer for Message
  s_msg_layer = text_layer_create(MSG_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_msg_layer));
  text_layer_set_text(s_msg_layer, "A Quick Brown FOX Jumps Over The Lazy DOG."); //"A QUICK BROWN FOX JUMPS OVER THE LAZY DOG,\na quick brown fox jumps over the lazy dog."
  text_layer_set_background_color(s_msg_layer, GColorWhite);
  text_layer_set_text_color(s_msg_layer, GColorBlack);
  text_layer_set_text_alignment(s_msg_layer, GTextAlignmentLeft);
  text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));

  // Create TextLayer for Options
  s_opt_layer = text_layer_create(OPT_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_opt_layer));
  text_layer_set_text(s_opt_layer, "Option # 0");
  text_layer_set_background_color(s_opt_layer, GColorWhite);
  text_layer_set_text_color(s_opt_layer, GColorBlack);
  text_layer_set_text_alignment(s_opt_layer, GTextAlignmentCenter);
  text_layer_set_font(s_opt_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));

  // Create TextLayer for RIGHT UP
  s_right_up_layer = text_layer_create(RIGHT_UP_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_right_up_layer));
  text_layer_set_text(s_right_up_layer, "P\nR\nE\nV");
  text_layer_set_background_color(s_right_up_layer, GColorBlack);
  text_layer_set_text_color(s_right_up_layer, GColorWhite);
  text_layer_set_text_alignment(s_right_up_layer, GTextAlignmentCenter);
  text_layer_set_font(s_right_up_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 
  // Create TextLayer for RIGHT DOWN
  s_right_down_layer = text_layer_create(RIGHT_DOWN_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_right_down_layer));
  text_layer_set_text(s_right_down_layer, "\nN\nE\nX\nT");
  text_layer_set_background_color(s_right_down_layer, GColorBlack);
  text_layer_set_text_color(s_right_down_layer, GColorWhite);
  text_layer_set_text_alignment(s_right_down_layer, GTextAlignmentCenter);
  text_layer_set_font(s_right_down_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 
  
  // Create TextLayer for LEFT
  s_left_layer = text_layer_create(LEFT_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_left_layer));
  text_layer_set_text(s_left_layer, "\n\nH\nO\nM\nE");
  text_layer_set_background_color(s_left_layer, GColorBlack);
  text_layer_set_text_color(s_left_layer, GColorWhite);
  text_layer_set_text_alignment(s_left_layer, GTextAlignmentCenter);
  text_layer_set_font(s_left_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 

}

void font_window_unload(Window *window) {
  action_bar_layer_destroy(s_font_bar_layer);
  text_layer_destroy(s_msg_layer);
  text_layer_destroy(s_opt_layer);
  text_layer_destroy(s_left_layer);
  text_layer_destroy(s_right_up_layer);
  text_layer_destroy(s_right_down_layer);
}


void vibe_window_load(Window *window) {  
  // Create ActionBar
  void *context = "VIBE";
  window_set_click_config_provider_with_context(window, config_provider, context);
  /*
  s_response_bar_layer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_response_bar_layer, window);
  action_bar_layer_set_context(s_response_bar_layer, context);
  action_bar_layer_set_click_config_provider(s_response_bar_layer, config_provider);
  */
  
  // Create TextLayer for Message
  s_msg_layer = text_layer_create(MSG_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_msg_layer));
  text_layer_set_text(s_msg_layer, "Experience \n Vibration Levels!");
  text_layer_set_background_color(s_msg_layer, GColorWhite);
  text_layer_set_text_color(s_msg_layer, GColorBlack);
  text_layer_set_text_alignment(s_msg_layer, GTextAlignmentCenter);
  text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));

  // Create TextLayer for Options
  s_opt_layer = text_layer_create(OPT_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_opt_layer));
  text_layer_set_text(s_opt_layer, "Option # 0");
  text_layer_set_background_color(s_opt_layer, GColorWhite);
  text_layer_set_text_color(s_opt_layer, GColorBlack);
  text_layer_set_text_alignment(s_opt_layer, GTextAlignmentCenter);
  text_layer_set_font(s_opt_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));

  // Create TextLayer for RIGHT UP
  s_right_up_layer = text_layer_create(RIGHT_UP_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_right_up_layer));
  text_layer_set_text(s_right_up_layer, "P\nR\nE\nV");
  text_layer_set_background_color(s_right_up_layer, GColorBlack);
  text_layer_set_text_color(s_right_up_layer, GColorWhite);
  text_layer_set_text_alignment(s_right_up_layer, GTextAlignmentCenter);
  text_layer_set_font(s_right_up_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 
  // Create TextLayer for RIGHT DOWN
  s_right_down_layer = text_layer_create(RIGHT_DOWN_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_right_down_layer));
  text_layer_set_text(s_right_down_layer, "\nN\nE\nX\nT");
  text_layer_set_background_color(s_right_down_layer, GColorBlack);
  text_layer_set_text_color(s_right_down_layer, GColorWhite);
  text_layer_set_text_alignment(s_right_down_layer, GTextAlignmentCenter);
  text_layer_set_font(s_right_down_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 
  
  // Create TextLayer for LEFT
  s_left_layer = text_layer_create(LEFT_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_left_layer));
  text_layer_set_text(s_left_layer, "\n\nH\nO\nM\nE");
  text_layer_set_background_color(s_left_layer, GColorBlack);
  text_layer_set_text_color(s_left_layer, GColorWhite);
  text_layer_set_text_alignment(s_left_layer, GTextAlignmentCenter);
  text_layer_set_font(s_left_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 

}

void vibe_window_unload(Window *window) {
  action_bar_layer_destroy(s_vibe_bar_layer);
  text_layer_destroy(s_msg_layer);
  text_layer_destroy(s_opt_layer);
  text_layer_destroy(s_left_layer);
  text_layer_destroy(s_right_up_layer);
  text_layer_destroy(s_right_down_layer);
}



void main_window_load(Window *window) {  
  // Create ActionBar
  void *context = "MAIN";
  window_set_click_config_provider_with_context(window, config_provider, context);
  /*
  s_action_bar_layer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_action_bar_layer, window);
  action_bar_layer_set_context(s_action_bar_layer, context);
  action_bar_layer_set_click_config_provider(s_action_bar_layer, config_provider);
  */
  
  // Create TextLayer for Battery
  s_battery_layer = text_layer_create(BATTERY_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_battery_layer));
  text_layer_set_background_color(s_battery_layer, GColorBlack);
  text_layer_set_text_color(s_battery_layer, GColorWhite);
  text_layer_set_text_alignment(s_battery_layer, GTextAlignmentRight);
  text_layer_set_font(s_battery_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  
  // Create TextLayer for Time
  s_time_layer = text_layer_create(TIME_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_background_color(s_time_layer, GColorBlack);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS)); //FONT_KEY_ROBOTO_BOLD_SUBSET_49

  // Create TextLayer for Date
  s_date_layer = text_layer_create(DATE_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  text_layer_set_text(s_date_layer, "XXXDay\n00/00/0000");
  text_layer_set_background_color(s_date_layer, GColorBlack);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  
  // Create TextLayer for Text
  s_text_layer = text_layer_create(TEXT_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer));
  text_layer_set_text(s_text_layer, " "); //"No event marked" // changes made: 03/20/16
  text_layer_set_background_color(s_text_layer, GColorBlack);
  text_layer_set_text_color(s_text_layer, GColorWhite);
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 

  // Create TextLayer for RIGHT UP
  s_right_up_layer = text_layer_create(RIGHT_UP_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_right_up_layer));
  text_layer_set_text(s_right_up_layer, "F\nO\nN\nT");
  text_layer_set_background_color(s_right_up_layer, GColorWhite);
  text_layer_set_text_color(s_right_up_layer, GColorBlack);
  text_layer_set_text_alignment(s_right_up_layer, GTextAlignmentCenter);
  text_layer_set_font(s_right_up_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 
  // Create TextLayer for RIGHT DOWN
  s_right_down_layer = text_layer_create(RIGHT_DOWN_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_right_down_layer));
  text_layer_set_text(s_right_down_layer, "\nV\nI\nB\nE");
  text_layer_set_background_color(s_right_down_layer, GColorWhite);
  text_layer_set_text_color(s_right_down_layer, GColorBlack);
  text_layer_set_text_alignment(s_right_down_layer, GTextAlignmentCenter);
  text_layer_set_font(s_right_down_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); 
  
}



void main_window_unload(Window *window) {
  action_bar_layer_destroy(s_action_bar_layer);
  text_layer_destroy(s_battery_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_text_layer);
  text_layer_destroy(s_right_up_layer);
  text_layer_destroy(s_right_down_layer);
}



void display_subscribe(){
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  s_font_window = window_create();
  window_set_background_color(s_font_window, GColorBlack);
  s_vibe_window = window_create();
  window_set_background_color(s_vibe_window, GColorBlack);
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_set_window_handlers(s_font_window, (WindowHandlers) {
    .load = font_window_load,
    .unload = font_window_unload,
  });
  window_set_window_handlers(s_vibe_window, (WindowHandlers) {
    .load = vibe_window_load,
    .unload = vibe_window_unload,
  });

  window_stack_push(s_main_window, true);
  //window_stack_push(s_notification_window, true);
}


void display_unsubscribe(){
  window_destroy(s_main_window);
  window_destroy(s_font_window);
  window_destroy(s_vibe_window);
}