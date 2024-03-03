#ifndef ESC_Driver_H
#define ESC_Driver_H

#ifndef F_CPU_
#define F_CPU_ 16000000UL
#endif

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#define MIN_PULSE_WIDTH 1500
#define MID_PULSE_WIDTH 2000
#define MAX_PULSE_WIDTH 4200

void timers_init(void);
void arm_esc(void);
void set_esc_speed(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4);
void disarm_esc(void);

#define ARMING_PWM 2000
#define STARTUP_DELAY 15000

#endif