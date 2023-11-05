#include<I2C.h>

namespace I2C{

    void init(byte &i2c_rcv, uint32_t &time_start){
	    i2c_rcv = 255;
	    time_start = millis();
    }
}
