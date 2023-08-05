#include <failSafe.h>

bool failSafeStatus(int HARDWAREKILLSWITCHTRIG, int SOFTWAREKILLSWITCHTRIG){
  bool failsafeTriggered = false;

  /*
  As per specification, if and only if both software and hardware fail signals safe are high
  */
  if (digitalRead(HARDWAREKILLSWITCHTRIG) == LOW) { 
    failsafeTriggered = true;
  }
  if (digitalRead(SOFTWAREKILLSWITCHTRIG) == LOW) {
    failsafeTriggered = true;
  }

  return failsafeTriggered;
}

int operatingModeStatus(int HARDWAREOPERATINGMODE){
  /*
  -1: ERROR
  
  0: Hardware operation mode
  1: Software operation mode
  */
  int operationMode = -1;

  if (digitalRead(HARDWAREOPERATINGMODE) == LOW) {
    operationMode = 0;
  }
  if (digitalRead(HARDWAREOPERATINGMODE) == HIGH) {
    operationMode = 1;
  }

  return operationMode;
}
