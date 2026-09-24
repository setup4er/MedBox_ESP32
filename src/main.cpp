#include <Arduino.h>

#include "app/app.h"
#include "board/board.h"


void setup() {
  Serial.begin(115200);

  board_init();
  Serial.print("[SYS] BOARD initialized successfully !\n");
  
  app_init();
  Serial.print("[SYS] APP initialized successfully !\n");
}

void loop() {
  app_update();
}