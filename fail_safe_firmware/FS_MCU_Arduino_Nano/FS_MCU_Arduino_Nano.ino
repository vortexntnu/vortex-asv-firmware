
//This Fail Safe firmware is used on an Arduino Nano, to read DC signals from the PWM MCU, Hardware kill switch and Software kill switch in order to control the thruster relays and securely operate the ASV. It also controls the status indicator lights for the ASV, so that nearby traffic may act accordingly.

#include "FS_MCU_Arduino_Nano.h"

void setup() {
  // Serial.begin(9600);
  // Serial.println("Boot");
  
  //boot FS MCU in a safe state
  fail_safe_locked = true;
  
  //setup input pins
  pinMode(pin_arm_input, INPUT_PULLUP);
  pinMode(pin_OtA_KS_input, INPUT_PULLUP);
  pinMode(pin_HW_KS_input, INPUT_PULLUP);
  pinMode(pin_RX_timeout_input, INPUT_PULLUP);

  pinMode(pin_RX_operation_mode_input, INPUT_PULLUP);

  //setup output pins
  pinMode(pin_SW_fail_safe_status_output, OUTPUT);
  pinMode(pin_main_output, OUTPUT);
  pinMode(pin_LED_FS_locked_output, OUTPUT);
  pinMode(pin_status_light_Y_output, OUTPUT);
  pinMode(pin_LED_RX_timeout_output, OUTPUT);
  pinMode(pin_LED_armed_output, OUTPUT);
  pinMode(pin_status_light_B_output, OUTPUT);
  pinMode(pin_status_light_G_output, OUTPUT);
  pinMode(pin_LED_SW_KS_status_output, OUTPUT);
  pinMode(pin_LED_HW_KS_status_output, OUTPUT);
  pinMode(pin_LED_OtA_KS_status_output, OUTPUT);
  pinMode(pin_status_light_R_output, OUTPUT);

  //blackout of 24V-Status-Light
  set_RGBY(LOW, LOW, LOW, LOW);

  //test FS-PCB-LEDs
  digitalWrite(pin_LED_FS_locked_output, HIGH);
  digitalWrite(pin_LED_RX_timeout_output, HIGH);
  digitalWrite(pin_LED_armed_output, HIGH);
  digitalWrite(pin_LED_SW_KS_status_output, HIGH);
  digitalWrite(pin_LED_HW_KS_status_output, HIGH);
  digitalWrite(pin_LED_OtA_KS_status_output, HIGH);
  delay(2000); //2 seconds LED HIGH

  digitalWrite(pin_LED_FS_locked_output, LOW);
  digitalWrite(pin_LED_RX_timeout_output, LOW);
  digitalWrite(pin_LED_armed_output, LOW);
  digitalWrite(pin_LED_SW_KS_status_output, LOW);
  digitalWrite(pin_LED_HW_KS_status_output, LOW);
  digitalWrite(pin_LED_OtA_KS_status_output, LOW);
  delay(1000); //1 second LED LOW

  //test 24V-Status-Light
  
  set_RGBY(HIGH, LOW, LOW, LOW);
  delay(1000); //1 Second solid "Red"
  set_RGBY(LOW, LOW, LOW, LOW);
  delay(333); //.333 Second blackout

  set_RGBY(LOW, HIGH, LOW, LOW);
  delay(1000); //1 Second solid "Green"
  set_RGBY(LOW, LOW, LOW, LOW);
  delay(333); //.333 Second blackout

  set_RGBY(LOW, LOW, HIGH, LOW);
  delay(1000); //1 Second solid "Blue"
  set_RGBY(LOW, LOW, LOW, LOW);
  delay(333); //.333 Second blackout

  set_RGBY(LOW, LOW, LOW, HIGH);
  delay(1000); //1 Second solid "Yellow"
  
  set_RGBY(LOW, LOW, LOW, LOW);
  delay(2000); //2 Second blackout

  //Setup finished
}

