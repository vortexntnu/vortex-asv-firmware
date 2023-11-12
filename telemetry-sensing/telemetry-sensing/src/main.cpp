#include <Arduino.h>
#include <TEMPERATURE.h>
#include <I2C.h>
#include <BUZZER.h>
#include <DISTANCE.h>
#include <BUTTON.h>

bool button_start_state;

void setup() {
  Serial.begin(9600);
  delay(1000);

  // Set up communication ----------
  I2C::init();
  delay(1000);

  // Set up sensors ----------
  TEMPERATURE::init();

  // Set up Buzzer system ----------
  BUZZER::init();
  DISTANCE::init(); 
  BUTTON::init();

  // Button logic
  /*
   * Initialize button
   * 
   * Read the first state of the button
   * This is done so that what ever the state of the button is right now, we will always have to toggle the switch to turn off the annoying buzzer
   * This is because people forget to reset the electronics
   */ 
  button_start_state = BUTTON::get_state();
}


void loop() {
  // Buzz the beeper only if both lid and button is in active state
  if ((BUTTON::get_state() == button_start_state) and (DISTANCE::lid_is_open())) {
    BUZZER::Set_Buzzer(1);
  }
  else {
    BUZZER::Set_Buzzer(0);
  }

  // Get temperature
  float* temperatures = TEMPERATURE::getTemps();

  // Send all 6 temperature sensors data back to master
  for (int i = 0; i < 6; i++) {
    I2C::temperatureData[i] = temperatures[i];
  }

  // For debugging
  Serial.println(DISTANCE::get_distance(trigPin1, echoPin1));
  Serial.println(DISTANCE::get_distance(trigPin2, echoPin2));
  Serial.println(DISTANCE::lid_is_open());

  for (int i = 0; i < 6; i++) {
    Serial.print(temperatures[i]); //
    Serial.print(", ");
  }
  delete[] temperatures;
  Serial.println("");

  delay(1000);
}


