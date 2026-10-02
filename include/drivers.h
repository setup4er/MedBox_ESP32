#ifndef DRIVERS_H
#define DRIVERS_H

/**
 * @file drivers.h
 * @date 2026-10-02
 * @description Агрегирующий заголовок всех драйверов
 *
 * Подключается в модули app и protocol для получения доступа ко всем драйверам.
 * При добавлении нового драйвера — добавить #include сюда.
 */

#include "drivers/dbg_led.h"
#include "drivers/rtc.h"
#include "drivers/servo.h"

#endif // DRIVERS_H