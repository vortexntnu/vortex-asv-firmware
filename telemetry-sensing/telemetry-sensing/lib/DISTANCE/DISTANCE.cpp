#include <DISTANCE.h>

namespace DISTANCE{
    
    void init() {
        pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
        pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
        pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an Output
        pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input
    }

    uint32_t get_distance(int trigPin, int echoPin){
        uint32_t duration;

        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
       
        return duration * 0.34 / 2;
    }

    bool lid_is_open() {
        // Blocks buzzer from making sound if the switch for the buzzer is turned off
        uint32_t distanceSensor1 = get_distance(trigPin1, echoPin1);
        uint32_t distanceSensor2 = get_distance(trigPin2, echoPin2);

        if ((distanceSensor1 >= distanceClosed) or (distanceSensor2 >= distanceClosed)) {
            return true;
        }
        else {         // Does not sound alarm
            return false;
        }
    }
}