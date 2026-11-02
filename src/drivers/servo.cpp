#include "drivers/servo.h"

#include "Arduino.h"
#include "ESP32Servo.h"

#include "config.h"
#include "drivers/dbg_led.h"

Servo SERVO_1, SERVO_2, SERVO_3, SERVO_4, SERVO_5, SERVO_6, SERVO_7;

static Servo* servos[] = {
    &SERVO_1,
    &SERVO_2,
    &SERVO_3,
    &SERVO_4,
    &SERVO_5,
    &SERVO_6,
    &SERVO_7
};

static const int servoPins[] = {
    SERVO_1_PWM_PIN,
    SERVO_2_PWM_PIN,
    SERVO_3_PWM_PIN,
    SERVO_4_PWM_PIN,
    SERVO_5_PWM_PIN,
    SERVO_6_PWM_PIN,
    SERVO_7_PWM_PIN
};

static bool servoStatus[7] = {false, false, false, false, false, false, false};
static int _speedDelay = 5;

void servo_set_speed(int delay_ms) {
    if (delay_ms < 1) delay_ms = 1;
    if (delay_ms > 500) delay_ms = 500;
    _speedDelay = delay_ms;
}

void toggleServo(int servoNum) {
    if (servoNum < 1 || servoNum > 7) return;

    int index = servoNum - 1;
    Servo& servo = *servos[index];

    servoStatus[index] = !servoStatus[index];

    int targetAngle = servoStatus[index] ? 180 : 0;
    int currentAngle = servo.read();

    while (currentAngle != targetAngle) {
        currentAngle += (currentAngle < targetAngle) ? 1 : -1;
        servo.write(currentAngle);
        delay(_speedDelay);
    }

    delay(500);
}

bool servo_init() {
    servo_set_speed(5);

    for (int i = 0; i < 7; i++) {
        servos[i]->attach(servoPins[i]);
        servos[i]->write(0);
        servoStatus[i] = false;

        delay(200);
    }

    Serial.println("[SERVO] Initialized successfully!");

    set_led_dbg_status(LED_OK);

    return true;
}