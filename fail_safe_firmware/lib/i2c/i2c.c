#include "i2c.h"
#include "esc_driver.h"

void I2C::setup()
{
    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receive_message);
}

void I2C::receive_message(int bytes)
{

    if (bytes == 8)
    {

        int pwmValues[4];
        for (int i = 0; i < 4; i++)
        {
            int msb = Wire.read();
            int lsb = Wire.read();
            pwmValues[i] = (msb << 8) | lsb;
        }

        if (!IS_ARMED)
        {
            ESC_Driver::drive(pwmValues[0], pwmValues[1], pwmValues[2], pwmValues[3]);

            Serial.print(F("PWM values: "));
            for (int i = 0; i < 4; i++)
            {
                Serial.print(pwmValues[i]);
                Serial.print("  ");
            }
            Serial.println();
        }
        else
        {
            Serial.println(F("Thrusters are not armed"));
        }
    }
    else
    {
        ESC_Driver::disarm();
        Serial.println("Invalid data length recieved. Thrusters disarmed!");
    }
}