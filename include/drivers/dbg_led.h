#ifndef DBG_LED_H
#define DBG_LED_H

/**
 * @file dbg_led.h
 * @date 2026-09-24
 * @description BOARD LED FILE
 */

void led_dbg_init(); // Инициализация отладочного светодиода
void set_led_dbg_status(int status); // Функция для установки статуса отладочного светодиода на плате

#endif // DBG_LED_H