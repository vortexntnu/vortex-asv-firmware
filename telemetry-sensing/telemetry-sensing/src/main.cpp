#include <Arduino.h>
#include <Wire.h>


#define TEMP_PIN_0 A0
#define TEMP_PIN_1 A1
#define TEMP_PIN_2 A2
#define TEMP_PIN_3 A3
#define TEMP_PIN_4 A6
#define TEMP_PIN_5 A7
#define TEMP_RES 4700 //resistance of thermistor at room temperature
#define TEMP_VDRES 10000 //resistance of voltage divider
#define TEMP_BETA 3799.42 //beta value of thermistor
#define TEMP_AMB 298.15 //ambient temperature in Kelvin
#define Voltage 5.000 //voltage of arduino

#define I2C_ADDR 0x08           // I2C address of this slave device             // I2C pin number on which to receive data

#define RX_PIN 0
#define TX_PIN 1

byte i2c_rcv;               // data received from I2C bus
unsigned long time_start;   // start time in mSec

// put function declarations here:

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getVoltage(int16_t pin) {
  return Voltage - floatMap(analogRead(pin), 0, 1023, 0.000, Voltage);
}

float voltageToResistance(int16_t pin) {
  return (getVoltage(pin)*TEMP_VDRES)/(Voltage-getVoltage(pin));
}

float resistanceToTemp(int16_t pin) {

  return pow((1/TEMP_AMB)+(1/TEMP_BETA)*log(voltageToResistance(pin)/TEMP_RES),-1);
}

String getTemps(){
  return String(resistanceToTemp(TEMP_PIN_0)-273.15) + "," + String(resistanceToTemp(TEMP_PIN_1)-273.15) + "," + String(resistanceToTemp(TEMP_PIN_2)-273.15) + "," + String(resistanceToTemp(TEMP_PIN_3)-273.15) + "," + String(resistanceToTemp(TEMP_PIN_4)-273.15) + "," + String(resistanceToTemp(TEMP_PIN_5)-273.15);
}

//received data handler function
void dataRcv(int numBytes){
	while(Wire.available()) {	// read all bytes received
		i2c_rcv = Wire.read();
	}
}

// requests data handler function
void dataRqst(){
	Wire.write("test"); // send potentiometer position
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);           // join I2C bus as Slave with address 0x08
	
	// event handler initializations
	Wire.onReceive(dataRcv);    // register an event handler for received data
	Wire.onRequest(dataRqst);   // register an event handler for data requests
	
	// initialize global variables
	i2c_rcv = 255;
	time_start = millis();
      // set pin 13 mode to output


}

void loop() {

  Serial.println(getTemps());

  Serial.println("");
  delay(1000);


}