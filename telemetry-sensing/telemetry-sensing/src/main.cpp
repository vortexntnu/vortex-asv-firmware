#include <Arduino.h>
#include <TEMPERATURE.h>
#include <I2C.h>
#include <BUZZER.h>
#include <DISTANCE.h>
#include <BUTTON.h>

bool button_start_state;

void setup() {

  //byte i2c_rcv;          // data received from I2C bus
  //uint32_t time_start;   // start time in mSec
  
  Serial.begin(9600);

  //I2C::init(i2c_rcv, time_start);

  //Wire.begin(I2C_ADDR);           // join I2C bus as Slave with address 0x08
	
	// event handler initializations
	//Wire.onReceive(I2C::dataRcv);    // register an event handler for received data
	//Wire.onRequest(I2C::dataRqst);   // register an event handler for data requests
	
    
  //---------------------------------------------------------------------
  //SETUP THE BUZZER

  BUZZER::Buzzer_init();

  //SETUP THE DISTANCE SENSOR

  DISTANCE::CoverSensor_init(); 

  // Button logic
  /*
   * Initialize button
   * 
   * Read the first state of the button
   * This is done so that what ever the state of the button is right now, we will always have to toggle the switch to turn off the annoying buzzer
   * This is because people forget to reset the electronics jesjes
   */  
  BUTTON::init();
  button_start_state = BUTTON::get_state();
}


void loop() {

  Serial.println(DISTANCE::Getdistance(4,3));
  Serial.println(DISTANCE::Getdistance(8,7));
  Serial.println(DISTANCE::Is_lid_open());

  // Buzz the beeper only if both lid and button is in active state
  if (BUTTON::get_state() == button_start_state) {
    BUZZER::Set_Buzzer(DISTANCE::Is_lid_open());
  }
  else {
    BUZZER::Set_Buzzer(0);
  }

  Serial.println(TEMPERATURE::getTemps());
  Serial.println("");

  delay(1000);


}


