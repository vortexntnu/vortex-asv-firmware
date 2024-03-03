/*
    * File:   i2c.c
    * Version: 1.0
    * Author: Ibrahim F. Abdalaal
    * Organisation: Vortex NTNU
    * Created on:  2023-11-20
    * Last update: 2024-03-03
    * Tested on: N/A
    * 
    * Description:  This file implements the TWI interface for the slave device.
    *               for the atmega2560 microcontroller.           
*/
#include "i2c.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

// Initialise the TWI interface
void TWI_init(void)
{
    // Set slave address and enable global call 
    TWAR = (SLAVE_ADDRESS << 1) | (1 << TWGCE);

    // Enable TWI and TWI ACK  
    TWCR = (1 << TWEN) | (1 << TWEA);
    TWCR &= ~(1 << TWSTA) & ~(1 << TWSTO) & ~(1 << TWWC) & ~(1 << TWINT);
}

// TWI interrupt service routine 
ISR(TWI_vect)
{
    // Status register
    uint8_t status = TWSR & 0xF8;

    // If the slave address is received, check the status
    switch (status)
    {
        // If master sends a write request, read the data and store it in the thrusters_values array
        case TWI_SR_DATA_ACK:
            thrusters_values[TWI_RX_BUFFER_INDEX++] = TWDR;
            if(TWI_RX_BUFFER_INDEX >= TWI_RX_BUFFER_SIZE)
             {
                TWI_RX_BUFFER_INDEX = 0;
             }
             SLAVE_END_TWI();
            break;

        // If the master sends a read request, send the sensor values
        case TWI_ST_SLA_ACK:
            TWI_TX_BUFFER_INDEX = 0;
            TWDR = sensor_values[TWI_TX_BUFFER_INDEX++];
            SLAVE_END_TWI();
            break;

        // If a data byte is transmitted, send the next byte, if available
        case TWI_ST_DATA_ACK:
            if(TWI_TX_BUFFER_INDEX < TWI_TX_BUFFER_SIZE)
            {
                TWDR = sensor_values[TWI_TX_BUFFER_INDEX++];
            }
            else
            {
                TWDR = 0xFF; 
            }
            SLAVE_END_TWI();
            break;

        // If the last byte is transmitted, end the TWI communication
        case TWI_ST_LAST_DATA_ACK:
            SLAVE_END_TWI();
            break;

        // If the master sends a stop condition, end the TWI communication
        case TWI_ST_DATA_NACK:
            SLAVE_END_TWI();
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

