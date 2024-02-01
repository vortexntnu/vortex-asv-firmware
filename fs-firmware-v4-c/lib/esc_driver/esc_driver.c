#include "esc_driver.h"

void esc_setup()
{
    Servo ESC1;
    Servo ESC2;
    Servo ESC3;
    Servo ESC4;

    ESC1.attach(ESC_PIN1, minPulseWidth, maxPulseWidth);
    ESC2.attach(ESC_PIN2, minPulseWidth, maxPulseWidth);
    ESC3.attach(ESC_PIN3, minPulseWidth, maxPulseWidth);
    ESC4.attach(ESC_PIN4, minPulseWidth, maxPulseWidth);

    arm_thrusters();
    delay(STARTUP_DELAY);

    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receive_i2c_message);
}

void arm_thrusters()
{
    ESC1.writeMicroseconds(ARMING_PWM);
    ESC2.writeMicroseconds(ARMING_PWM);
    ESC3.writeMicroseconds(ARMING_PWM);
    ESC4.writeMicroseconds(ARMING_PWM);
}

int drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4)
{
    ESC1.writeMicroseconds(PWM_ESC1);
    ESC2.writeMicroseconds(PWM_ESC2);
    ESC3.writeMicroseconds(PWM_ESC3);
    ESC4.writeMicroseconds(PWM_ESC4);
}

void receive_i2c_message(int bytes)
{
    if (bytes == 8)
    {
        int pwm_values[4];

        for (int i = 0; i < 4; i++)
        {
            pwm_values[i] = Wire.read() << 8;
            pwm_values[i] |= Wire.read();
        }

        drive_thrusters(pwm_values[0], pwm_values[1], pwm_values[2], pwm_values[3]);
    }
}