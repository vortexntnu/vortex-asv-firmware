#include <TEMPERATURE.h>

namespace TEMPERATURE{
  void init(){
    pinMode(TEMP_PIN_0, INPUT); 
    pinMode(TEMP_PIN_1, INPUT); 
    pinMode(TEMP_PIN_2, INPUT);
    pinMode(TEMP_PIN_3, INPUT);
    pinMode(TEMP_PIN_4, INPUT); 
    pinMode(TEMP_PIN_5, INPUT);  
  }
  
  float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  float getVoltage(int16_t pin) {
    return Voltage - floatMap(analogRead(pin), 0, 1023, 0.000, Voltage);
  }

  float voltageToResistance(int16_t pin) {
    return (getVoltage(pin)*TEMP_VDRES)/(Voltage-getVoltage(pin));
  }

  float resistanceToTemp(int16_t pin) {

    return pow((1/TEMP_AMB)+(1/TEMP_BETA)*log(voltageToResistance(pin)/TEMP_RES),-1);
  }

  float KtoC(float T_in_K) {
    return T_in_K - 273.15;
  }

  float* getTemps(){
    float* temperatures = new float[6]{
      KtoC(resistanceToTemp(TEMP_PIN_0)),
      KtoC(resistanceToTemp(TEMP_PIN_1)),
      KtoC(resistanceToTemp(TEMP_PIN_2)),
      KtoC(resistanceToTemp(TEMP_PIN_3)),
      KtoC(resistanceToTemp(TEMP_PIN_4)),
      KtoC(resistanceToTemp(TEMP_PIN_5))
      };
    return temperatures;
  }

}