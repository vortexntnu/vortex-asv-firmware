#include <Arduino.h>
#include<TEMP.h>
#include<I2C.h>


void setup() {

  byte i2c_rcv;          // data received from I2C bus
  uint32_t time_start;   // start time in mSec
  
  Serial.begin(9600);

  I2C::init(i2c_rcv, time_start);

  //Wire.begin(I2C_ADDR);           // join I2C bus as Slave with address 0x08
	
	// event handler initializations
	//Wire.onReceive(I2C::dataRcv);    // register an event handler for received data
	//Wire.onRequest(I2C::dataRqst);   // register an event handler for data requests
	
	
}


void loop() {

  Serial.println(TEMP::getTemps());

  Serial.println("");

  delay(1000);


}