#include <pebble.h>
#include "battery.h"



BatteryChargeState battery_charge;
bool battery_flag;
bool plugged_flag;
bool charging_flag;

void battery_handler(BatteryChargeState battery_charge_1) {
  static char battery_text[] = "----";
  battery_charge = battery_charge_1;
  
  bool temp = plugged_flag;
  charging_flag = battery_charge.is_charging;
  plugged_flag = battery_charge.is_plugged;
  if ((temp==false) && (plugged_flag==true)){
    //APP_LOG(APP_LOG_LEVEL_WARNING,"PLUGGED IN!");
    battery_flag = false;
  }
  else if ((temp==true) && (plugged_flag==false)){
    //APP_LOG(APP_LOG_LEVEL_WARNING,"UNPLUGGED!");
    battery_flag = true;
  }
  
  if (charging_flag) {
    snprintf(battery_text, sizeof(battery_text), ">>>>");
  } else {
    snprintf(battery_text, sizeof(battery_text), "%d%%", battery_charge.charge_percent);
  }
  text_layer_set_text(s_battery_layer, battery_text);
  
}

void battery_subscribe(){
  battery_state_service_subscribe(battery_handler);
  battery_charge = battery_state_service_peek();
  charging_flag = battery_charge.is_charging;
  plugged_flag = battery_charge.is_plugged;
  battery_flag = (plugged_flag?false:true);
  battery_handler(battery_charge);
}

void battery_unsubscribe(){
  battery_state_service_unsubscribe();
}
