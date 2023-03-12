#include <failSafe.c>

void failSafeStatus(int failSafeIn,int failSafeOut, int softKillIn, int softKillOut){
  /*As per specification, if and only if both software and hardware fail signals safe are high, 
  are the outputs high, otherwise both are low*/
  if(digitalRead(failSafeIn) == HIGH && digitalRead(softKillIn) == HIGH){ 
    digitalWrite(failSafeOut, HIGH);
    digitalWrite(softKillOut, HIGH);
  }
  else{
    digitalWrite(failSafeOut, LOW);
    digitalWrite(softKillOut, LOW);
  }
}


void operatingModeStatus(int hardOpModeIn, int hardOpModeOut, int softOpModeIn, int softOpModeOut){
  //If the input signal goes high, we output high
  if(digitalRead(hardOpModeIn) == HIGH){
    digitalWrite(hardOpModeOut, HIGH);
  }
  else{
    digitalWrite(hardOpModeOut, LOW);
  }

  //If the input signal goes high we output high.
  if(digitalRead(softOpModeIn) == HIGH){
    digitalWrite(softOpModeOut, HIGH);
  }
  else{
    digitalWrite(softOpModeOut, LOW);
  }
}