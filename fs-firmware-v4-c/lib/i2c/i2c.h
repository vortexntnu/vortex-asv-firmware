#ifndef FS_Status_Light_H
#define FS_Status_Light_H

#include "gpio.h"
#include "util/twi.h"

#define I2C_ADDRESS 0x21

volatile uint8_t status = 0;
void twi_init(uint8_t sub_address);
int8_t i2c_listen();
int8_t i2c_transmit(char data);
void twi_match_read_slave(void);
void twi_read(void);
void twi_match_wrtie_slave(void);

#endif
