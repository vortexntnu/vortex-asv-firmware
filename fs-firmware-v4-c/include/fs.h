#ifndef __FS_H__
#define __FS_H__

#ifndef F_CPU_
#define F_CPU_ 16000000UL
#endif

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#include <stdbool.h>

#define RC_OtA_KS       0x04
#define FS_BUTTON_KS    0x08

volatile bool RC_OtA_KS_STATUS      = false;
volatile bool FS_BUTTON_KS_STATUS   = false;

void fs_init(void);

#endif // __FS_H__