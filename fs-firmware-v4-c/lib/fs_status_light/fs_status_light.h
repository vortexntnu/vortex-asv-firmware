#ifndef FS_Status_Light_H
#define FS_Status_Light_H

#include "gpio.h"

void set_rgby(bool r, bool g, bool b, bool y);
void test_24v_status();
void test_leds();
void run();
void status_lights();

#endif
