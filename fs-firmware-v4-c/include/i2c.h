/**
 * @file i2c.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */



#ifndef __I2C_H__
#define __I2C_H__

#ifndef F_CPU_
#define F_CPU_ 16000000UL
#endif

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#include <stdint.h>

// Buffer sizes for TWI communication
#define TWI_TX_BUFFER_SIZE 6
#define TWI_RX_BUFFER_SIZE 4

// Global buffers
extern volatile uint8_t     TWI_TX_BUFFER[TWI_TX_BUFFER_SIZE];
extern volatile uint16_t    TWI_RX_BUFFER[TWI_RX_BUFFER_SIZE];

// Buffer indexes
volatile int TWI_TX_BUFFER_INDEX;
volatile int TWI_RX_BUFFER_INDEX;

#define SLAVE_ADDRESS 0x20

uint8_t IS_HIGH_BYTE;

// Status Codes

    #define TWI_SR_SLA_ACK              0x60

    #define TWI_SR_ARB_LOST_SLA_ACK     0x68
    #define TWI_SR_GCALL_ACK            0x70
    #define TWI_SR_ARB_LOST_GCALL_ACK   0x78
    
    #define TWI_SR_DATA_ACK             0x80
    #define TWI_SR_DATA_NACK            0x88
    #define TWI_SR_GCALL_DATA_ACK       0x90
    #define TWI_SR_GCALL_DATA_NACK      0x98
    #define TWI_SR_STOP_RS_RECOGNIZED   0xA0

    #define TWI_ST_SLA_ACK              0xA8
    #define TWI_ST_ARB_LOST_SLA_ACK     0xB0
    #define TWI_ST_DATA_ACK             0xB8
    #define TWI_ST_DATA_NACK            0xC0
    #define TWI_ST_LAST_DATA_ACK        0xC8

    #define TWI_BUS_ERROR               0x00
/*-------------------------------------------*/

#define SLAVE_RESET_TWI()  (TWCR = 0b01000101)

// Global variables
extern volatile uint16_t thrusters_values_g[TWI_RX_BUFFER_SIZE];
volatile uint8_t sensor_values_g[TWI_TX_BUFFER_SIZE];

// Function Prototypes
void TWI_init(void);
void PARSE_DATA(uint8_t received_byte, volatile uint8_t *index, uint8_t *is_high_byte);

#endif // __I2C_H__
