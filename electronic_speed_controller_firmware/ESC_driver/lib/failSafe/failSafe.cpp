#include <failSafe.h>

bool failSafeStatus(int HARDWAREKILLSWITCHTRIG, int SOFTWAREKILLSWITCHTRIG){
  bool failsafeTriggered = false;

  /*
  As per specification, if and only if both software and hardware fail signals safe are high, 
  are the outputs high, otherwise both are low
  */
  if (digitalRead(HARDWAREKILLSWITCHTRIG) == HIGH) { 
    failsafeTriggered = true;
  }
  else if (digitalRead(SOFTWAREKILLSWITCHTRIG) == HIGH){
    failsafeTriggered = true;
  }

  return failsafeTriggered;
}

int operatingModeStatus(int SOFTWAREOPERATINGMODE, int HARDWAREOPERATINGMODE){
  /*
  -1: ERROR
  
	@@ -29,21 +26,13 @@ int operatingModeStatus(int hardOpModeIn, int hardOpModeOut, int softOpModeIn, i
  */
  int operationMode = -1;

  if(digitalRead(HARDWAREOPERATINGMODE) == HIGH){
    operationMode = 0;
  }
  else if(digitalRead(SOFTWAREOPERATINGMODE) == HIGH){
    operationMode = 1;
  }

  return operationMode;
}
