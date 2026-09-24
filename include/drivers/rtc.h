#ifndef RTC_H
#define RTC_H

/**
 * @file rtc.h
 * @date 2026-09-24
 * @description RTC Module header file
 */
#include <cstdint>

typedef struct {
    uint8_t hour;      // 0-23
    uint8_t minute;    // 0-59
    uint8_t second;    // 0-59
    uint8_t weekday;   // 0-6 (Вс-Пн-Вт-...-Сб)
} rtc_time_t;

bool rtc_get_time(rtc_time_t* out); // Функция геттер. Присваевает аргументу rtc_time_t поля: часы(24-формат), минуты, секунды, день недели (0-6) 
char *rtc_get_time(); //Возврат времени и день недели в текстовом формате

bool rtc_init(); // Инициализация временного модуля RTC DS1302
void rtc_set_time(int16_t hour, int16_t min, int16_t sec, int16_t week_num); // Функция установки времени на модуль RTC DS1302

#endif // RTC_H