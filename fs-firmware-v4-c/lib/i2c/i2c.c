
#include "i2c.h"

ISR(TWI_vect)
{

    if ((TWSR & TW_NO_INFO) == TW_SR_SLA_ACK || (TWSR & TW_NO_INFO) == TW_SR_ARB_LOST_SLA_ACK)
    {
        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
    }
    else if ((TWSR & TW_NO_INFO) == TW_SR_DATA_ACK || (TWSR & TW_NO_INFO) == TW_SR_DATA_NACK)
    {
        status = TWDR;

        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
    }
    else
    {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
    }
}

void twi_init(uint8_t sub_address)
{
    // sub for submissi... I mean subscriber...
    TWAR = sub_address << 1;
    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
    sei();
}

int8_t i2c_listen()
{
    while (1)
    {
        uint8_t status;
        while (!(TWCR & (1 << TWINT)))
            ;
        status = TWSR & 0xF8;
        if (status == 0x60 || status == 0x68)
        {
            return 0;
        }
        if (status == 0xA8 || status == 0xB0)
        {
            return 1;
        }
        if (status == 0x70 || status == 0x78)
        {
            return 2;
        }
        else
        {
            continue;
        }
    }
}

int8_t i2c_transmit(char data)
{
    uint8_t status;
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

    while (!(TWCR & (1 << TWINT)))
        ;
    status = TWSR & 0xF8;
    if (status == 0xA0)
    {
        TWCR |= (1 << TWINT);
        return -1;
    }
}

void twi_match_read_slave(void)
{
    while ((TWSR & TW_NO_INFO) != TW_SR_SLA_ACK)
    {
        TWCR = (1 << TWEA) | (1 << TWEM) | (1 << TWINT);
        while (!(TWCR & (1 << TWINT)))
            ;
    }
}

void twi_read(void)
{
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
    while ((TWSR & TW_NO_INFO) != TW_SR_DATA_ACK)
        ;
    recv_data = TWDR;
    PORTB = recv_data;
}

void twi_match_wrtie_slave(void)
{
    while ((TWSR & TW_NO_INFO) != TW_ST_SLA_ACK)
    {
        TWCR = (1 << TWEA) | (1 << TWEM) | (1 << TWINT);
        while (!(TWCR & (1 << TWINT)))
            ;
    }
}
