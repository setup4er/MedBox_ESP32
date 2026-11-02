#ifndef PROTOCOL_H
#define PROTOCOL_H

/**
 * @file protocol.h
 * @date 2026-10-02
 * @description Protocol module file. CMD handle
 */
#include "Arduino.h"

void handle_cmd(const String& cmd); // Функция для обработки команд для работы с ESP32 и драйверами.

#endif // PROTOCOL_H