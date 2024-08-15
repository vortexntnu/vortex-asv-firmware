
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
  pinMode(pin_LED_RX_timeout_output, OUTPUT);
  pinMode(pin_LED_armed_output, OUTPUT);
  pinMode(pin_LED_SW_KS_status_output, OUTPUT);
  pinMode(pin_LED_HW_KS_status_output, OUTPUT);
  pinMode(pin_LED_OtA_KS_status_output, OUTPUT);

  pinMode(pin_LED_R_output, output);
  pinMode(pin_LED_G_output, output);
  pinMode(pin_LED_Y_output, output);

  digitalWrite(pin_LED_Y_output, LOW);
  digitalWrite(pin_LED_G_output, LOW);
  digitalWrite(pin_LED_R_output, LOW);

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
  
  startup_sequence();
  set_LED_RGY(DIMMED_BRIGHTNESS, DIMMED_BRIGHTNESS, DIMMED_BRIGHTNESS);
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
    if(!digitalRead(pin_RX_operation_mode_input)){
      //Manual
      set_LED_RGY(0, 0, FULL_BRIGHTNESS);
    }
    else{
      //SW controlled
      if (analogRead(pin_SW_operation_mode_input)>analog_logic_high_cutoff){
        //Software manual control (solid yellow)
        set_LED_RGY(0, 0, FULL_BRIGHTNESS); 
      }
      else{
        //Autonomous (solid green)
        set_LED_RGY(0, FULL_BRIGHTNESS, 0);
      }
    }
  }
  else if (all_systems_go && !armed){

    if(!digitalRead(pin_RX_operation_mode_input)){
      //Manual - unarmed
      default_pulsing_sequence();
    }
    else{
      //SW controlled - unarmed
      if (analogRead(pin_SW_operation_mode_input)>analog_logic_high_cutoff){
        //Software manual control unarmed
        default_pulsing_sequence(); 
      }
      else{
        //Autonomous - unarmed 
        default_pulsing_sequence();
      }
    }

  }
  
  else{
    //KS triggered
    set_LED_RGY(FULL_BRIGHTNESS, 0, 0); 
  }
}

void startup_sequence() {
  set_LED_RGY(DIMMED_BRIGHTNESS, 0, 0);
  delay(1000);
  set_LED_RGY(0, DIMMED_BRIGHTNESS, 0);
  delay(1000);
  set_LED_RGY(0, 0, DIMMED_BRIGHTNESS);
  delay(1000);
  set_LED_RGY(0, 0, 0);
  delay(1000);
}

void default_pulsing_sequence() {
  for(int i = 0; i < 50; i += 5) {
    analogWrite(pin_LED_R_output, i);
    analogWrite(pin_LED_G_output, i);
    analogWrite(pin_LED_Y_output, i);
    delay(30);
  }
  for(int i = 50; i >= 0; i -= 5) {
    analogWrite(pin_LED_R_output, i);
    analogWrite(pin_LED_G_output, i);
    analogWrite(pin_LED_Y_output, i);
    delay(30);
  }
}

void set_LED_RGY(byte red, byte green, byte yellow) {
  analogWrite(pin_LED_R_output, red);    // Set Red PWM
  analogWrite(pin_LED_G_output, green);  // Set Green PWM
  analogWrite(pin_LED_Y_output, yellow); // Set Yellow PWM
}

