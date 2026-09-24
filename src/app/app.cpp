#include "app.h"

// System includes
#include <Arduino.h>

// Project headers
#include "config.h"
#include "drivers/dbg_led.h"
#include "drivers/rtc.h"

static rtc_time_t rtc_time_obj;

void init_app(){
    //init_bluetooth();
}


/*      Main cycle    */
void app_update(){
    rtc_get_time(&rtc_time_obj);
    delay(1000);
    Serial.println(rtc_time_obj.second);

}