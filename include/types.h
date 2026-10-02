#ifndef TYPES_H
#define TYPES_H

/**
 * @file types.h
 * @date 2026-10-02
 * @description 
 */
#include <cstdint>

typedef struct {
    uint8_t hour;      // 0-23
    uint8_t minute;    // 0-59
    uint8_t second;    // 0-59
    uint8_t weekday;   // 0-6 (Вс-Пн-Вт-...-Сб)
} rtc_time_t;

#endif // TYPES_H



