#include "drivers/rtc.h"

// Arduino includes
#include <Arduino.h>
#include <iarduino_RTC.h>

// Project includes
#include "drivers/dbg_led.h"
#include "config.h"

static iarduino_RTC rtc(RTC_DS1302, RTC_RST_PIN, RTC_CLK_PIN, RTC_DAT_PIN);


bool init_rtc(){
    bool res = rtc.begin();
    if(!res){
        Serial.println("[RTC] ERROR !!! Initialized unsuccessfully!");
        set_led_status(LED_ERR);
        return false;
    }
    set_led_status(OK);
    Serial.println("[RTC] Initialized successfully!");
    Serial.print("[RTC] Now time: ");
    Serial.println(rtc.gettime("[H:i:s, D(w)]"));

    return true;
}

void rtc_set_time(int16_t hour, int16_t min, int16_t sec, int16_t week_num) {

    if (hour < 0 || hour > 23) {
        Serial.println("[RTC] rtc_set_time: invalid hour");
        return;
    }
    if (min < 0 || min > 59) {
        Serial.println("[RTC] rtc_set_time: invalid minute");
        return;
    }
    if (sec < 0 || sec > 59) {
        Serial.println("[RTC] rtc_set_time: invalid second");
        return;
    }
    if (week_num < 0 || week_num > 6) {
        Serial.println("[RTC] rtc_set_time: invalid weekday (0-6)");
        return;
    }
    // settime(sec, min, hour, day, month, year, weekday)
    rtc.settime(
        sec,
        min,
        hour,
        -1,
        -1,
        -1,
        week_num
    );

    Serial.printf("[RTC] Time set: %02d:%02d:%02d (wd=%d)\n",
                  hour, min, sec, week_num);
}

bool rtc_get_time(rtc_time_t* out){
    if (!out) return false;

    rtc.gettime();

    out->hour = rtc.Hours;
    out->minute = rtc.minutes;
    out->second = rtc.seconds;
    out->weekday = rtc.weekday;

    return true;
}

char *rtc_get_time(){
    char *result = rtc.gettime("H:i:s, D(w)");
    return result;
}