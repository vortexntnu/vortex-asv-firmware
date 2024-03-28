#include "i2c.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <util/delay.h>
#include <stdio.h>

volatile uint8_t test_tx_one_byte = 0;
volatile uint8_t test_rx_one_byte = 0;

//volatile uint8_t thrusters_values_g[TWI_RX_BUFFER_SIZE] = {500, 500, 500, 500};
//volatile uint8_t sensor_values_g[TWI_TX_BUFFER_SIZE] = {0, 0, 0, 0, 0, 0};
//volatile uint8_t test_tx_one_byte = 0;

//volatile uint8_t TWI_TX_BUFFER_INDEX = 0;
//volatile uint8_t TWI_RX_BUFFER_INDEX = 0;

void TWI_init(uint8_t address) {
    TWAR = (address << 1);
    TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE);

    //IS_HIGH_BYTE = 1;
}

/*
void PARSE_DATA(uint8_t received_byte, volatile uint8_t *index, uint8_t *is_high_byte)
{
    static uint16_t received_2_bytes = 0;
    
    if(*is_high_byte)
    {
        received_2_bytes = received_byte << 8;
        *is_high_byte = 0;
    }
    else
    {
        received_2_bytes |= received_byte;
        // thrusters_values_g[*index] = received_2_bytes;
        *is_high_byte = 1;
        *index++;
    }
}
*/

void test_built_in_led(void) {
    for(int i = 0; i < 5; i++) {
        PORTB |= (1 << PB7);
        _delay_ms(100);
        PORTB &= ~(1 << PB7);
        _delay_ms(100);
    }
}

ISR(TWI_vect) {
    uint8_t status = TWSR & 0xF8;

    switch(status)
    {  
        case TWI_SR_DATA_ACK:
            test_rx_one_byte = TWDR;
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
            break;

        case TWI_SR_SLA_ACK:
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
            break;

        case TWI_ST_DATA_ACK:
            TWDR = test_tx_one_byte;
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
            break;

        default:
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
            break;         
    }
}

int main() {
    TWI_init(0x20);
    sei();

    _delay_ms(5000);

    DDRB |= (1 << PB7);

    test_built_in_led();

    while(1) {
        _delay_ms(100);
        if(test_rx_one_byte == 0) {
            PORTB |= (1 << PB7);
            test_tx_one_byte = 1;
        } else {
            PORTB &= ~(1 << PB7);
            test_tx_one_byte = 0;
        }
    }
}