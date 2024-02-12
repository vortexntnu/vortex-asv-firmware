#include "esc_driver.h"

void timer1_init(void)
{
    // Set timer 1 to Fast PWM mode, 16-bit
    TCCR1A |= (1 << WGM11)(1 << COM1A1)(1 << COM1B1)(1 << COM1C1);

    TCCR1B |= (1 << WGM13)(1 << WGM12)(1 << CS11); // Set prescaler to 8

    ICR1 = 39999; // Set TOP value to 39999

    // Set duty cycle to 0
    OCR1A = 0;
}

void arm_esc(void)
{
    // Set duty cycle to 50%
    OCR1A = ARMING_PWM;
    OCR1B = ARMING_PWM;
    OCR1C = ARMING_PWM;
    OCR1D = ARMING_PWM;

    // Wait for 1.5 seconds
    _delay_ms(STARTUP_DELAY);
}

void set_esc_speed(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4)
{
    // Set duty cycle to the desired PWM value
    OCR1A = PWM_ESC1;
    OCR1B = PWM_ESC2;
    OCR1C = PWM_ESC3;
    OCR1D = PWM_ESC4;

    // Wait for 20ms to allow the ESCs to update
    _delay_ms(20);
}

void disarm_esc(void)
{
    // Set duty cycle to 0
    OCR1A = 0;
    OCR1B = 0;
    OCR1C = 0;
    OCR1D = 0;

    // wait for 20ms to allow the ESCs to update
    _delay_ms(20);
}
