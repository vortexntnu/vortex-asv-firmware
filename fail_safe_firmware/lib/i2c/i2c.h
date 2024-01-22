#ifndef I2C_H
#define I2C_H

#include "gpio.h"
#include <Wire.h>

namespace I2C
{
    void setup();
    void receive_message(int bytes);
}

#endif
