#include <pebble.h>
#include "clicks.h"

static int vibes_key_local = 0;
static int font_key_local = 0;

uint32_t segments[] = { 200, 100, 400 };
VibePattern pattern = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};

void vibes_action(int vibes_key){
  light_enable(true);
  delay_time(10);
  switch (vibes_key){
    case 0: 
      text_layer_set_text(s_opt_layer, "Option # 1");
      vibes_short_pulse(); break;
      //vibes_long_pulse(); break;
    case 1:
      text_layer_set_text(s_opt_layer, "Option # 2");
      segments[0] = 400;
      segments[1] = 200;
      segments[2] = 700;
      vibes_enqueue_custom_pattern(pattern); break;
      //vibes_short_pulse(); break;
    case 2:
      text_layer_set_text(s_opt_layer, "Option # 3");
      segments[0] = 200;
      segments[1] = 100;
      segments[2] = 400;
      vibes_enqueue_custom_pattern(pattern); break;
      //vibes_double_pulse(); break;
    /*
    case 3:
      text_layer_set_text(s_opt_layer, "Option # 4");
      segments[0] = 200;
      segments[1] = 100;
      segments[2] = 400;
      vibes_enqueue_custom_pattern(pattern); break;
    case 4:
      text_layer_set_text(s_opt_layer, "Option # 5");
      segments[0] = 400;
      segments[1] = 200;
      segments[2] = 700;
      vibes_enqueue_custom_pattern(pattern); break;
    case 5:
      text_layer_set_text(s_opt_layer, "Option # 6");
      segments[0] = 1000;
      segments[1] = 500;
      segments[2] = 1000;
      vibes_enqueue_custom_pattern(pattern); break;
    case 6:
      text_layer_set_text(s_opt_layer, "Option # 7");
      segments[0] = 700;
      segments[1] = 400;
      segments[2] = 700;
      vibes_enqueue_custom_pattern(pattern); break;
    case 7:
      text_layer_set_text(s_opt_layer, "Option # 8");
      segments[0] = 500;
      segments[1] = 500;
      segments[2] = 500;
      vibes_enqueue_custom_pattern(pattern); break;
    */
    default:
      text_layer_set_text(s_opt_layer, "Option # 0");
      vibes_long_pulse(); break;
  }
  delay_time(10);
  light_enable(false);
  //APP_LOG(APP_LOG_LEVEL_INFO, "%lu", *(pattern.durations));
  //APP_LOG(APP_LOG_LEVEL_INFO, "%lu", *(pattern.durations+1));
  //APP_LOG(APP_LOG_LEVEL_INFO, "%lu", *(pattern.durations+2));
  return;
}

void font_action(int font_key){
  light_enable(true);
  switch (font_key){
    case 0: 
      text_layer_set_text(s_opt_layer, "Option # 1");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD)); break;
      //text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); break;
    case 1:
      text_layer_set_text(s_opt_layer, "Option # 2");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD)); break;
      //text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD)); break;
    case 2:
      text_layer_set_text(s_opt_layer, "Option # 3");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD)); break;
      //text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18)); break;
    /*
    case 3:
      text_layer_set_text(s_opt_layer, "Option # 4");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD)); break;
    case 4:
      text_layer_set_text(s_opt_layer, "Option # 5");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24)); break;
    case 5:
      text_layer_set_text(s_opt_layer, "Option # 6");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD)); break;
    case 6:
      text_layer_set_text(s_opt_layer, "Option # 7");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28)); break;
    case 7:
      text_layer_set_text(s_opt_layer, "Option # 8");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD)); break;
    */
    default:
      text_layer_set_text(s_opt_layer, "Option # 0");
      text_layer_set_font(s_msg_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24)); break;
  }
  delay_time(10);
  light_enable(false);
  return;
}



void update_scene(uint8_t click_id, char* context) {     
  APP_LOG(APP_LOG_LEVEL_INFO, "%s", context);
  if (strcmp(context, "MAIN")==0){
    if (click_id==11){
      window_stack_push(s_font_window, true);
    }
    else if (click_id==12){
      window_stack_push(s_vibe_window, true);
    }
    else if (click_id==14){
      delay_time(5);
    }
  }
  else if (strcmp(context, "FONT")==0){
    int font_option_count = 3;
    if (click_id==11){
      if (font_key_local==0){
        font_key_local = font_option_count;
      }
      font_key_local = (font_key_local - 1) % font_option_count;
      font_action(font_key_local);
    }
    else if (click_id==12){
      font_key_local = (font_key_local + 1) % font_option_count;
      font_action(font_key_local);
    }
    else if (click_id==14){
      window_stack_remove(s_font_window,true);
    }
  }
  else if (strcmp(context, "VIBE")==0){
    int vibe_option_count = 3;
    if (click_id==11){
      if (vibes_key_local==0){
        vibes_key_local = vibe_option_count;
      }
      vibes_key_local = (vibes_key_local - 1) % vibe_option_count;
      vibes_action(vibes_key_local);
    }
    else if (click_id==12){
      vibes_key_local = (vibes_key_local + 1) % vibe_option_count;
      vibes_action(vibes_key_local);
    }
    else if (click_id==14){
      window_stack_remove(s_vibe_window,true);
    }
  }
  else{
    return;
  }

}


void single_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  uint8_t click_id = 11;
  update_scene(click_id, (char*)context);
  delay_time(1);
}

void single_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  uint8_t click_id = 12;
  update_scene(click_id, (char*)context);
  delay_time(1);
}

void single_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 13;
  //update_params(click_id,(char*)context);
  delay_time(5);
}

void single_back_click_handler(ClickRecognizerRef recognizer, void *context) {
  uint8_t click_id = 14;
  update_scene(click_id,(char*)context);
  delay_time(1);
}

/*
void long_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 21;
  //update_params(click_id,(char*)context);
  delay_time(1);
}

void long_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 22;
  //update_params(click_id,(char*)context);
  delay_time(1);
}

void long_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 23;
  //update_params(click_id,(char*)context);
  delay_time(1);
}



void multi_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 31;
  //update_params(click_id,(char*)context);
  delay_time(1);
}

void multi_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 32;
  //update_params(click_id,(char*)context);
  delay_time(1);
}

void multi_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 33;
  //update_params(click_id,(char*)context);
  delay_time(1);
}

void multi_back_click_handler(ClickRecognizerRef recognizer, void *context) {
  //uint8_t click_id = 34;
  //update_params(click_id,(char*)context);
  delay_time(1);
}
*/


void config_provider(void *ctx) {  
  window_single_click_subscribe(BUTTON_ID_UP, single_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, single_down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, single_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, single_back_click_handler);
  //window_long_click_subscribe(BUTTON_ID_UP, 1000, long_up_click_handler, NULL);
  //window_long_click_subscribe(BUTTON_ID_DOWN, 1000, long_down_click_handler, NULL);
  //window_long_click_subscribe(BUTTON_ID_SELECT, 1000, long_select_click_handler, NULL);
  //window_multi_click_subscribe(BUTTON_ID_UP, 2, 3, 1000, true, multi_up_click_handler);
  //window_multi_click_subscribe(BUTTON_ID_DOWN, 2, 3, 1000, true, multi_down_click_handler);
  //window_multi_click_subscribe(BUTTON_ID_SELECT, 2, 3, 1000, true, multi_select_click_handler);
  //window_multi_click_subscribe(BUTTON_ID_BACK, 2, 3, 1000, true, multi_back_click_handler);
}

