#include <Arduino.h>
#include <Wire.h>

// I2C address of this slave device used globally
#define I2C_ADDR 0x22

namespace I2C {
    // Used globally to interact and send data through I2C, bu manipulating this variable we send data through I2C that we want
    extern float* temperatureData;

    void requestEventHandler();
    void init();
}