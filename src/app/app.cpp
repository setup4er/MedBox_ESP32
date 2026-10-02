#include "app.h"

// System includes
#include <Arduino.h>

// Project headers
#include "config.h"
#include "drivers/dbg_led.h"
#include "comm/bluetooth.h"

static String _bluetoothMessage = "";

void app_init(){
    bluetooth_init();
}

/*      Main cycle    */
void app_update(){
    if(has_bluetooth_message()){
        _bluetoothMessage = get_bluetooth_message();
        Serial.print("[APP] RX Message in app module: ");
        Serial.println(_bluetoothMessage);
        // handle_cmd();
    }
}