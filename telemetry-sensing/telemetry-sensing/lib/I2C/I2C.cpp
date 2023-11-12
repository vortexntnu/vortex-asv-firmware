#include <I2C.h>

namespace I2C {
    float* temperatureData = new float[6]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    void requestEventHandler() {
        // float has 4 bytes, we have 6 floats
        // iterate 6 times, bit shift 4 times by 1byte(8 bits) at a time
        for (int i = 0; i < 6; ++i) {
            // Get the address of the current float pointer
            uint8_t* byteData = (uint8_t*)(temperatureData + i);

            // Send each of the 4 bytes of the float
            for (uint32_t j = 0; j < sizeof(float); ++j) {
                Wire.write(byteData[j]);
            }
        }
    }

    void init(){
	    Wire.begin(I2C_ADDR); // join I2C bus as Slave with address 0x08
        Wire.onRequest(requestEventHandler);
    }
}
