#ifndef __I2C_H__
#define __I2C_H__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#include <stdbool.h>
#include <stdint.h>

//#define TWI_ENABLE_PULLUPS
//#define SLAVE_RESET_TWI()  (TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE))

//#define TWI_TX_BUFFER_SIZE 6
//#define TWI_RX_BUFFER_SIZE 4

//extern volatile uint8_t    TWI_TX_BUFFER[TWI_TX_BUFFER_SIZE];
//extern volatile uint16_t   TWI_RX_BUFFER[TWI_RX_BUFFER_SIZE];

//extern volatile uint8_t TWI_TX_BUFFER_INDEX;
//extern volatile uint8_t TWI_RX_BUFFER_INDEX;

//uint8_t IS_HIGH_BYTE;

/*****************************/
/* TWI Status Codes          */

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

/*****************************/


//extern volatile uint16_t    thrusters_values_g[TWI_RX_BUFFER_SIZE];
//extern volatile uint8_t     sensor_values_g[TWI_TX_BUFFER_SIZE];
extern volatile uint8_t     test_tx_one_byte;
extern volatile uint8_t     test_rx_one_byte;

void TWI_init(uint8_t address);
//void PARSE_DATA(uint8_t received_byte, volatile uint8_t *index, uint8_t *is_high_byte);
void test_built_in_led(void);


#endif // __I2C_H__