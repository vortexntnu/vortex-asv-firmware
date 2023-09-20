#include <Arduino.h>

// defines pins numbers
const int trigPin1 = 4;
const int echoPin1 = 5;

const int trigPin2 = 7;
const int echoPin2 = 8;

const int switchPin = 3;
const int buzzerPin = 6;

//Distance when cover is on 
const unsigned int distanceClosed = 130;

// defines variables
long duration;
unsigned int distance;

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input
  pinMode(buzzerPin, OUTPUT);
  pinMode(switchPin, INPUT);

  Serial.begin(9600); // Starts the serial communication
  Serial.println("Starting process");
}

bool isLidClosed(int trigPin, int echoPin) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.34 / 2;
  Serial.println(distance);

  return distance>distanceClosed;
}

void BuzzIfLidOpen() {

  int stateOfSwitch = digitalRead(switchPin);

  if (stateOfSwitch == HIGH){
    if (isLidClosed(trigPin1, echoPin1) && isLidClosed(trigPin2, echoPin2)) {
      tone(buzzerPin, 1000);
      delay(100);
    }
    else{
      noTone(buzzerPin);
    }
  }
  else{
    noTone(buzzerPin);
  }
}

void loop(){}