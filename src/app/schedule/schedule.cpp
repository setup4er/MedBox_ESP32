#include "schedule/schedule.h"

// System includes
#include <Arduino.h>
#include <Preferences.h>

static Preferences _prefs;
static uint16_t _times[SCHEDULE_DAYS][SCHEDULE_SECTORS];
static int _lastAlarmSector = -1;

void schedule_init() {
    _prefs.begin("medbox_sched", false);
    schedule_load();
    Serial.println("[SCHEDULE] Initialized");
}

void schedule_load() {
    for (int d = 0; d < SCHEDULE_DAYS; d++) {
        for (int s = 0; s < SCHEDULE_SECTORS; s++) {
            String key = "d" + String(d) + "s" + String(s);
            _times[d][s] = _prefs.getUShort(key.c_str(), 0);
        }
    }
}

void schedule_save() {
    for (int d = 0; d < SCHEDULE_DAYS; d++) {
        for (int s = 0; s < SCHEDULE_SECTORS; s++) {
            String key = "d" + String(d) + "s" + String(s);
            _prefs.putUShort(key.c_str(), _times[d][s]);
        }
    }
}

void schedule_set(int day, int sector, int hour, int minute) {
    if (day < 0 || day >= SCHEDULE_DAYS) return;
    if (sector < 0 || sector >= SCHEDULE_SECTORS) return;
    if (hour < 0 || hour > 23) return;
    if (minute < 0 || minute > 59) return;

    // Сохраняем как HMM (например, 830 = 8:30)
    _times[day][sector] = (hour * 100) + minute;
}

bool schedule_get(int day, int sector, int* hour, int* minute) {
    if (day < 0 || day >= SCHEDULE_DAYS) return false;
    if (sector < 0 || sector >= SCHEDULE_SECTORS) return false;

    uint16_t t = _times[day][sector];
    if (t == 0) return false;

    if (hour)   *hour   = t / 100;
    if (minute) *minute = t % 100;
    return true;
}

bool schedule_should_alarm(const rtc_time_t* now) {
    if (!now) return false;

    // В ESP32 библиотеке iarduino_RTC: 0 - воскресенье, 1 - понедельник.
    // Переводим в индекс массива: 0 - понедельник, ..., 6 - воскресенье.
    int dayIndex = (now->weekday == 0) ? 6 : now->weekday - 1;

    for (int s = 0; s < SCHEDULE_SECTORS; s++) {
        int h, m;
        if (!schedule_get(dayIndex, s, &h, &m)) continue;

        if (now->hour == h && now->minute == m && now->second < 5) {
            _lastAlarmSector = s;
            return true;
        }
    }
    return false;
}

int schedule_current_sector() {
    return _lastAlarmSector;
}