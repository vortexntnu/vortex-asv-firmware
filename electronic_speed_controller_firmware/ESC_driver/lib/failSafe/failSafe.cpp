#include <failSafe.h>

bool failSafeStatus(int failSafeIn,int failSafeOut, int softKillIn, int softKillOut){
  bool failsafeTriggered = false;

  /*
  As per specification, if and only if both software and hardware fail signals safe are high, 
  are the outputs high, otherwise both are low
  */
  if(digitalRead(failSafeIn) == HIGH && digitalRead(softKillIn) == HIGH){ 
    digitalWrite(failSafeOut, HIGH);
    digitalWrite(softKillOut, HIGH);
  }
  else{
    failsafeTriggered = true;
    digitalWrite(failSafeOut, LOW);
    digitalWrite(softKillOut, LOW);
  }

  return failsafeTriggered;
}

int operatingModeStatus(int hardOpModeIn, int hardOpModeOut, int softOpModeIn, int softOpModeOut){
  /*
  -1: ERROR
  
	@@ -29,21 +26,13 @@ int operatingModeStatus(int hardOpModeIn, int hardOpModeOut, int softOpModeIn, i
  */
  int operationMode = -1;

  if(digitalRead(softOpModeIn) == HIGH){
    digitalWrite(softOpModeOut, HIGH);
    operationMode = 1;
  }
  else{
    digitalWrite(softOpModeOut, LOW);
  }

  if(digitalRead(hardOpModeIn) == HIGH){
    digitalWrite(hardOpModeOut, HIGH);
    operationMode = 0;
  }
  else{
    digitalWrite(hardOpModeOut, LOW);
  }

  return operationMode;
}
