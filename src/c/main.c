#include <pebble.h>
#include <time.h>
#include <stdio.h>
#include "main.h"




static void init() {  
  // Display
  display_subscribe();
  
  
  // Subscribe to Timer service
  timer_subscribe();
  
  // Subscribe to Battery service
  battery_subscribe();
  
}

static void deinit() {
  // Clock Timer
  timer_unsubscribe();
  // Battery Charge State
  battery_unsubscribe();
  // Destroy Window
  display_unsubscribe();
}


int main(void) {  
  init();
  app_event_loop();
  deinit();
}

