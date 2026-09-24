#include "drivers/dbg_led.h"

// Arduino includes
#include <Arduino.h>


// Project headers
#include "config.h"


void led_dbg_init(){
    pinMode(DBG_LED, OUTPUT);
    digitalWrite(DBG_LED, LOW);
    Serial.print("[DBG_LED] Initialized successfully!\n");
    set_led_dbg_status(LED_OK);
}

void set_led_dbg_status(int status){
    switch (status)
    {
    case LED_OK:
        digitalWrite(DBG_LED, HIGH);
        delay(100);
        digitalWrite(DBG_LED, LOW);
        delay(100);
        break;
    
    case LED_ERR:
        while(1){
            digitalWrite(DBG_LED, HIGH);
            delay(800);
            digitalWrite(DBG_LED, LOW);
            delay(800);
        }
    default:
        break;
    }

}