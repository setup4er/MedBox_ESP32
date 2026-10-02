#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/**
 * @file bluetooth.h
 * @date 2026-09-25
 * @description Bluetooth module headerfile
 */
#include "Arduino.h"


void bluetooth_init(); // Инициализация NimBLE. Название отображаемого BLE устройства, UUID сервиса и характеристик представлены в config.h.

void send_bluetooth_message(const String &msg); // Отправка сообщения клиенту по TX (NOTIFY, READ) характеристике.
String get_bluetooth_message(); // Получение _rxBuffer сообщения от клиента. Используется с функцией has_bluetooth_message() во избежания получения пустой строки.
bool has_bluetooth_message(); // Получение булевого значения о наличии сообщения о клиенте.

#endif // BLUETOOTH_H