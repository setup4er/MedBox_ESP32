#ifndef RTC_H
#define RTC_H

/**
 * @file rtc.h
 * @date 2026-09-24
 * @description RTC Module header file
 */

#include "types.h"

bool rtc_get_time(rtc_time_t* out); // Функция геттер. Присваевает аргументу rtc_time_t поля: часы(24-формат), минуты, секунды, день недели (0-6) 
char *rtc_get_time(); //Возврат времени и день недели в текстовом формате

bool rtc_init(); // Инициализация временного модуля RTC DS1302
bool rtc_set_time(int16_t hour, int16_t min, int16_t sec, int16_t week_num); // Функция установки времени на модуль RTC DS1302

#endif // RTC_H