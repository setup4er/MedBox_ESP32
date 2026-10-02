#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/**
 * @file bluetooth.h
 * @date 2026-09-25
 * @description Bluetooth module headerfile
 */
#include "Arduino.h"


void bluetooth_init();

bool send_bluetooth_message(String msg);
String get_bluetooth_message();
bool has_bluetooth_message();

#endif // BLUETOOTH_H