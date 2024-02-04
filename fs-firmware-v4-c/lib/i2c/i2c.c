
#include <util/twi.h>
#include <avr/interrupt.h>


#ifndef I2C_H_
#define I2C_H_



void i2c_init();
void i2c_receive();
void i2c_transmit();

#endif /* I2C_H_ */ 
