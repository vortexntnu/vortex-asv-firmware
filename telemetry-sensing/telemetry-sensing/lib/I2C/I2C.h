#include<Arduino.h>
#include <Wire.h>

#define I2C_ADDR 0x08   // I2C address of this slave device             
#define RX_PIN 0        // I2C pin number on which to receive data
#define TX_PIN 1

namespace I2C{

    void init(byte &i2c_rcv, uint32_t &time_start); // initialize global variables
}