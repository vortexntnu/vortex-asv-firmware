#include "freyaStatusLightArduinoCode.h"
 
//define variables
int redValue = 26;    // Default value
int yellowValue = 26; // Default value
int greenValue = 26;  // Default value
 
int header = 0;

enum State { RUNNING, SIGNALLOSS };
State currentState = RUNNING;
const int timeout = 1500;
unsigned long currentTime;
unsigned long lastMessageTime = millis();

void receiveEvent(int howMany) {
  lastMessageTime = millis();
  // Blink the LED to indicate that data was received
  digitalWrite(LED_PIN, HIGH); // Turn on LED (indicate end of reception)
  
  if (howMany >= 4) { // Expecting 3 bytes
    header = Wire.read();
    redValue = Wire.read();
    yellowValue = Wire.read();
    greenValue = Wire.read();
  }
  // Return to RUNNING state if in SIGNALLOSS state
  if (currentState == SIGNALLOSS) {
    currentState = RUNNING;
    digitalWrite(LED_PIN, LOW); // Turn off LED in RUNNING state
  }
}
  

void setup() {
  // Initialize the PWM pins as outputs
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
 
  // Set the default PWM values
  analogWrite(PIN_RED, redValue);
  analogWrite(PIN_YELLOW, yellowValue);
  analogWrite(PIN_GREEN, greenValue);
 
  // Initialize the I2C bus as a slave device with address 8
  Wire.begin(8);
 
  // Register the receive event
  Wire.onReceive(receiveEvent);

  // Store current time for signal loss detection  
  currentTime = millis();

  // Turn on the onboard LED to indicate that the code is running
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}
 
void loop() {

  switch (currentState) {
    case RUNNING:
      // Update the PWM signals on the pins
      analogWrite(PIN_RED, redValue);
      analogWrite(PIN_YELLOW, yellowValue);
      analogWrite(PIN_GREEN, greenValue);
      // Check for timeout
      currentTime = millis();
      if (currentTime - lastMessageTime > timeout) {
        currentState = SIGNALLOSS;
      }
      break;

    case SIGNALLOSS:
      analogWrite(PIN_RED, 5);
      analogWrite(PIN_YELLOW, 5);
      analogWrite(PIN_GREEN, 5);
      delay(200);
      analogWrite(PIN_RED, 0);
      analogWrite(PIN_YELLOW, 0);
      analogWrite(PIN_GREEN, 0);
      delay(190);
      break;
    delay(10);
  }
}
 
