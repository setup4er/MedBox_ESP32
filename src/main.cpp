#include <Arduino.h>

#include "app/app.h"
#include "board/board.h"


void setup() {
  Serial.begin(115200);

  init_board();
  Serial.print("[SYS] BOARD initialized successfully !\n");
  
  init_app();
  Serial.print("[SYS] APP initialized successfully !\n");
}

void loop() {
  app_update();
}