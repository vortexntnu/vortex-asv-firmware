#include "usart.h"

void usart_init(void)
{
    // Set baud rate
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    if (USE_2X)
    {
        UCSR0A |= (1 << U2X0);
    }
    else
    {
        UCSR0A &= ~(1 << U2X0);
    }

    UCSR0C = 0x06; // Set frame format: 8data, 1stop bit
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void usart_sendChar(unsigned char c)
{
    // Wait until data register is empty
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    // Send data
    UDR0 = c;
}

unsigned char usart_receive(void)
{
    // Wait until data is received
    while (!(UCSR0A & (1 << RXC0)))
        ;
    // Return received data
    return UDR0;
}

void usart_sendString(char *str)
{
    // Send characters until null terminator is reached
    while (*str != '\0')
    {
        usart_sendChar(*str);
        str++;
    }
}
