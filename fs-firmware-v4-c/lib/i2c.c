/*
    * File:   i2c.c
    * Version: 1.0
    * Organisation: Vortex NTNU
    * Created on:  2023-11-20
    * Last update: 2024-03-03
    * Tested on: N/A
    * 
    * Description:  This file implements the TWI interface for the slave device.
    *               for the atmega2560 microcontroller.           
*/

#include <i2c.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

TWI_TX_BUFFER_INDEX = 0;
TWI_RX_BUFFER_INDEX = 0;

IS_HIGH_BYTE = 1;

thrusters_values_g = {500, 500, 500, 500};
sensor_values_g = {0, 0, 0, 0, 0, 0};

// Initialise the TWI interface
void TWI_init(void)
{
    // Set slave address and enable global call 
    TWAR = (SLAVE_ADDRESS << 1) | (1 << TWGCE);

    // Enable TWI and TWI ACK  
    TWCR = (1 << TWEN) | (1 << TWEA);
    TWCR &= ~(1 << TWSTA) & ~(1 << TWSTO) & ~(1 << TWWC) & ~(1 << TWINT);
}

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
        thrusters_values_g[*index] = received_2_bytes;
        *is_high_byte = 1;
        *index++;
    }
}

// TWI interrupt service routine 
ISR(TWI_vect)
{
    // Status register
    uint8_t status = TWSR & 0xF8;

    // If the slave address is received, check the status
    switch (status)
    {
        // If master sends a write request, read the data and store it in the thrusters_values_g array
        case TWI_SR_DATA_ACK:
            PARSE_DATA(TWDR, &TWI_RX_BUFFER_INDEX, &IS_HIGH_BYTE);
            // thrusters_values_g[TWI_RX_BUFFER_INDEX++] = TWDR;
            if(TWI_RX_BUFFER_INDEX >= TWI_RX_BUFFER_SIZE)
             {
                TWI_RX_BUFFER_INDEX = 0;
             }
             SLAVE_RESET_TWI();
            break;

        // If the master sends a read request, send the sensor values
        case TWI_ST_SLA_ACK:
            TWI_TX_BUFFER_INDEX = 0;
            TWDR = sensor_values_g[TWI_TX_BUFFER_INDEX++];
            SLAVE_RESET_TWI();
            break;

        // If a data byte is transmitted, send the next byte, if available
        case TWI_ST_DATA_ACK:
            if(TWI_TX_BUFFER_INDEX < TWI_TX_BUFFER_SIZE)
            {
                TWDR = sensor_values_g[TWI_TX_BUFFER_INDEX++];
            }
            else
            {
                TWDR = 0xFF; 
            }
            SLAVE_RESET_TWI();
            break;

        // If the last byte is transmitted, end the TWI communication
        case TWI_ST_LAST_DATA_ACK:
            SLAVE_RESET_TWI();
            break;

        // If the master sends a stop condition, end the TWI communication
        case TWI_ST_DATA_NACK:
            SLAVE_RESET_TWI();
            break;

        // If the bus error occurs, reset the TWI interface
        case TWI_BUS_ERROR:
            TWCR = (1 << TWSTO) | (1 << TWEN);
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
            break;

        // Otherwise, enable TWI and TWI ACK
        default:  
            TWCR = (1 << TWEN) | (1 << TWEA);
            TWCR &= ~(1 << TWSTA) & ~(1 << TWSTO) & ~(1 << TWWC) & ~(1 << TWINT);
            break;     
    }
}

