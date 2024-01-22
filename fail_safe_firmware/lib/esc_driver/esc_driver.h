#ifndef ESC_Driver_H
#define ESC_Driver_H

#include "gpio.h"
#include <Servo.h>
#include <Wire.h>

#define ARMING_PWM 1500
#define STARTUP_DELAY 15000
#define FS_CHECK_INTERVAL 500

unsigned long FS_TIMER_LAST_CHECK = 0;
bool IS_ARMED = false;

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

namespace ESC_Driver
{
    void setup();
    void run();
    void arm();
    void disarm();
    int drive(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4);
    void receive_message(int bytes);
    bool fs_status(int status);
    int om_status(int status);
} // namespace name

#endif