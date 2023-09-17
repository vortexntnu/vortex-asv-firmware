#include <Arduino.h>

#define TEMP_PIN_0 A0
#define TEMP_PIN_1 A1
#define TEMP_PIN_2 A2
#define TEMP_PIN_3 A3
#define TEMP_PIN_4 A4
#define TEMP_PIN_5 A5
#define TEMP_PIN_6 A6
#define TEMP_PIN_7 A7
#define TEMP_RES 4700 //resistance of thermistor
#define TEMP_VDRES 4700 //resistance of voltage divider
#define TEMP_BETA 3799.42 //beta value of thermistor
#define TEMP_AMB 298.15 //ambient temperature in Kelvin

#define RX_PIN 0
#define TX_PIN 1

// put function declarations here:

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getVoltage(int16_t pin) {
  return floatMap(analogRead(pin), 0, 1023, 0.000, 5.000);
}

float voltageToResistance(int16_t pin) {
  return TEMP_VDRES * ((5/getVoltage(pin)) - 1);
}

float resistanceToTemp(int16_t pin) {

  return pow((1/TEMP_AMB)+(1/TEMP_BETA)*log(voltageToResistance(pin)/TEMP_RES),-1);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*pinMode(TEMP_PIN_0, INPUT) ;
  pinMode(TEMP_PIN_1, INPUT) ;
  pinMode(TEMP_PIN_2, INPUT) ;
  pinMode(TEMP_PIN_3, INPUT) ;
  pinMode(TEMP_PIN_4, INPUT) ;
  pinMode(TEMP_PIN_5, INPUT) ;
  pinMode(TEMP_PIN_6, INPUT) ;
  pinMode(TEMP_PIN_7, INPUT) ;*/


}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(resistanceToTemp(TEMP_PIN_0)-273.15);

  Serial.println(getVoltage(TEMP_PIN_0));

  //Serial.println(analogRead(TEMP_PIN_0));

  Serial.println("");
  delay(100);

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}