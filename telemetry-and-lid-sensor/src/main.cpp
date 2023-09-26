#include <Arduino.h>
#include <Wire.h>

#define TEMP_PIN_0 A0
#define TEMP_PIN_1 A1
#define TEMP_PIN_2 A2
#define TEMP_PIN_3 A3
#define TEMP_PIN_4 A6
#define TEMP_PIN_5 A7
#define TEMP_RES 4700 // resistance of thermistor at room temperature
#define TEMP_VDRES 10000 // resistance of voltage divider
#define TEMP_BETA 3799.42 // beta value of thermistor
#define TEMP_AMB 298.15 // ambient temperature in Kelvin
#define Voltage 5.000 // voltage of Arduino

#define I2C_ADDR 0x08 // I2C address of this slave device
#define RX_PIN 0
#define TX_PIN 1

// Ultrasonic sensor pins
const int trigPin1 = 4;
const int echoPin1 = 5;
const int trigPin2 = 7;
const int echoPin2 = 8;

// Buzzer and switch pins
const int switchPin = 3;
const int buzzerPin = 6;

byte i2c_rcv; // data received from I2C bus
unsigned long time_start; // start time in mSec

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

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);
  Wire.onReceive(dataRcv);
  Wire.onRequest(dataRqst);
  i2c_rcv = 255;
  time_start = millis();

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(switchPin, INPUT);

  Serial.println("Starting process");
}

void loop() {
  Serial.println(getTemps());
  BuzzIfLidOpen();
  delay(1000);
}

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
  bool stateOfSwitch = digitalRead(switchPin);
  if (!stateOfSwitch) {
    noTone(buzzerPin);
  }
  return stateOfSwitch;
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
    if (isLidClosed(trigPin1, echoPin1,130) && isLidClosed(trigPin2, echoPin2,50)) {
      tone(buzzerPin, 1000);
      delay(100);
    } else {
      noTone(buzzerPin);
    }
  } else {
    noTone(buzzerPin);
  }
}
