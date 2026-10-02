#include "protocol/protocol.h"

// System includes
#include <Arduino.h>

// Project includes
#include "drivers/rtc.h"
#include "comm/bluetooth.h"

void handle_cmd(const String& cmd) {
    Serial.print("[PROTO] RX: ");
    Serial.println(cmd);

    if (cmd == "GET_TIME") {
        char buf[64];
        snprintf(buf, sizeof(buf), "TIME %s", rtc_get_time());
        send_bluetooth_message(buf);
        return;
    }
    
    if (cmd == "GET_TIME_ARR") {
    rtc_time_t t;
    if (!rtc_get_time(&t)) {
        send_bluetooth_message("ERROR rtc_get_time");
        return;
    }

    char buf[48];
    snprintf(buf, sizeof(buf), "TIME_ARR %d,%d,%d,%d",
             t.hour, t.minute, t.second, t.weekday);
    send_bluetooth_message(buf);
    return;
}

    if (cmd.startsWith("SET_TIME ")) {
        int h, m, s, wd;
        int parsed = sscanf(cmd.c_str(), "SET_TIME %d:%d:%d %d", &h, &m, &s, &wd);
        if (parsed != 4) {
            send_bluetooth_message("ERROR bad args");
            return;
        }

        if (rtc_set_time(h, m, s, wd)) {
            send_bluetooth_message("OK");
        } else {
            send_bluetooth_message("ERROR rtc_set_time");
        }
        return;
    }

    send_bluetooth_message("ERROR unknown cmd");
}