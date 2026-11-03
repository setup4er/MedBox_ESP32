#include "drivers/led.h"

// System includes
#include <Arduino.h>
#define FASTLED_ESP32_I2S // Ускоряет работу ленты на ESP32
#include <FastLED.h>

// Project includes
#include "config.h"

#define NUM_LEDS 7
static CRGB leds[NUM_LEDS];

void led_init() {
    // Инициализируем ленту на пине WS2812B_PIN
    FastLED.addLeds<WS2812B, WS2812B_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50); // Яркость 0-255 (50 - чтобы не слепило)
    led_off_all();
    Serial.println("[LED] Initialized successfully!");
}

void led_on(int day) {
    if (day < 1 || day > 7) return;
    int index = day - 1;
    
    // Можно задать цвет в зависимости от дня, или всем один
    leds[index] = CRGB::Green; 
    FastLED.show();
    Serial.printf("[LED] Turned ON led for day %d\n", day);
}

void led_off(int day) {
    if (day < 1 || day > 7) return;
    int index = day - 1;
    
    leds[index] = CRGB::Black;
    FastLED.show();
    Serial.printf("[LED] Turned OFF led for day %d\n", day);
}

void led_off_all() {
    FastLED.clear();
    FastLED.show();
}

void led_update() {
    // Здесь можно реализовать мигание, если нужно
}