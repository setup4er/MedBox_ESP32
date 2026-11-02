#ifndef SERVO_H
#define SERVO_H

/**
 * @file servo.h
 * @date 2026-09-24
 * @description Servo module file
 */
#include "ESP32Servo.h"

bool servo_init();
void toggleServo(int servoNum); // Функция для изменения угла сервопривода. &servo - ссылка на экземпляр. targetAngle - угол.
void servo_set_speed(int delay_ms); // Функция для установки скорости сервоприводов в ms.
#endif // SERVO_H