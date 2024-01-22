/*
    GPIO.c - Source file for the GPIO library.
    This file contains the functions for the GPIO library.

    To add a new function, add it to the header file and then add the function here.

    To define a new pin, you need to find the port and pin number of the pin you want to use.
    The port and pin number can be found in the datasheet of the microcontroller.
    If that port is already in use, change the respective byte you want to use to 1 for output or 0 for input.
    If the port is not in use, define it in the header file and then add it here.
    You can follow the exact same syntax as the other defines but you need to change the address for the port.

    The defines are written with hexadecimal numbers because:
        1. The registers are written in hexadecimal numbers in the datasheet.
        2. It is less messy than having to do a logical shift every time you want to set a bit.

    However, feel free to use logical shift operations but make sure to use |= instead of = for output
    and &=~ instead of = for input. This is because you don't want to overwrite the other pins on the port.

    For more information on the logical shift operations, read the attached file "Logical Shift Operations.pdf".

    It is still possible to add pins with arduino pinMode() function alongside the existing ones
    However, it is not recommended to do so because it is not as efficient as using the registers directly.
    But if you really want to, make sure to check the port and pin number so that you don't overwrite
    Check the attached picture of the pinout of the Arduino Mega 2560 for the port and pin numbers.
    You also need to decomment the #include <Arduino.h> in the header file on line 14.

    PORTx, DDRx, and PINx can also be used instead. The defines in this library are just for convenience.
*/

#include "gpio.h"

void gpio_setup()
{
    // OUTPUT PINS:
    ESC_PINS_DIR |= 0x78;      // Set PH3, PH4, PH5, PH6 as output (ESC1, ESC2, ESC3, ESC4)
    FS_MCU_OUTPUT_DIR |= 0x10; // Set PB4 as output (FS_MCU_OUTPUT)
    MIXED_DIR1 |= 0x03;        // Set PG0, PG1 as output (DEBUG_MODE_BUTTON, LED_OVERTEMP)
    MIXED_DIR2 |= 0x78;        // Set PA3, PA4, PA5, PA6 as output (LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW)
    LEDS_DIR = 0xFF;           // Set all PC pins as output (LED_BENJAMIN_DEBUGGER, LED_RX_TO, LED_OtA_KS, LED_SW_KS, LED_HW_KS, LED_FS_LOCKED, LED_OM, LED_THRUSTERS_ARMED)

    // INPUT PINS:
    E_FUSES_DIR &= 0x80; // Set all PL pins as input except PL7 (E_FUSE_ESC1, E_FUSE_ESC2, E_FUSE_ESC3, E_FUSE_ESC4, E_FUSE_RELAY, E_FUSE_HW_KS, E_FUSE_TEMP_SESNORS)
    MIXED_DIR1 &= 0xFB;  // Set PG2 as input (PRECHARGE_RELAY1)
    MIXED_DIR2 &= 0x7F;  // Set PA7 as input (PRECHARGE_RELAY2)
    SENSORS_DIR &= 0x01; // Set all PF pins as input except PF0 (AMBIENT_TEMP_SENSOR_1, AMBIENT_TEMP_SENSOR_2, PCB_TEMP_SENSOR, ESC1_TEMP_SENSOR, ESC2_TEMP_SENSOR, ESC3_TEMP_SENSOR, ESC4_TEMP_SENSOR
    BUTTONS_DIR = 0x00;  // Set all PK pins as input (BUTTON_KS, RC_OM, RC_THRUSTERS_ARMED, RC_OtA_KS, RC_ESC1_PWM, RC_ESC2_PWM, RC_ESC3_PWM, RC_ESC4_PWM)

    /*
        The code above translates to the following, in Arduino C:
            pinMode(6, OUTPUT);
            pinMode(7, OUTPUT);
            pinMode(8, OUTPUT);
            pinMode(9, OUTPUT);
            pinMode(10, OUTPUT);

            pinMode(40, OUTPUT);
            pinMode(37, OUTPUT);
            pinMode(36, OUTPUT);
            pinMode(35, OUTPUT);
            pinMode(34, OUTPUT);
            pinMode(33, OUTPUT);
            pinMode(32, OUTPUT);
            pinMode(31, OUTPUT);
            pinMode(30, OUTPUT);
            pinMode(28, OUTPUT);
            pinMode(27, OUTPUT);
            pinMode(26, OUTPUT);
            pinMode(25, OUTPUT);

            pinMode(49, INPUT);
            pinMode(48, INPUT);
            pinMode(47, INPUT);
            pinMode(46, INPUT);
            pinMode(45, INPUT);
            pinMode(44, INPUT);
            pinMode(43, INPUT);

            pinMode(39, INPUT);
            pinMode(29, INPUT);

            pinMode(A1, INPUT);
            pinMode(A2, INPUT);
            pinMode(A3, INPUT);
            pinMode(A4, INPUT);
            pinMode(A5, INPUT);
            pinMode(A6, INPUT);
            pinMode(A7, INPUT);
            pinMode(A8, INPUT);
            pinMode(A9, INPUT);
            pinMode(A10, INPUT);
            pinMode(A11, INPUT);
            pinMode(A12, INPUT);
            pinMode(A13, INPUT);
            pinMode(A14, INPUT);
            pinMode(A15, INPUT);
    */
}