
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
    //test SW operation mode
    if (analogRead(pin_SW_operation_mode_input)>analog_logic_high_cutoff){
      set_RGBY(LOW, LOW, LOW, HIGH);
    }
    else{set_RGBY(LOW, HIGH, LOW, LOW);}
    delay(1000); //1 Second solid "Blue"
    set_RGBY(LOW, LOW, LOW, LOW);
    delay(333); //.333 Second blackout
    
    //test SW KS
    if (analogRead(pin_SW_KS_input)>analog_logic_high_cutoff){
      set_RGBY(LOW, LOW, HIGH, LOW);
    }
    else{set_RGBY(HIGH, LOW, LOW, LOW);}
    delay(1000); //1 Second solid "Blue"
    set_RGBY(LOW, LOW, LOW, LOW);
    delay(333); //.333 Second blackout

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
      set_RGBY(LOW,LOW,HIGH,LOW); //use LOW,LOW,LOW,HIGH for competition
    }
    else{
      //SW controlled
      if (analogRead(pin_SW_operation_mode_input)>analog_logic_high_cutoff){
        //Software manual control (solid yellow)
        set_RGBY(LOW,LOW,LOW,HIGH); //change to LOW,HIGH,LOW,LOW if using simplified SW mode
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
      set_RGBY(LOW,LOW,HIGH,HIGH); //use HIGH,LOW,HIGH,HIGH for competition 
    }
    else{
      //SW controlled - unarmed (yellow-red flash)
      if (analogRead(pin_SW_operation_mode_input)>analog_logic_high_cutoff){
        //Software manual control unarmed (yellow-red flash)
        set_RGBY(HIGH,LOW,HIGH,HIGH); //change to LOW,HIGH,HIGH,LOW if using simplified SW mode
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