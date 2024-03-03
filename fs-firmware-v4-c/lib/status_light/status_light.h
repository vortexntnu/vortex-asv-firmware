#ifndef FS_Status_Light_H
#define FS_Status_Light_H

#ifndef F_CPU_
#define F_CPU_ 16000000UL
#endif

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#include <stdint.h>

#define RGB_RED     0x40
#define RGB_GREEN   0x20
#define RGB_BLUE    0x10
#define RGB_YELLOW  0x08 

#define LED_THRUSTERS_ARMED     0x80
#define LED_SW_OM               0x40
#define LED_FS_LOCKED           0x20
#define LED_HW_KS_STATUS        0x10
#define LED_SW_KS_STATUS        0x08
#define LED_OtA_KS_STATUS       0x04
#define LED_RX_TIMEOUT          0x02
#define LED_BENJAMIN_DEBUGGER   0x01

#define LED_OVERTEMP_STATUS     0x02

void LED_init(void);
void set_rgby(uint8_t r, uint8_t g, uint8_t b, uint8_t y);
void test_rgby(void);
void test_leds(void);

#endif // FS_Status_Light_H
