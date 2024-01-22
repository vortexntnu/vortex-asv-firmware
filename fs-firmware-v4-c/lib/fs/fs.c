#include "fs.h"

void test_fs_trigger(byte input_pin, byte led_output_pin)
{
    if (digitalRead(input_pin))
    {
        digitalWrite(led_output_pin, HIGH);
    }
    else
    {
        allSystemsGo = false;
        fsLocked = true;
        digitalWrite(LED_FS_LOCKED_STATUS, HIGH);
        set_main_output(LOW);
        digitalWrite(led_output_pin, HIGH);
    }
}

void set_main_output(bool main_output_value)
{
    digitalWrite(FS_MC_OUTPUT, main_output_value);
    digitalWrite(LED_SW_OM, main_output_value);
}

void test_sw_ks(byte input_pin)
{
    if (analogRead(input_pin) > analogLogicHighCutoff)
    {
        digitalWrite(LED_SW_KS, LOW);
    }
    else
    {
        digitalWrite(LED_SW_KS, HIGH);

        allSystemsGo = false;
        fsLocked = true;
        digitalWrite(LED_FS_LOCKED_STATUS, HIGH);
        set_main_output(LOW);
    }
}

void temperature_check()
{

    while (temp >= maxLevelLimit && temperatureLevel != 5)
    {

        startTime = currentTime;

        if (currentTime - startTime >= 10)
        {
            temperatureLevel += 1;
        }
    }

    while (temp < minLevelLimit && temperatureLevel != 0)
    {

        startTime = currentTime;

        if (currentTime - startTime >= 10)
        {
            temperatureLevel -= 1;
        }
    }

    switch (temperatureLevel)
    {

    case 0:

        maxLevelLimit = 40;
        break;

    case 1:

        minLevelLimit = 40;
        maxLevelLimit = 60;
        break;

    case 2:

        minLevelLimit = 60;
        maxLevelLimit = 70;
        break;

    case 3:

        minLevelLimit = 70;
        maxLevelLimit = 80;
        break;

    case 4:

        minLevelLimit = 80;
        maxLevelLimit = 90;
        break;

    case 5:

        minLevelLimit = 90;
        break;
    }
}