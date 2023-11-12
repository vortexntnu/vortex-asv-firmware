#include <Arduino.h>

// Distance sensor pins for global usage
#define trigPin1 4
#define echoPin1 3

#define trigPin2 8
#define echoPin2 7

// Distance when cover is on 
#define distanceClosed 130 //[mm]

namespace DISTANCE{
    void init();
    uint32_t get_distance(int trigPin, int echoPin);
    bool lid_is_open();
}