void loop() {
  armed = digitalRead(pin_arm_input);
  if (armed){
    digitalWrite(pin_LED_armed_output,HIGH);
  }
  else{
    digitalWrite(pin_LED_armed_output,LOW);
    set_main_output(LOW);
  }

  //assume all is well, but check if any tests fail 
  all_systems_go = true;

  //OtA KS test
  test_fail_safe_trigger(pin_OtA_KS_input, pin_LED_OtA_KS_status_output);
  
  //HW KS test
  test_fail_safe_trigger(pin_HW_KS_input, pin_LED_HW_KS_status_output);
  
  //RX timeout test
  test_fail_safe_trigger(pin_RX_timeout_input, pin_LED_RX_timeout_output);
  
  //SW KS test
  if (analogRead(pin_SW_KS_input)>analog_logic_high_cutoff){
    digitalWrite(pin_LED_SW_KS_status_output,LOW);
    // Serial.println("HIGH");
    // Serial.println(analogRead(pin_SW_KS_input));

  }
  else{
    digitalWrite(pin_LED_SW_KS_status_output,HIGH);
    
    all_systems_go = false;
    fail_safe_locked = true;
    digitalWrite(pin_LED_FS_locked_output,HIGH);
    set_main_output(LOW);
    // Serial.println("LOW");
    // Serial.println(analogRead(pin_SW_KS_input));
  
  }


  if (fail_safe_locked){
    digitalWrite(pin_LED_FS_locked_output,HIGH);
    
    //try to unlock KS
    if (armed){
      all_systems_go = false; //neccessary for status light to be "red" colour
    }
    else if (all_systems_go){
      fail_safe_locked = false;
      digitalWrite(pin_LED_FS_locked_output,LOW);
    }
  else{
    }
  }
  
  //KS not locked
  else{
    if(armed){
      if (all_systems_go){
        set_main_output(HIGH);
      }
      else{
        set_main_output(LOW);
      } 
    }
    else{
      set_main_output(LOW);
    }
  }
  status_lights();   
}

void test_fail_safe_trigger(byte input_pin, byte LED_output_pin){
  if (digitalRead(input_pin)){
      digitalWrite(LED_output_pin,LOW);
    }
  else{
    all_systems_go = false;
    fail_safe_locked = true;
    digitalWrite(pin_LED_FS_locked_output,HIGH);    
    set_main_output(LOW);
    digitalWrite(LED_output_pin,HIGH);
  }
}

void set_main_output(bool main_output_value){
  digitalWrite(pin_main_output, main_output_value);               //Set fail safe main output
  digitalWrite(pin_SW_fail_safe_status_output, main_output_value);//Tell SW current status of FS
  
}

void status_lights(){
  //Set pins to control the status light indicating ASV operation mode. Reference the Vortex Wiki for more info.
  if (all_systems_go && armed){
    if(digitalRead(pin_RX_operation_mode_input)){
      //Manual
      set_RGBY(LOW,LOW,LOW,HIGH);
    }
    else{
      //SW controlled
      if (analogRead(pin_SW_operation_mode_input)>analog_logic_high_cutoff){
        //Software manual control (solid yellow)
        set_RGBY(LOW,HIGH,LOW,LOW); //change to 0,0,0,1 if using proper SW mode
      }
      else{
        //Autonomous (solid green)
        set_RGBY(LOW, HIGH, LOW, LOW);
      }
    }
  }
  else if (all_systems_go && !armed){

    if(digitalRead(pin_RX_operation_mode_input)){
      //Manual - unarmed (yellow-red flash)
      set_RGBY(HIGH,LOW,HIGH,HIGH);
    }
    else{
      //SW controlled - unarmed (yellow-red flash)
      if (analogRead(pin_SW_operation_mode_input)>analog_logic_high_cutoff){
        //Software manual control unarmed (yellow-red flash)
        set_RGBY(LOW,HIGH,HIGH,LOW); //change to 1,0,1,1 if using proper SW mode
      }
      else{
        //Autonomous - unarmed (green-red flash)
        set_RGBY(LOW, HIGH, HIGH, LOW);
      }
    }

  }
  
  else{
    //KS triggered
    set_RGBY(HIGH, LOW, LOW, LOW); 
  }
}

void set_RGBY(bool R, bool G, bool B, bool Y){
  //due to incorrectly selected Mosfet, states are inverted
  digitalWrite(pin_status_light_R_output, !R);    //RED status pin 
  digitalWrite(pin_status_light_G_output, !G);    //GREEN status pin 
  digitalWrite(pin_status_light_B_output, !B);    //BLUE status pin 
  digitalWrite(pin_status_light_Y_output, !Y);    //YELLOW status pin
}