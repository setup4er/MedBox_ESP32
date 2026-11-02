#include "protocol/protocol.h"

// System includes
#include <Arduino.h>

// Project includes
#include "drivers.h"
#include "comm/bluetooth.h"

void handle_cmd(const String& cmd) {
    Serial.print("[PROTO] RX: ");
    Serial.println(cmd);

    if (cmd == "GET_TIME") {
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
        int parsed = sscanf(cmd.c_str(), "SET_TIME %d:%d:%d %d",
                            &h, &m, &s, &wd);

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

    if (cmd.startsWith("SERVO_TOGGLE ")) {
        int servoNum;
        char extra;

        if (sscanf(cmd.c_str(), "SERVO_TOGGLE %d %c",
                   &servoNum, &extra) != 1 ||
            servoNum < 1 || servoNum > 7) {
            send_bluetooth_message("ERROR bad servo number (1-7)");
            return;
        }

        toggleServo(servoNum);
        send_bluetooth_message("OK");
        return;
    }

    if (cmd.startsWith("SERVO_SET_SPEED ")) {
        int speed;
        char extra;

        if (sscanf(cmd.c_str(), "SERVO_SET_SPEED %d %c",
                   &speed, &extra) != 1 ||
            speed < 1 || speed > 500) {
            send_bluetooth_message("ERROR speed must be 1-500");
            return;
        }

        servo_set_speed(speed);
        send_bluetooth_message("OK");
        return;
    }

    send_bluetooth_message("ERROR unknown cmd");
}