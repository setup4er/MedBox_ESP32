#ifndef LED_H
#define LED_H

/**
 * @file led.h
 * @date 2026-10-03
 * @description Драйвер адресной ленты WS2812B (7 светодиодов)
 */

#include <stdbool.h>

// Инициализация ленты
void led_init();

// Зажечь светодиод определенного дня (day: 1-7)
void led_on(int day);

// Потушить светодиод определенного дня (day: 1-7)
void led_off(int day);

// Потушить все светодиоды
void led_off_all();

// Обновить состояние (вызывается в цикле, если нужно мигание)
void led_update();

#endif // LED_H