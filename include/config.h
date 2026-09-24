#pragma once

// DBG Led
 #define DBG_LED 2

// Led statuses
#define LED_OK 0
#define LED_ERR -1

// RTC DS1302 pins
#define RTC_RST_PIN   18
#define RTC_CLK_PIN    5
#define RTC_DAT_PIN   17

// NimBLE
#define BLE_DEVICE_NAME "MedBox"
#define BLE_UUID_SERVICE "a63c22c9-f961-46c4-9ef2-779f6b92fbb5"
#define BLE_UUID_RX_CHAR "98637278-77c9-4af7-927a-eedac7684cc1"
#define BLE_UUID_TX_CHAR "83ab3918-c277-4c70-a17f-0476eb17ab09"