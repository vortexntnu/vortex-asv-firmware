#ifndef ESC_Driver_H
#define ESC_Driver_H

#include "gpio.h"
#include "i2c.h"

#define MIN_PULSE_WIDTH 1500
#define MID_PULSE_WIDTH 2000
#define MAX_PULSE_WIDTH 4200

void timer1_init(void);
void arm_esc(void);
void set_esc_speed(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4);
void disarm_esc(void);

#define ARMING_PWM 2000
#define STARTUP_DELAY 15000

#endif