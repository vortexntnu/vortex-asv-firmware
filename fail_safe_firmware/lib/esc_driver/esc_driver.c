#include "esc_driver.h"

int ESC_Driver::drive(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4)
{
    ESC1.writeMicroseconds(PWM_ESC1);
    ESC2.writeMicroseconds(PWM_ESC2);
    ESC3.writeMicroseconds(PWM_ESC3);
    ESC4.writeMicroseconds(PWM_ESC4);
}

void ESC_Driver::arm()
{
    IS_ARMED = true;
    ESC1.writeMicroseconds(ARMING_PWM);
    ESC2.writeMicroseconds(ARMING_PWM);
    ESC3.writeMicroseconds(ARMING_PWM);
    ESC4.writeMicroseconds(ARMING_PWM);
}

void ESC_Driver::disarm()
{
    IS_ARMED = false;
    ESC_Driver::drive(0, 0, 0, 0);
}

bool ESC_Driver::fs_status(int status)
{
    bool fsTriggered = false;

    if (~(digitalRead(status)))
    {
        fsTriggered = true;
    }

    return fsTriggered;
}

int ESC_Driver::om_status(int status)
{
    int omStatus = -1;

    omStatus = digitalRead(status) ? 1 : 0;

    return omStatus;
}

void ESC_Driver::setup()
{
    ESC1.attach(PIN_ESC1);
    ESC2.attach(PIN_ESC2);
    ESC3.attach(PIN_ESC3);
    ESC4.attach(PIN_ESC4);
    ESC_Driver::arm();
}

void ESC_Driver::run()
{

    if (millis() - FS_TIMER_LAST_CHECK > FS_CHECK_INTERVAL)
    {

        int omStatus = ESC_Driver::om_status(OM);
        bool fsTriggered = ESC_Driver::fs_status(BUTTON_KS);

        if (IS_ARMED && (fsTriggered || omStatus == -1) || omStatus == 0)
        {
            Serial.println("Disarming!!!");
            ESC_Driver::disarm();
        }

        else if (IS_ARMED && !fsTriggered && omStatus == 1)
        {
            Serial.println("Arming...");
            ESC_Driver::arm();
        }

        FS_TIMER_LAST_CHECK = millis();
        Serial.print("HK (23): ");
        Serial.print(digitalRead(BUTTON_KS));
        Serial.print("  |   HM (20): ");
        Serial.print(digitalRead(OM));
        Serial.print("  |   Mode: ");
        Serial.print(fsTriggered);
        Serial.println();
    }
}
