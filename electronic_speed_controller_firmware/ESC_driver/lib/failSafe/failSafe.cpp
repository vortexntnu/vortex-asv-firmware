#include <failSafe.h>

bool failSafeStatus(int HARDWAREKILLSWITCHTRIG, int SOFTWAREKILLSWITCHTRIG){
  bool failsafeTriggered = false;

  /*
  As per specification, if and only if both software and hardware fail signals safe are high, 
  are the outputs high, otherwise both are low
  */
  if(digitalRead(HARDWAREKILLSWITCHTRIG) == LOW) {
    failsafeTriggered = true;
  }
  if(digitalRead(SOFTWAREKILLSWITCHTRIG) == LOW) {
    failsafeTriggered = true;
  }

  return failsafeTriggered;
}

int operatingModeStatus(int HARDWAREOPERATINGMODE, int SOFTWAREOPERATINGMODE){
  /*
  -1: ERROR
  
  0: Hardware operation mode
  1: Software operation mode
  */
  int operationMode = -1;

  if(digitalRead(SOFTWAREOPERATINGMODE) == HIGH){
    operationMode = 1;
  }

  if(digitalRead(HARDWAREOPERATINGMODE) == HIGH){
    operationMode = 0;
  }

  return operationMode;
}
