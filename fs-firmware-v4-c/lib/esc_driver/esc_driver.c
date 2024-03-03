#include "esc_driver.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void timers_init(void)
{
    // Set timer 1 and 4 to Fast PWM mode, 16-bit
    TCCR1A |= (1 << WGM11) | (1 << COM1A1);
    TCCR4A |= (1 << WGM41) | (1 << COM4A1) | (1 << COM4B1) | (1 << COM4C1);

    // Set prescaler to 8 for timer 1 and 4
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); 
    TCCR4B |= (1 << WGM43) | (1 << WGM42) | (1 << CS41);

    ICR1 = 39999; // Set TOP value to 39999

    // Set duty cycle to 0
    OCR1A = 0;
}

void arm_esc(void)
{
    // Set duty cycle to 50%
    OCR4A = ARMING_PWM;
    OCR4B = ARMING_PWM;
    OCR4C = ARMING_PWM;
    OCR1A = ARMING_PWM;

    _delay_ms(STARTUP_DELAY);
}

void set_esc_speed(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4)
{
    // Set duty cycle to the desired PWM value
    OCR4A = PWM_ESC1;
    OCR4B = PWM_ESC2;
    OCR4C = PWM_ESC3;
    OCR1A = PWM_ESC4;

    // Wait for 20ms to allow the ESCs to update
    _delay_ms(20);
}

void disarm_esc(void)
{
    // Set duty cycle to 0
    OCR4A = 0;
    OCR4B = 0;
    OCR4C = 0;
    OCR1A = 0;

    // wait for 20ms to allow the ESCs to update
    _delay_ms(20);
}
