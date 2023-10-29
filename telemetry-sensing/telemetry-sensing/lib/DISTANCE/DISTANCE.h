#include <Arduino.h>



#define trigPin1 4
#define echoPin1 3

#define trigPin2 8
#define echoPin2 7

//Distance when cover is on 
#define distanceClosed 130; //[mm]




namespace DISTANCE{

    void CoverSensor_init();
    bool Test_distance_sensor(int trigPin, int echoPin);
    bool Is_lid_open();
    uint32_t Getdistance(int trigPin, int echoPin); //function used for debugging
}