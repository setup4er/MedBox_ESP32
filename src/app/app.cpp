#include "app.h"

// System includes
#include <Arduino.h>

// Project headers
#include "config.h"
#include "drivers.h"
#include "comm/bluetooth.h"
#include "protocol/protocol.h"
#include "schedule/schedule.h"

static String _bluetoothMessage = "";
static bool _alarmActive = false;
static int _alarmDay = -1;
static int _alarmSector = -1;
static unsigned long _lastTimeCheck = 0;

void app_init(){
    led_init();
    schedule_init();
    bluetooth_init();
}

/*      Main cycle    */
void app_update(){
    if(has_bluetooth_message()){
        _bluetoothMessage = get_bluetooth_message();

        Serial.print("[APP] RX Message in app module: ");
        Serial.println(_bluetoothMessage);

        if (_bluetoothMessage.startsWith("SERVO_MOVE") && _alarmActive) {
            led_off(_alarmDay);
            _alarmActive = false;
        }

        handle_cmd(_bluetoothMessage);
    }

    // Автономная проверка времени (раз в секунду)
    if (millis() - _lastTimeCheck >= 1000) {
        _lastTimeCheck = millis();
        
        rtc_time_t now;
        if (rtc_get_time(&now)) {
            if (!_alarmActive) {
                if (schedule_should_alarm(&now)) {
                    _alarmActive = true;
                    _alarmSector = schedule_current_sector();
                    _alarmDay = (now.weekday == 0) ? 7 : now.weekday; // 1-Пн...7-Вс
                    
                    Serial.printf("[APP] ALARM! Day: %d, Sector: %d\n", _alarmDay, _alarmSector);
                    
                    led_on(_alarmDay);
                    servo_move_to_sector(_alarmDay, _alarmSector);
                    
                    char buf[32];
                    snprintf(buf, sizeof(buf), "ALARM %d %d", _alarmDay, _alarmSector);
                    send_bluetooth_message(buf);
                }
            }
        }
    }
}