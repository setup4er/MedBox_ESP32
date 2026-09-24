#include "app.h"

// System includes
#include <Arduino.h>

// Project headers
#include "config.h"
#include "drivers/dbg_led.h"
#include "drivers/rtc.h"
#include "comm/bluetooth.h"

static rtc_time_t rtc_time_obj;

void app_init(){
    bluetooth_init();
}

/*      Main cycle    */
void app_update(){
    
}