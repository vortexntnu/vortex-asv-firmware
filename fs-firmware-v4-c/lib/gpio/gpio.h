#ifndef gpio_H
#define gpio_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// #include <Arduino.h>

/*
    The following defines to the addresses of the registers for the pins
    are taken from the  Atmega 2560 datasheet.
    The datasheet can be found here:
    https://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf
    The datasheet is also included in the docs folder of this project.
    These defines are only for programming directly in C and not in Arduino C.
    PORT is for writing to the pin, DIR is for setting the pin as input or output, and PIN is for reading the pin.
*/
// The following uses PORTH, DDRH, and PINH addresses
#define ESC_PINS_PORT (*((volatile uint8_t *)0x102))
#define ESC_PINS_DIR (*((volatile uint8_t *)0x101))
#define ESC_PINS_PIN (*((volatile uint8_t *)0x100))

// The following uses PORTB, DDRB, and PINB addresses
#define FS_MCU_OUTPUT_PORT (*((volatile uint8_t *)0x25))
#define FS_MCU_OUTPUT_DIR (*((volatile uint8_t *)0x24))
#define FS_MCU_OUTPUT_PIN (*((volatile uint8_t *)0x23))

// The following uses PORTG, DDRG, and PING addresses
#define MIXED_PORT1 (*((volatile uint8_t *)0x34))
#define MIXED_DIR1 (*((volatile uint8_t *)0x33))
#define MIXED_PIN1 (*((volatile uint8_t *)0x32))

// The following uses PORTA, DDRA, and PINA addresses
#define MIXED_PORT2 (*((volatile uint8_t *)0x22))
#define MIXED_DIR2 (*((volatile uint8_t *)0x21))
#define MIXED_PIN2 (*((volatile uint8_t *)0x20))

// The following uses PORTC, DDRC, and PINC addresses
#define LEDS_PORT (*((volatile uint8_t *)0x28))
#define LEDS_DIR (*((volatile uint8_t *)0x27))
#define LEDS_PIN (*((volatile uint8_t *)0x26))

// The following uses PORTL, DDRL, and PINL addresses
#define E_FUSES_PORT (*((volatile uint8_t *)0x10B))
#define E_FUSES_DIR (*((volatile uint8_t *)0x10A))
#define E_FUSES_PIN (*((volatile uint8_t *)0x109))

// The following uses PORTF, DDRF, and PINF addresses
#define SENSORS_PORT (*((volatile uint8_t *)0x31))
#define SENSORS_DIR (*((volatile uint8_t *)0x30))
#define SENSORS_PIN (*((volatile uint8_t *)0x2F))

// The following uses PORTK, DDRK, and PINK addresses
#define BUTTONS_PORT (*((volatile uint8_t *)0x108))
#define BUTTONS_DIR (*((volatile uint8_t *)0x107))
#define BUTTONS_PIN (*((volatile uint8_t *)0x106))

// The following uses PORTE, DDRE, and PINE addresses
#define RC_ESC_PWM_PORT (*((volatile uint8_t *)0x2E))
#define RC_ESC_PWM_DIR (*((volatile uint8_t *)0x2D))
#define RC_ESC_PWM_PIN (*((volatile uint8_t *)0x2C))

// The following uses PORTD, DDRD, and PIND addresses
#define KS_PORT (*((volatile uint8_t *)0x2B))
#define KS_DIR (*((volatile uint8_t *)0x2A))
#define KS_PIN (*((volatile uint8_t *)0x29))

/*--------------------------------------------------*/

/*
    The following defines are for the bit number of the associated pin on the port.
    The numbers are not unique because each port has 8 pins represented by a byte.
    Thus ESC1 for example is on pin 3 of port H, which is the 3rd bit of the byte.
    Whilst LED_YELLOW is on pin 3 of port A, which is also the 3rd bit of the byte.
    NP! The numbers start at 0 and go up to 7.
    P.S: You will find the respective arduino pin number under these defines commented out.
*/
// Port H
#define ESC1_PIN 3
#define ESC2_PIN 4
#define ESC3_PIN 5
#define ESC4_PIN 6

