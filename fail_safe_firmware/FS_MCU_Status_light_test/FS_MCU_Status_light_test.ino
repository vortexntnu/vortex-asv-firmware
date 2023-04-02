
//This Fail Safe firmware is used on an Arduino Nano, to read DC signals from the PWM MCU, Hardware kill switch and Software kill switch in order to control the thruster relays and securely operate the ASV. It also controls the status indicator lights for the ASV, so that nearby traffic may act accordingly.

//DC input pins
  const byte pin_arm_input = 14;    //Pin A0: RX Arm
  const byte pin_OtA_KS_input = 15;    //Pin A1: RX Over the Air Kill Switch
  const byte pin_HW_KS_input = 16;    //Pin A2: HW Kill Switch
  const byte pin_RX_timeout_input = 17;    //Pin A3: RX timeout, if low then err

  const byte pin_RX_operation_mode_input = 19;    //Pin A5: Operation Mode -- Software/Manual RX
  const byte pin_SW_KS_input = 20;    //Pin A6: SW Kill Switch
  const byte pin_SW_operation_mode_input = 21;    //Pin A7: Software Operation Mode -- Manual/Autonomous

//DC output pins
  const byte pin_SW_fail_safe_status_output = 18;    //Pin A4: SW Kill switch return
  
  const byte pin_main_output = 2;   //Pin D2: MCU fail safe system MAIN OUTPUT
  const byte pin_LED_FS_locked_output = 3;   //Pin D3: LED KS locked
  const byte pin_status_light_Y_output = 4;   //Pin D4: Status light Y
  const byte pin_LED_RX_timeout_output = 5;   //Pin D5: LED RX timeout
  const byte pin_LED_armed_output = 6;   //Pin D6: LED Armed
  const byte pin_status_light_B_output = 7;   //Pin D7: Status light B
  const byte pin_status_light_G_output = 8;   //Pin D8: Status light G
  const byte pin_LED_SW_KS_status_output = 9;   //Pin D9: LED SW KS
  const byte pin_LED_HW_KS_status_output = 10;   //Pin D10: LED HW KS
  const byte pin_LED_OtA_KS_status_output = 11;   //Pin D11: LED OtA KS
  const byte pin_status_light_R_output = 12;   //Pin D12: Status light R

//The SW inputs may send 3.3 V or less and therefore need to be read by the ADC
//The analog range 0V to 5V corresponds to the integer range 0 to 1023.
  const int analog_logic_high_cutoff =  670;

//Variables
  bool armed;
  bool fail_safe_locked = true;
  bool all_systems_go;
  
//Declare functions
  void test_fail_safe_trigger(byte input_pin, byte LED_output_pin);
  void set_main_output(bool main_output_value);
  void status_lights();  
  void set_RGBY(bool R, bool G, bool B, bool Y);


void setup() {
  // Serial.begin(9600);
  // Serial.println("Boot");
  
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

  //test LEDs
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

}

void loop() {
  set_RGBY(0,0,0,1);
  delay(2000);
  set_RGBY(0,0,1,0);
  delay(2000);
  set_RGBY(0,1,0,0);
  delay(2000);
  set_RGBY(1,0,0,0);
  delay(2000);
  set_RGBY(0,0,0,0);
  delay(5000);
  while(true){
    set_RGBY(1,1,1,1);
    delay(1000);
  }
}
  



void set_RGBY(bool R, bool G, bool B, bool Y){
  digitalWrite(pin_status_light_R_output, R);    //RED status pin 
  digitalWrite(pin_status_light_G_output, G);    //GREEN status pin 
  digitalWrite(pin_status_light_B_output, B);    //BLUE status pin 
  digitalWrite(pin_status_light_Y_output, Y);    //YELLOW status pin
}
