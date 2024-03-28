#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << PB7);

    while (1)
    {
        PORTB |= (1 << PB7);
        _delay_ms(1000);
        PORTB &= ~(1 << PB7);
        _delay_ms(500);
    }
}