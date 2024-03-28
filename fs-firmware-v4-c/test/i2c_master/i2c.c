#include "i2c.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <stdbool.h>
#include <util/delay.h>

void test_built_in_led(void) {
    for(int i = 0; i < 5; i++) {
        PORTB |= (1 << PB5);
        _delay_ms(100);
        PORTB &= ~(1 << PB5);
        _delay_ms(100);
    }
}

void TWI_init(void)
{
    // Enable master mode
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // Wait until TWI finish its current job (start condition)
    while (!(TWCR & (1 << TWINT)));
    // Set frequency to 100kHz
    TWBR = 0x47;
}

void TWI_start(void)
{
    // Enable start condition and clear interrupt flag
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // Wait until TWI finish its current job (start condition)
    while (!(TWCR & (1 << TWINT)));
}


void TWI_write(uint8_t address, uint8_t data)
{
    // send device address
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait until TWI finish its current job (Write operation)
    while (!(TWCR & (1 << TWINT)));
    // send data to slave
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait until TWI finish its current job (Write operation)
    while (!(TWCR & (1 << TWINT)));
    // Stop condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

int main(void)
{
    DDRB |= (1 << PB5);
    _delay_ms(5000);
    test_built_in_led();

    bool data_send = 0;
    

    while(1) {
        _delay_ms(750);

        TWI_write(0x20, data_send);
        data_send = !data_send;
    }   
}