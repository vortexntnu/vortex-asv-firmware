//DC input pins
#define pin_arm_input 14    //Pin A0: RX Arm
#define pin_OtA_KS_input = 15    //Pin A1: RX Over the Air Kill Switch
#define pin_HW_KS_input = 16    //Pin A2: HW Kill Switch
#define pin_RX_timeout_input = 17    //Pin A3: RX timeout, if low then err

#define pin_RX_operation_mode_input = 19    //Pin A5: Operation Mode -- Software/Manual RX
#define pin_SW_KS_input = 20    //Pin A6: SW Kill Switch
#define pin_SW_operation_mode_input = 21    //Pin A7: Software Operation Mode -- Manual/Autonomous

//DC output pins
#define pin_SW_fail_safe_status_output = 18    //Pin A4: SW Kill switch return
#define pin_main_output = 2   //Pin D2: MCU fail safe system MAIN OUTPUT
#define pin_LED_FS_locked_output = 3   //Pin D3: LED KS locked
#define pin_LED_RX_timeout_output = 5   //Pin D5: LED RX timeout
#define pin_LED_armed_output = 6   //Pin D6: LED Armed
#define pin_LED_SW_KS_status_output = 9   //Pin D9: LED SW KS
#define pin_LED_HW_KS_status_output = 10   //Pin D10: LED HW KS
#define pin_LED_OtA_KS_status_output = 11   //Pin D11: LED OtA KS


#define pin_LED_Y_output
#define pin_LED_G_output
#define pin_LED_R_output  
#define FULL_BRIGHTNESS   255
#define DIMMED_BRIGHTNESS 255

//The SW inputs may send 3.3 V or less and therefore need to be read by the ADC
//The analog range 0V to 5V corresponds to the integer range 0 to 1023.
#define analog_logic_high_cutoff =  670;

//Declare functions
void test_fail_safe_trigger(byte input_pin, byte LED_output_pin);
void set_main_output(bool main_output_value);
void status_lights();  
void set_LED_RGY(byte red, byte green, byte yellow);
void default_pulsing_sequence();
void startup_sequence();

//Global Variables
bool armed;
bool fail_safe_locked;
bool all_systems_go;