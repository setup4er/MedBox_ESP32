#pragma once

// DBG Led pin
 #define DBG_LED 2

// Led statuses
#define LED_OK 0
#define LED_ERR -1

// RTC DS1302 pins
#define RTC_RST_PIN   19
#define RTC_CLK_PIN   18
#define RTC_DAT_PIN   21

// MG90S Servo pins
#define SERVO_1_PWM_PIN 13
#define SERVO_2_PWM_PIN 12
#define SERVO_3_PWM_PIN 14
#define SERVO_4_PWM_PIN 27
#define SERVO_5_PWM_PIN 26
#define SERVO_6_PWM_PIN 25
#define SERVO_7_PWM_PIN 33

// WS2812B
#define WS2812B_PIN 32
#define WS2812B_NUM_LEDS 7

// NimBLE
#define BLE_DEVICE_NAME "MedBox"
#define BLE_UUID_SERVICE "a63c22c9-f961-46c4-9ef2-779f6b92fbb5"
#define BLE_UUID_RX_CHAR "98637278-77c9-4af7-927a-eedac7684cc1"
#define BLE_UUID_TX_CHAR "83ab3918-c277-4c70-a17f-0476eb17ab09"