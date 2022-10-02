
//This Fail Safe firmware is used on an Arduino Nano, to read DC signals from the PWM MCU, Hardware Kill switch and Software kill Switch in order to securely operate the ASV.

//DC input pins
  const byte inpA0 = 14;    //Arm
  const byte inpA1 = 15;    //OtA Kill Switch
  const byte inpA2 = 16;    //HW Kill Switch
  const byte inpA3 = 17;    //inverted SW Kill Switch

  const byte inpA5 = 19;    //Operation Mode -- Autonomous/Manual

//DC output pins
  const byte outA4 = A4;    //SW Kill switch return
  
  const byte outD2 = 2;   //MCU mosfet --- MAIN OUTPUT
  const byte outD3 = 3;   //LED KS locked
  const byte outD4 = 4;   //Status light Y
  
  const byte outD6 = 6;   //LED Armed
  const byte outD7 = 7;   //Status light B
  const byte outD8 = 8;   //Status light G
  const byte outD9 = 9;   //LED SW KS
  const byte outD10 = 10;   //LED HW KS
  const byte outD11 = 11;   //LED OtA KS
  const byte outD12 = 12;   //Status light R

//Variables
  bool armed;
  bool FS_locked = true;
  bool all_sys_go = false;
//Declare functions
void status_lights();  

void setup() {
  //Serial.begin(9600);
  
  //setup input pins
  pinMode(inpA0, INPUT_PULLUP);
  pinMode(inpA1, INPUT_PULLUP);
  pinMode(inpA2, INPUT_PULLUP);
  pinMode(inpA3, INPUT_PULLUP);
  
  pinMode(inpA5, INPUT_PULLUP);

  //setup output pins
  pinMode(outA4, OUTPUT);
  pinMode(outD2, OUTPUT);
  pinMode(outD3, OUTPUT);
  pinMode(outD4, OUTPUT);
  
  pinMode(outD6, OUTPUT);
  pinMode(outD7, OUTPUT);
  pinMode(outD8, OUTPUT);
  pinMode(outD9, OUTPUT);
  pinMode(outD10, OUTPUT);
  pinMode(outD11, OUTPUT);
  pinMode(outD12, OUTPUT);

}

void loop() {
  while (true){
    armed = digitalRead(inpA0);
    if (armed){
      digitalWrite(outD6,HIGH);   //LED Armed HIGH
    }
    else{
      digitalWrite(outD6,LOW);    //LED Armed LOW
    }
        
    if (FS_locked){
      
      //try to unlock KS
      if (armed){
        continue;
      }
      else{
        FS_locked = false;
        digitalWrite(outD3,LOW);   //LED Locked LOW
        continue;
      }
    }
    
    //KS not locked
    else{
      //OtA KS test
      if (digitalRead(inpA1)){
        digitalWrite(outD11,HIGH);    //LED OtA KS HIGH
        
        //HW KS test
        if(digitalRead(inpA2)){
          digitalWrite(outD11,HIGH);    //LED HW KS HIGH
          
          //SW KS test
          if (digitalRead(inpA3)){
            digitalWrite(outD9,HIGH);    //LED SW KS HIGH
            digitalWrite(outD2,LOW);    //MCU mosfet --- MAIN OUTPUT set LOW
            all_sys_go = false;
            continue;
          }
          else{
            digitalWrite(outD9,LOW);    //LED SW KS LOW
            if(armed){
              //Set MAIN OUTPUT HIGH
              digitalWrite(outD2,HIGH);    //MCU mosfet --- MAIN OUTPUT set HIGH
              all_sys_go = true;
              continue;
            }
            else{
              digitalWrite(outD2,LOW);    //MCU mosfet --- MAIN OUTPUT set LOW
              all_sys_go = false;
              continue;
            }
          }
        }
        //HW KS low
        else{
          digitalWrite(outD2,LOW);    //MCU mosfet --- MAIN OUTPUT set LOW
          digitalWrite(outD11,LOW);    //LED HW KS LOW
          FS_locked = true;
          all_sys_go = false;
        }
      }
      //OtA KS low
      else{
        digitalWrite(outD11,LOW);    //LED OtA KS LOW
        digitalWrite(outD2,LOW);    //MCU mosfet --- MAIN OUTPUT set LOW
        FS_locked = true;
      }    
    }
    status_lights();
  }
}

void status_lights(){
  if (all_sys_go){
    if(digitalRead(inpA5)){
      //Manual
      digitalWrite(outD12,LOW);    //RED status pin 
      digitalWrite(outD8,LOW);    //GREEN status pin 
      digitalWrite(outD7,LOW);    //BLUE status pin 
      digitalWrite(outD4,HIGH);    //YELLOW status pin 
    }
    else{
      //Autonomous
      digitalWrite(outD12,LOW);    //RED status pin 
      digitalWrite(outD8,HIGH);    //GREEN status pin 
      digitalWrite(outD7,LOW);    //BLUE status pin 
      digitalWrite(outD4,LOW);    //YELLOW status pin 
    }
  }
  else{
    //KS triggered
    digitalWrite(outD12,HIGH);    //RED status pin 
    digitalWrite(outD8,LOW);    //GREEN status pin 
    digitalWrite(outD7,LOW);    //BLUE status pin 
    digitalWrite(outD4,LOW);    //YELLOW status pin 
  }
}
