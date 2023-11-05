#include <Arduino.h>
#include <TEMPERATURE.h>
#include <I2C.h>
#include <BUZZER.h>
#include <DISTANCE.h>
#include <BUTTON.h>

bool button_start_state;

void setup() {
  Serial.begin(9600);

  //byte i2c_rcv;          // data received from I2C bus
  //uint32_t time_start;   // start time in mSec
  //I2C::init(i2c_rcv, time_start);         
	
	// event handler initializations
	//Wire.onReceive(I2C::dataRcv);    // register an event handler for received data
	//Wire.onRequest(I2C::dataRqst);   // register an event handler for data requests
	
  //---------------------------------------------------------------------
  //setup I2C

   Wire.begin(I2C_ADDR); // join I2C bus as Slave with address 0x08

  //---------------------------------------------------------------------
  //SETUP THE BUZZER

  TEMPERATURE::Temperature_sensors_init();

  //---------------------------------------------------------------------
  //SETUP THE BUZZER

  BUZZER::Buzzer_init();

  //---------------------------------------------------------------------
  //SETUP THE DISTANCE SENSOR

  DISTANCE::CoverSensor_init(); 

  //---------------------------------------------------------------------
  //SETUP THE DISTANCE BUTTON

  BUTTON::init();
  button_start_state = BUTTON::get_state();

  // Button logic
  /*
   * Initialize button
   * 
   * Read the first state of the button
   * This is done so that what ever the state of the button is right now, we will always have to toggle the switch to turn off the annoying buzzer
   * This is because people forget to reset the electronics
   */  
}


void loop() {

  // Buzz the beeper only if both lid and button is in active state
  if (BUTTON::get_state() == button_start_state) {
    BUZZER::Set_Buzzer(DISTANCE::Is_lid_open());
  }
  else {
    BUZZER::Set_Buzzer(0);
  }


  // Send Temperature trough I2C

  Wire.beginTransmission(I2C_ADDR); 
  Wire.write(TEMPERATURE::getTemps().c_str());  
  //const char* myCString = myString.c_str();                
  Wire.endTransmission(); 

  delay(1000);  

  //For debugging

  Serial.println(DISTANCE::Getdistance(4,3));
  Serial.println(DISTANCE::Getdistance(8,7));
  Serial.println(DISTANCE::Is_lid_open());

  Serial.println(TEMPERATURE::getTemps());
  Serial.println("");


}


