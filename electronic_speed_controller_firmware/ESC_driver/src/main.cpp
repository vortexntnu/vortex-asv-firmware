#include <Arduino.h>
#include "failSafe.c"
//Refer to the last 8 rows of the table https://vortex.a2hosted.com/index.php/ASV_Fail_Safe#Teensy_connections_(SW)
#define FAILSAFESTATUS_OUT 2 
#define FAILSAFESTATUS_IN 23
#define SOFTWAREKILLSWITCHTRIG_OUT 3
#define SOFTWAREKILLSWITCHTRIG_IN 22
#define HARDWAREOPERATINGMODE_OUT 4
#define HARDWAREOPERATINGMODE_IN 21
#define SOFTWAREOPERATINGMODE_OUT 5
#define SOFTWAREOPERATINGMODE_IN 20


void setup() {
  pinMode(FAILSAFESTATUS_IN, INPUT);
  pinMode(SOFTWAREKILLSWITCHTRIG_IN, INPUT);
  pinMode(HARDWAREOPERATINGMODE_IN, INPUT);
  pinMode(SOFTWAREOPERATINGMODE_IN, INPUT);

  pinMode(FAILSAFESTATUS_OUT, OUTPUT);
  pinMode(SOFTWAREKILLSWITCHTRIG_OUT, OUTPUT);
  pinMode(HARDWAREOPERATINGMODE_OUT, OUTPUT);
  pinMode(SOFTWAREOPERATINGMODE_OUT, OUTPUT);
}

void loop() {

  failSafeStatus(FAILSAFESTATUS_IN, FAILSAFESTATUS_OUT, SOFTWAREKILLSWITCHTRIG_IN, SOFTWAREKILLSWITCHTRIG_OUT);

  operatingModeStatus(HARDWAREOPERATINGMODE_IN, HARDWAREOPERATINGMODE_OUT, SOFTWAREOPERATINGMODE_IN, SOFTWAREOPERATINGMODE_OUT);
  
}