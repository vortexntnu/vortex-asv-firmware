#include "fs_status_light.h"

/*
    void set_rgby(bool r, bool g, bool b, bool y)
    {
    if (r)
    {
        MIXED_PORT2 |= (1 << LED_RED); // Set pin 3 on MIXED_PORT2
    }
    else
    {
        MIXED_PORT2 &= ~(1 << LED_RED); // Clear pin 3 on MIXED_PORT2
    }

    if (g)
    {
        MIXED_PORT2 |= (1 << LED_GREEN); // Set pin 4 on MIXED_PORT2
    }
    else
    {
        MIXED_PORT2 &= ~(1 << LED_GREEN); // Clear pin 4 on MIXED_PORT2
    }

    if (b)
    {
        MIXED_PORT2 |= (1 << LED_BLUE); // Set pin 5 on MIXED_PORT2
    }
    else
    {
        MIXED_PORT2 &= ~(1 << LED_BLUE); // Clear pin 5 on MIXED_PORT2
    }

    if (y)
    {
        MIXED_PORT2 |= (1 << LED_YELLOW); // Set pin 6 on MIXED_PORT2
    }
    else
    {
        MIXED_PORT2 &= ~(1 << LED_YELLOW); // Clear pin 6 on MIXED_PORT2
    }


        The following code is the same as the above, but in Arduino C:
        Which I admit is a lot easier to read, but I wanted to use the bitwise operators.
            digitalWrite(LED_RED, r);
            digitalWrite(LED_GREEN, g);
            digitalWrite(LED_BLUE, b);
            digitalWrite(LED_YELLOW, y);

    }
*/

void set_rgby(char colour[1], int state)
{
    switch (colour[0])
    {
    case 'r' || 'R':
        if (state == HIGH)
        {
            MIXED_PORT2 |= (1 << LED_RED);
        }
        else
        {
            MIXED_PORT2 &= ~(1 << LED_RED);
        }
        break;
    case 'g' || 'G':
        if (state == HIGH)
        {
            MIXED_PORT2 |= (1 << LED_GREEN);
        }
        else
        {
            MIXED_PORT2 &= ~(1 << LED_GREEN);
        }
        break;
    case 'b' || 'B':
        if (state == HIGH)
        {
            MIXED_PORT2 |= (1 << LED_BLUE);
        }
        else
        {
            MIXED_PORT2 &= ~(1 << LED_BLUE);
        }
        break;
    case 'y' || 'Y':
        if (state == HIGH)
        {
            MIXED_PORT2 |= (1 << LED_YELLOW);
        }
        else
        {
            MIXED_PORT2 &= ~(1 << LED_YELLOW);
        }
        break;
    case 'a' || 'A':
        if (state == HIGH)
        {
            MIXED_PORT2 |= (1 << LED_RED);
            MIXED_PORT2 |= (1 << LED_GREEN);
            MIXED_PORT2 |= (1 << LED_BLUE);
            MIXED_PORT2 |= (1 << LED_YELLOW);
        }
        else
        {
            MIXED_PORT2 &= ~(1 << LED_RED);
            MIXED_PORT2 &= ~(1 << LED_GREEN);
            MIXED_PORT2 &= ~(1 << LED_BLUE);
            MIXED_PORT2 &= ~(1 << LED_YELLOW);
        }
        break;
    default:
        MIXED_PORT2 &= ~(1 << LED_RED);
        MIXED_PORT2 &= ~(1 << LED_GREEN);
        MIXED_PORT2 &= ~(1 << LED_BLUE);
        MIXED_PORT2 &= ~(1 << LED_YELLOW);
        break;
    }
}

void run()
{
}

void test_24v_status()
{
    /*
        Will flash the LEDs in the following order:
        Red, Green, Blue, Yellow
        The arduino c equivalent is the same except for the delay function,
        which is replaced with _delay_ms().
    */
    set_rgby(HIGH, LOW, LOW, LOW);
    _delay_ms(1000);
    // delay(1000);
    set_rgby(LOW, LOW, LOW, LOW);
    _delay_ms(333);
    // delay(333);

    set_rgby(LOW, HIGH, LOW, LOW);
    _delay_ms(1000);
    // delay(1000);
    set_rgby(LOW, LOW, LOW, LOW);
    _delay_ms(333);
    // delay(333);

    set_rgby(LOW, LOW, HIGH, LOW);
    _delay_ms(1000);
    // delay(1000);
    set_rgby(LOW, LOW, LOW, LOW);
    _delay_ms(333);
    // delay(333);

    set_rgby(LOW, LOW, LOW, HIGH);
    _delay_ms(1000);
    // delay(1000);
    set_rgby(LOW, LOW, LOW, LOW);
}

void test_leds()
{
    // Will turn on all the LEDs for 2 seconds and then turn them off.
    LEDS_PORT = 0xFF;

    _delay_ms(2000);

    LEDS_PORT = 0x00;

    /*
        The following code is the same as the above, but in Arduino C:
            for (int i = 30; i < 42; i++)
            {
                if (!(i == 38 || i == 39))
                {
                    digitalWrite(i, HIGH);
                }
            }

            delay(2000);

            for (int i = 30; i < 42; i++)
            {
                if (!(i == 38 || i == 39))
                {
                    digitalWrite(i, LOW);
                }
            }
    */
}
