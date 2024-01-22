#ifndef FS_H
#define FS_H

#include <Arduino.h>

bool fsLocked = true;
bool allSystemsGo;
const int analogLogicHighCutoff = 670;

int temperatureLevel = 0;
unsigned long currentTime = millis();
int startTime = 0;
int maxLevelLimit;
int minLevelLimit;
int temp;

void temperature_check();
void test_fs_trigger(byte input_pin, byte led_output_pin);
void set_main_output(bool main_output_value);
void test_sw_ks(byte input_pin);
void run();

#endif