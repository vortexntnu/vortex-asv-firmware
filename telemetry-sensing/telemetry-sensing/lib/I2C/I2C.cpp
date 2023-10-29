#include<I2C.h>

namespace I2C{

    void init(byte &i2c_rcv, uint32_t &time_start){
	    i2c_rcv = 255;
	    time_start = millis();
    }
/*
    void dataRcv(int numBytes){
        while(Wire.available()) {	
            i2c_rcv = Wire.read(); // read all bytes received
	}
}


    void dataRqst(){
	    Wire.write("test"); // send potentiometer position ????
}
   
*/

}
