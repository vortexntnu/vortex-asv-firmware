#ifndef ESC_Driver_H
#define ESC_Driver_H

#include <Servo.h>
#include <Wire.h>
#include <Arduino.h>

#define ESC_PIN1 6
#define ESC_PIN2 7
#define ESC_PIN3 8
#define ESC_PIN4 9

#define ARMING_PWM 1500
#define STARTUP_DELAY 15000

#define I2C_ADDRESS 0x21

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

void arm_thrusters();
void disarm_thrusters();
int drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4);
void receive_i2c_message(int bytes);
void esc_setup();

bool fs_status(int status);
int om_status(int status);

#endif