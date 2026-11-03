#include "protocol/protocol.h"

// System includes
#include <Arduino.h>

// Project includes
#include "drivers.h"
#include "comm/bluetooth.h"
#include "schedule/schedule.h"

void handle_cmd(const String& cmdRaw) {
    String cmd = cmdRaw;
    cmd.trim(); 

    Serial.print("[PROTO] RX: [");
    Serial.print(cmd);
    Serial.println("]"); 

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

    if (cmd.startsWith("GET_SCHED ")) {
        int d;
        char extra;
        if (sscanf(cmd.c_str(), "GET_SCHED %d %c", &d, &extra) != 1 || d < 1 || d > 7) {
            send_bluetooth_message("ERROR bad day");
            return;
        }
        
        int dayIndex = d - 1;
        char buf[48];
        char t1[6] = "00:00", t2[6] = "00:00", t3[6] = "00:00", t4[6] = "00:00";
        int h, m;

        if (schedule_get(dayIndex, 0, &h, &m)) snprintf(t1, sizeof(t1), "%02d:%02d", h, m);
        if (schedule_get(dayIndex, 1, &h, &m)) snprintf(t2, sizeof(t2), "%02d:%02d", h, m);
        if (schedule_get(dayIndex, 2, &h, &m)) snprintf(t3, sizeof(t3), "%02d:%02d", h, m);
        if (schedule_get(dayIndex, 3, &h, &m)) snprintf(t4, sizeof(t4), "%02d:%02d", h, m);

        snprintf(buf, sizeof(buf), "SCHED %d %s %s %s %s", d, t1, t2, t3, t4);
        send_bluetooth_message(buf);
        return;
    }

    if (cmd.startsWith("SET_SCHED ")) {
        int d, h1, m1, h2, m2, h3, m3, h4, m4;
        int parsed = sscanf(cmd.c_str(), "SET_SCHED %d %d:%d %d:%d %d:%d %d:%d",
                            &d, &h1, &m1, &h2, &m2, &h3, &m3, &h4, &m4);
        
        if (parsed != 9 || d < 1 || d > 7) {
            send_bluetooth_message("ERROR bad args");
            return;
        }
        
        int dayIndex = d - 1;
        schedule_set(dayIndex, 0, h1, m1);
        schedule_set(dayIndex, 1, h2, m2);
        schedule_set(dayIndex, 2, h3, m3);
        schedule_set(dayIndex, 3, h4, m4);
        schedule_save();

        send_bluetooth_message("OK");
        return;
    }

    if (cmd.startsWith("SERVO_MOVE ")) {
        int servoNum, sector;
        char extra;

        if (sscanf(cmd.c_str(), "SERVO_MOVE %d %d %c", &servoNum, &sector, &extra) != 2 ||
            servoNum < 1 || servoNum > 7 || sector < 0 || sector > 3) {
            send_bluetooth_message("ERROR bad args (servo 1-7, sector 0-3)");
            return;
        }

        servo_move_to_sector(servoNum, sector);
        send_bluetooth_message("OK");
        return;
    }

    if (cmd.startsWith("SERVO_SET_SPEED ")) {
        int speed;
        char extra;

        if (sscanf(cmd.c_str(), "SERVO_SET_SPEED %d %c", &speed, &extra) != 1 ||
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