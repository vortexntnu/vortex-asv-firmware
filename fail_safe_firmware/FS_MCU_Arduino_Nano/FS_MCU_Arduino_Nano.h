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

//Declare functions
  void test_fail_safe_trigger(byte input_pin, byte LED_output_pin);
  void set_main_output(bool main_output_value);
  void status_lights();  
  void set_RGBY(bool R, bool G, bool B, bool Y);

//Global Variables
  bool armed;
  bool fail_safe_locked;
  bool all_systems_go;