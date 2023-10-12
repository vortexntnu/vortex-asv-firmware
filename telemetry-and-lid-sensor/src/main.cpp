#include <Arduino.h>
#include <Wire.h>

//////////////////////////////////////////////////////////////////////////////////////

#define TEMP_PIN_0 A0 //motorcontroller 1
#define TEMP_PIN_1 A1 //motorcontroller 2
#define TEMP_PIN_2 A2 //motorcontroller 3
#define TEMP_PIN_3 A3 //motorcontroller 4
#define TEMP_PIN_4 A6 //ambient 2
#define TEMP_PIN_5 A7 //ambient 1
#define TEMP_RES 4700 // resistance of thermistor at room temperature
#define TEMP_VDRES 10000 // resistance of voltage divider
#define TEMP_BETA 2679.52 // beta value of thermistor
/* resistance values at certain temperatures (in celcius)
25  4k7
50  2k345
75  1k285
*/
#define TEMP_AMB 298.15 // ambient temperature in Kelvin
#define Voltage 5.000 // voltage of Arduino

#define I2C_ADDR 0x08 // I2C address of this slave device
#define RX_PIN 0
#define TX_PIN 1

// Ultrasonic sensor pins
#define TRIG_PIN_1 4
#define ECHO_PIN_1 3
#define TRIG_PIN_2 8
#define ECHO_PIN_2 7

// Buzzer and switch pins
#define SWITCH_PIN 11
#define BUZZER_PIN 6

byte i2c_rcv; // data received from I2C bus
unsigned long time_start; // start time in mSec

bool defaultSwitchState;

// Function declarations
float floatMap(float x, float in_min, float in_max, float out_min, float out_max);
float getVoltage(int16_t pin);
float voltageToResistance(int16_t pin);
float resistanceToTemp(int16_t pin);
String getTemps();
void dataRcv(int numBytes);
void dataRqst();
void setupCoverSensor();
void setupBuzzer();
bool systemOn();
bool isLidClosed(int trigPin, int echoPin);
void BuzzIfLidOpen();

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);
  Wire.onReceive(dataRcv);
  Wire.onRequest(dataRqst);
  i2c_rcv = 255;
  time_start = millis();

  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);

  defaultSwitchState = digitalRead(SWITCH_PIN);

  Serial.println("Starting process");
}

void loop() {

  // getTemps(); returns a string with all the temperatures
  // isLidClosed(); returns true if the lid is closed
  

  BuzzIfLidOpen();
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getVoltage(int16_t pin) {
  return Voltage - floatMap(analogRead(pin), 0, 1023, 0.000, Voltage);
}

float voltageToResistance(int16_t pin) {
  return (getVoltage(pin) * TEMP_VDRES) / (Voltage - getVoltage(pin));
}

float resistanceToTemp(int16_t pin) {
  return pow((1 / TEMP_AMB) + (1 / TEMP_BETA) * log(voltageToResistance(pin) / TEMP_RES), -1);
}

String getTemps() {
  return String(resistanceToTemp(TEMP_PIN_0) - 273.15) + "," +
         String(resistanceToTemp(TEMP_PIN_1) - 273.15) + "," +
         String(resistanceToTemp(TEMP_PIN_2) - 273.15) + "," +
         String(resistanceToTemp(TEMP_PIN_3) - 273.15) + "," +
         String(resistanceToTemp(TEMP_PIN_4) - 273.15) + "," +
         String(resistanceToTemp(TEMP_PIN_5) - 273.15);
}


void dataRcv(int numBytes) {
  while (Wire.available()) {
    i2c_rcv = Wire.read();
  }
}

void dataRqst() {
  Wire.write("test");
}

bool systemOn() {
  bool stateOfSwitch = digitalRead(SWITCH_PIN);
  if (stateOfSwitch == defaultSwitchState) {
    noTone(BUZZER_PIN);
    return true;
  } 
  else {
    return false;
  }
}

bool isLidClosed(int trigPin, int echoPin, unsigned int distanceClosed) {
  long duration;
  unsigned int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.34 / 2;
  return distance > distanceClosed;
}

void BuzzIfLidOpen() {
  if (systemOn()) {
    if (isLidClosed(TRIG_PIN_1, ECHO_PIN_1,130) || isLidClosed(TRIG_PIN_2, ECHO_PIN_2,50)) {
      tone(BUZZER_PIN, 1000);
      delay(100);
    } else {
      noTone(BUZZER_PIN);
    }
  } else {
    noTone(BUZZER_PIN);
  }
}

//////////////////////////////////////////////////////////////////////////////////////