// Port B
#define FS_MCU_OUTPUT 4

// Port G
#define DEBUG_MODE_BUTTON 0
#define LED_OVERTEMP 1
#define PRECHARGE_RELAY1 2

// Port A
#define PRECHARGE_RELAY2 7
#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 4
#define LED_YELLOW 3

// Port C
#define LED_BENJAMIN_DEBUGGER 0
#define LED_RX_TO 1
#define LED_OtA_KS 2
#define LED_SW_KS 3
#define LED_HW_KS 4
#define LED_FS_LOCKED 5
#define LED_OM 6
#define LED_THRUSTERS_ARMED 7

// Port L
#define E_FUSE_ESC1 0
#define E_FUSE_ESC2 1
#define E_FUSE_ESC3 2
#define E_FUSE_ESC4 3
#define E_FUSE_RELAY 4
#define E_FUSE_HW_KS 5
#define E_FUSE_TEMP_SESNORS 6

// Port F
#define AMBIENT_TEMP_SENSOR_1 1
#define AMBIENT_TEMP_SENSOR_2 2
#define PCB_TEMP_SENSOR 3
#define ESC1_TEMP_SENSOR 4
#define ESC2_TEMP_SENSOR 5
#define ESC3_TEMP_SENSOR 6
#define ESC4_TEMP_SENSOR 7

// Port K
#define RC_OM 1
#define RC_ARM_THRUSTERS 0

// Port D
#define BUTTON_KS 3
#define RC_OtA_KS 2

// Port E
#define RC_ESC1_PWM 4
#define RC_ESC2_PWM 5
#define RC_ESC3_PWM 6
#define RC_ESC4_PWM 7
/*--------------------------------------------------*/
/*

    // The following defines are for the arduino pin number of the associated pin.
    // Use these defines if you are programming in Arduino C.
    // NP! RC_ESC3_PWM and RC_ESC4_PWM are not connected to the Arduino Mega 2560.

    #define RC_ESC1_PWM 2
    #define RC_ESC2_PWM 3
    #define RC_ESC3_PWM Not_An_Arduino_Pin  // NP! Must be changed to an arduino pin if used
    #define RC_ESC4_PWM Not_An_Arduino_Pin  // NP! Must be changed to an arduino pin if used

    #define ESC1_PIN 6
    #define ESC2_PIN 7
    #define ESC3_PIN 8
    #define ESC4_PIN 9

    #define FC_MCU_OUTPUT 10

    #define E_FUSE_ESC1 49
    #define E_FUSE_ESC2 48
    #define E_FUSE_ESC3 47
    #define E_FUSE_ESC4 46
    #define E_FUSE_RELAY 45
    #define E_FUSE_HW_KS 44
    #define E_FUSE_TEMP_SESNORS 43

    #define RC_OtA_KS 19
    #define BUTTON_KS 18

    #define DEBUG_MODE_BUTTON 41
    #define LED_OVERTEMP 40

    #define LED_BENJAMIN_DEBUGGER 37
    #define LED_RX_TO 36
    #define LED_OtA_KS 35
    #define LED_SW_KS 34
    #define LED_HW_KS 33
    #define LED_FS_LOCKED 32
    #define LED_OM 31
    #define LED_THRUSTERS_ARMED 30

    #define PRECHARGE_RELAY1 39
    #define PRECHARGE_RELAY2 29

    #define LED_RED 28
    #define LED_GREEN 27
    #define LED_BLUE 26
    #define LED_YELLOW 25

    #define RC_OM A9
    #define RC_ARM_THRUSTERS A8

    #define ESC1_TEMP_SENSOR A7
    #define ESC2_TEMP_SENSOR A6
    #define ESC3_TEMP_SENSOR A5
    #define ESC4_TEMP_SENSOR A4
    #define PCB_TEMP_SENSOR A3
    #define AMBIENT_TEMP_SENSOR_1 A2
    #define AMBIENT_TEMP_SENSOR_2 A1
*/
/*--------------------------------------------------*/
#define HIGH 1
#define LOW 0

void gpio_setup();

#endif