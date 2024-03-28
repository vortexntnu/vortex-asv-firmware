#ifndef __I2C_H__
#define __I2C_H__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdint.h>

#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif

void test_built_in_led(void);
void TWI_init();
void TWI_start();

// Function to send data to a slave of address 'address'
void TWI_write(uint8_t address, uint8_t data);

#endif // __I2C_H__

