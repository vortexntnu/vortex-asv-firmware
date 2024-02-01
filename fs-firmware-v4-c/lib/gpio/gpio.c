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
    ESC_PINS_DIR |= 0x78;      // Set PH3, PH4, PH5, PH6 as output (ESCx_PIN)
    FS_MCU_OUTPUT_DIR |= 0x10; // Set PB4 as output (FS_MCU_OUTPUT)
    MIXED_DIR1 |= 0x03;        // Set PG0, PG1 as output (DEBUG_MODE_BUTTON, LED_OVERTEMP)
    MIXED_DIR2 |= 0x78;        // Set PA3, PA4, PA5, PA6 as output (LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW)
    LEDS_DIR = 0xFF;           // Set all PC pins as output (LED_BENJAMIN_DEBUGGER, LED_RX_TO, LED_OtA_KS, LED_SW_KS, LED_HW_KS, LED_FS_LOCKED, LED_OM, LED_THRUSTERS_ARMED)

    // INPUT PINS:
    E_FUSES_DIR &= 0x80;    // Set all PL pins as input except PL7 (E_FUSE_ESCx, E_FUSE_RELAY, E_FUSE_HW_KS, E_FUSE_TEMP_SESNORS)
    MIXED_DIR1 &= 0xFA;     // Set PG2 and PG0 as input (PRECHARGE_RELAY1 and DEBUG_MODE_BUTTON)
    MIXED_DIR2 &= 0x7F;     // Set PA7 as input (PRECHARGE_RELAY2)
    SENSORS_DIR &= 0x01;    // Set all PF pins as input except PF0 (AMBIENT_TEMP_SENSOR_x, PCB_TEMP_SENSOR, ESC1_TEMP_SENSOR, ESC2_TEMP_SENSOR, ESC3_TEMP_SENSOR, ESC4_TEMP_SENSOR
    RC_ESC_PWM_DIR &= 0x0F; // Set PE4, PE5, PE6, PE7 as input (RC_ESCx_PWM)
    BUTTONS_DIR &= 0xFC;    // Set PK0 and PK1 as input (RC_OM, RC_THRUSTERS_ARMED)
    KS_DIR &= 0xF3;         // Set PD2 and PD3 as input (RC_OtA_KS, BUTTON_KS)

    /*
        The code above translates to the following, in Arduino C
        To use this, uncomment the #include <Arduino.h> in the header file on line 12.
        Then uncomment the arduino pin defines in the header file lines 152-204
        and comment the bit defines in the header file, lines 84-144:
            pinMode(ESC1_PIN, OUTPUT);
            pinMode(ESC2_PIN, OUTPUT);
            pinMode(ESC3_PIN, OUTPUT);
            pinMode(ESC4_PIN, OUTPUT);
            pinMode(FC_MCU_OUTPUT, OUTPUT);

            pinMode(LED_OVERTEMP, OUTPUT);
            pinMode(LED_BENJAMIN_DEBUGGER, OUTPUT);
            pinMode(LED_RX_TO, OUTPUT);
            pinMode(LED_OtA_KS, OUTPUT);
            pinMode(LED_SW_KS, OUTPUT);
            pinMode(LED_HW_KS, OUTPUT);
            pinMode(LED_FS_LOCKED, OUTPUT);
            pinMode(LED_OM, OUTPUT);
            pinMode(LED_THRUSTERS_ARMED, OUTPUT);

            pinMode(LED_RED, OUTPUT);
            pinMode(LED_GREEN, OUTPUT);
            pinMode(LED_BLUE, OUTPUT);
            pinMode(LED_YELLOW, OUTPUT);

            pinMode(RC_ESC1_PWM, INPUT);
            pinMode(RC_ESC2_PWM, INPUT);
            pinMode(RC_ESC3_PWM, INPUT);    // NP! Change the header file definition since it is defined as Not_An_Arduino_Pin
            pinMode(RC_ESC4_PWM, INPUT);    // NP! Change the header file definition since it is defined as Not_An_Arduino_Pin

            pinMode(E_FUSE_ESC1, INPUT);
            pinMode(E_FUSE_ESC2, INPUT);
            pinMode(E_FUSE_ESC3, INPUT);
            pinMode(E_FUSE_ESC4, INPUT);
            pinMode(E_FUSE_RELAY, INPUT);
            pinMode(E_FUSE_HW_KS, INPUT);
            pinMode(E_FUSE_TEMP_SESNORS, INPUT);

            pinMode(DEBUG_MODE_BUTTON, INPUT);

            pinMode(PRECHARGE_RELAY1, INPUT);
            pinMode(PRECHARGE_RELAY2, INPUT);

            pinMode(AMBIENT_TEMP_SENSOR_2, INPUT);
            pinMode(AMBIENT_TEMP_SENSOR_1, INPUT);
            pinMode(PCB_TEMP_SENSOR, INPUT);
            pinMode(ESC4_TEMP_SENSOR, INPUT);
            pinMode(ESC3_TEMP_SENSOR, INPUT);
            pinMode(ESC2_TEMP_SENSOR, INPUT);
            pinMode(ESC1_TEMP_SENSOR, INPUT);
            pinMode(RC_ARM_THRUSTERS, INPUT);
            pinMode(RC_OM, INPUT);
    */
}