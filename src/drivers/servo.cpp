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

static int currentSector[7] = {0, 0, 0, 0, 0, 0, 0}; 
static int _speedDelay = 5;

void servo_set_speed(int delay_ms) {
    if (delay_ms < 1) delay_ms = 1;
    if (delay_ms > 500) delay_ms = 500;
    _speedDelay = delay_ms;
}

static void moveToAngle(Servo& servo, int targetAngle) {
    int currentAngle = servo.read();
    while (currentAngle != targetAngle) {
        currentAngle += (currentAngle < targetAngle) ? 1 : -1;
        servo.write(currentAngle);
        delay(_speedDelay);
    }
    delay(200); 
}

void servo_move_to_sector(int servoNum, int targetSector) {
    if (servoNum < 1 || servoNum > 7) return;
    if (targetSector < 0 || targetSector > 3) return;

    int index = servoNum - 1;

    if (currentSector[index] == targetSector) return;

    Servo& servo = *servos[index];

    int targetAngle = 0;
    if (targetSector == 0) targetAngle = 0;
    else if (targetSector == 1) targetAngle = 60;
    else if (targetSector == 2) targetAngle = 120;
    else if (targetSector == 3) targetAngle = 180;

    Serial.printf("[SERVO] Moving servo %d to sector %d (Angle: %d)\n", servoNum, targetSector, targetAngle);

    moveToAngle(servo, targetAngle);
    
    currentSector[index] = targetSector;
}

bool servo_init() {
    servo_set_speed(10); 

    for (int i = 0; i < 7; i++) {
        servos[i]->attach(servoPins[i]);
        servos[i]->write(0);
        currentSector[i] = 0; 

        delay(200);
    }

    Serial.println("[SERVO] Initialized successfully!");

    set_led_dbg_status(LED_OK);

    return true;
}