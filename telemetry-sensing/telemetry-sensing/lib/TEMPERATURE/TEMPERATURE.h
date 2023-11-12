#include <Arduino.h>

#define TEMP_PIN_0 A0 // ESC 1
#define TEMP_PIN_1 A1 // ESC 2
#define TEMP_PIN_2 A2 // ESC 3
#define TEMP_PIN_3 A3 // ESC 4
#define TEMP_PIN_4 A6 // Ambient 2 (PDB)
#define TEMP_PIN_5 A7 // Ambient 1 (Ideal Diode)
#define TEMP_RES 4700 //resistance of thermistor at room temperature
#define TEMP_VDRES 10000 //resistance of voltage divider
#define TEMP_BETA 3799.42 //beta value of thermistor
#define TEMP_AMB 298.15 //ambient temperature in Kelvin
#define Voltage 5.000 //voltage of arduino

namespace TEMPERATURE{
    void init();
    float floatMap(float x, float in_min, float in_max, float out_min, float out_max);
    float getVoltage(int16_t pin); // Calculate the voltage drop across the thermistor
    float voltageToResistance(int16_t pin);
    float resistanceToTemp(int16_t pin); // Calculate temperature in Kelvin using exponential law
    float KtoC(float T_in_K); // Convert °C to K
    
    float* getTemps(); // Returns a float array containing the temperature values of the 6 sensors
}