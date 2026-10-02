#ifndef PROTOCOL_H
#define PROTOCOL_H

/**
 * @file protocol.h
 * @date 2026-10-02
 * @description Protocol module file. CMD handle
 */
#include "Arduino.h"

void handle_cmd(const String& cmd);

#endif // PROTOCOL_H