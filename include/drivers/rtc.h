#ifndef RTC_H
#define RTC_H

/**
 * @file rtc.h
 * @date 2026-09-24
 * @description RTC Module header file
 */
#include <cstdint>

bool init_rtc();
void set_rtc_time(int16_t hour, int16_t min, int16_t sec, int16_t week_num);

#endif // RTC_H