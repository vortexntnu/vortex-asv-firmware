#include "status_light.h"

#include <avr/io.h>
#include <util/delay.h>

void LED_init(void)
{
    // Set the LED pins as outputs
    DDRA |= (1 << RGB_RED) | (1 << RGB_GREEN) | (1 << RGB_BLUE) 
            | (1 << RGB_YELLOW);

    DDRC |= (1 << LED_BENJAMIN_DEBUGGER) | (LED_RX_TIMEOUT)
            | (1 << LED_OtA_KS_STATUS) | (1 << LED_SW_KS_STATUS)
            | (1 << LED_HW_KS_STATUS) | (1 << LED_FS_LOCKED)
            | (1 << LED_SW_OM) | (1 << LED_THRUSTERS_ARMED);

    DDRG |= (1 << LED_OVERTEMP_STATUS); 
}


void set_rgby(uint8_t r, uint8_t g, uint8_t b, uint8_t y)
{
    if (r)
    {
        PORTA |= RGB_RED; 
    }
    else
    {
        PORTA &= ~RGB_RED; 
    }

    if (g)
    {
        PORTA |= RGB_GREEN; 
    }
    else
    {
        PORTA &= ~RGB_GREEN;
    }

    if (b)
    {
        PORTA |= RGB_BLUE;
    }
    else
    {
        PORTA &= ~RGB_BLUE;
    }

    if (y)
    {
        PORTA |= RGB_YELLOW; 
    }
    else
    {
        PORTA &= ~RGB_YELLOW;
    }
}

void test_rgby(void)
{
    set_rgby(1, 0, 0, 0); // Red
    _delay_ms(1000);
    set_rgby(0, 0, 0, 0);
    _delay_ms(333);

    set_rgby(0, 1, 0, 0); // Green
    _delay_ms(1000);
    set_rgby(0, 0, 0, 0);
    _delay_ms(333);

    set_rgby(0, 0, 1, 0); // Blue
    _delay_ms(1000);
    set_rgby(0, 0, 0, 0);
    _delay_ms(333);

    set_rgby(0, 0, 0, 1); // Yellow
    _delay_ms(1000);
    set_rgby(0, 0, 0, 0);
}

void test_leds(void)
{
    PORTC = 0xFF;       // Turn on all LEDs on PORTC
    PORTG |= 0x02;      // Turn on LED on PORTG
    _delay_ms(1000);  
    PORTC &= 0x00;      // Turn off all LEDs on PORTC
    PORTG &= ~0x02;     // Turn off LED on PORTG
}

