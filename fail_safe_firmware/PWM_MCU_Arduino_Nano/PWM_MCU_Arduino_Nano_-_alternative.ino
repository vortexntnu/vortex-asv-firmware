//This firmware is used on an Arduino Nano, to interpret 50Hz RC PWM signals from a FrSky Radio Reciever and relay those to the Fail Safe MCU.

//ATTENTION: Do not upload while sending PWM signals to pins, this causes errors and results in an aborted upload. (This is presumably caused by hardware interrupts halting upload while triggered.)


//duty cycle range values, if outside range: do nothing
const int top_lim_DC_HIGH  = 2200;   //gives HIGH output, measured in [us]
const int bttm_lim_DC_HIGH = 1800;   //gives HIGH output, measured in [us]
const int top_lim_DC_LOW  = 1200;    //gives LOW output, measured in [us]
const int bttm_lim_DC_LOW = 800;     //gives LOW output, measured in [us]

//PWM input pins
const byte pin_OtA_KS_input = 2;   //D2: OtA Kill Switch - 5V PWM input
const byte pin_arm_input = 3;   //D3: Arm system - 5V PWM input
const byte pin_MUX_selector_input = 8;   //D8: ESC selector for MUX - 5V PWM input

//bool output pins
const byte pin_OtA_KS_output1 = 14;    //A0: OtA Kill Switch 1 - 5VDC out
const byte pin_OtA_KS_output2 = 15;    //A1: OtA Kill Switch 2 - 5VDC out
const byte pin_MUX_Selector_LED_output = 16;    //A2: MUX Selector LED - 5VDC out
const byte pin_arm_output = 17;    //A3: Arm system - 5VDC out
const byte pin_selector_output = 18;    //A4: ESC PWM MUX selector DC - 5 VDC out
const byte pin_RX_timeout_output = 19;    //A5: RX timeout - 5 VDC out

//RX timeout limit
const unsigned long max_wait = 5000000; //5 seconds

//declare functions
void interrupt_inpD2();
void interrupt_inpD3();
void pwm_read(byte pin, unsigned long & rise_time, bool & old_state);
void RX_timeout_check(unsigned long rise_time);

//rising edge - duty cycle start time variables
unsigned long rise_inpD2;
unsigned long rise_inpD3;
unsigned long rise_inpD8;

//RX timeout
unsigned long wait_time;

//output state storage
bool OtA_KS_state = LOW;
bool arm_state = LOW;
bool selector_state = LOW;



void setup() {
  Serial.begin(9600);
  Serial.println("Boot");

  //setup input pins
  pinMode(pin_OtA_KS_input, INPUT_PULLUP);
  pinMode(pin_arm_input, INPUT_PULLUP);
  pinMode(pin_MUX_selector_input, INPUT_PULLUP);

  //setup output pins
  pinMode(pin_OtA_KS_output1, OUTPUT);
  pinMode(pin_OtA_KS_output2, OUTPUT);
  pinMode(pin_MUX_Selector_LED_output, OUTPUT);
  pinMode(pin_arm_output, OUTPUT);
  pinMode(pin_selector_output, OUTPUT);
  pinMode(pin_RX_timeout_output, OUTPUT);
  
  //setup interrupts
    //Hardware interrupts
      attachInterrupt(digitalPinToInterrupt(pin_OtA_KS_input), interrupt_inpD2, CHANGE);
      attachInterrupt(digitalPinToInterrupt(pin_arm_input), interrupt_inpD3, CHANGE);
    //Software interrupt
      //Enable PCIE0 Bit 0 = 1(Port B)
      PCICR |= B00000001;
      //Select PCINT0 Bit0 = 1(Pin D8)
      PCMSK0 |= B00000001;

  //test LEDs
  digitalWrite(pin_MUX_Selector_LED_output, HIGH);
  delay(1000);
  digitalWrite(pin_MUX_Selector_LED_output, LOW);
  delay(1000);
}

//Check radio communication integrity. The RX sets all outputs low on signal loss.
void loop() {
  unsigned long wait = micros()-wait_time;

  if (wait>max_wait){
    digitalWrite(pin_RX_timeout_output, LOW);
  }
  else{
    digitalWrite(pin_RX_timeout_output, HIGH);
  }
}

void interrupt_inpD2() {
  pwm_read(pin_OtA_KS_input, rise_inpD2, OtA_KS_state);
  // update the outputs
  digitalWrite(pin_OtA_KS_output1, OtA_KS_state);
  digitalWrite(pin_OtA_KS_output2, OtA_KS_state);

}

void interrupt_inpD3() {
  pwm_read(pin_arm_input, rise_inpD3, arm_state);
  // update the output
  digitalWrite(pin_arm_output, arm_state);

}

ISR (PCINT0_vect){
  // Interrupt for Port B
  pwm_read(pin_MUX_selector_input, rise_inpD8, selector_state);
  // update the output
  digitalWrite(pin_selector_output, selector_state);
  digitalWrite(pin_MUX_Selector_LED_output, selector_state);
  
}

void pwm_read(byte pin, unsigned long & rise_time, bool & old_state){
    //Rising edge
  if (digitalRead(pin) == HIGH){
    rise_time = micros();
    wait_time = micros();
    return;
  }
  else{
    //Pin low --> Falling edge
    unsigned long duration = micros() - rise_time;
    //Serial.println(duration);
    
    if (bttm_lim_DC_HIGH < duration){
      if ( duration < top_lim_DC_HIGH){
        old_state = HIGH;   // turn the output HIGH
        return;
      }
    }
    else if (bttm_lim_DC_LOW<duration){
      if(duration<top_lim_DC_LOW){
        old_state = LOW;   // turn the output LOW
        return;
      }
    }
  }
}

