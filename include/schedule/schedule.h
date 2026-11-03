#ifndef SCHEDULE_H
#define SCHEDULE_H

/**
 * @file schedule.h
 * @date 2026-10-02
 * @description Расписание приёмов (7 дней × 4 сектора) в энергонезависимой памяти (NVS)
 */

#include <stdbool.h>
#include "types.h"

#define SCHEDULE_DAYS    7
#define SCHEDULE_SECTORS 4

// Инициализация расписания
void schedule_init();

// Загрузка и сохранение
void schedule_load();
void schedule_save();

// Установка времени (hour 0-23, min 0-59). Если hour=0 и min=0 - выключено.
void schedule_set(int day, int sector, int hour, int minute);

// Получение времени (возвращает true, если время задано)
bool schedule_get(int day, int sector, int* hour, int* minute);

// Проверка: не наступило ли сейчас время приема
bool schedule_should_alarm(const rtc_time_t* now);

// Получить номер сектора, который сработал
int schedule_current_sector();

#endif // SCHEDULE_H