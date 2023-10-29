#include <DISTANCE.h>

namespace DISTANCE{
    
    void CoverSensor_init() {
        pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
        pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
        pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an Output
        pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input
    }

    bool Test_distance_sensor(int trigPin, int echoPin){

        uint32_t duration;

        uint32_t distance;

        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
        // Calculating the distance
        distance = duration * 0.34 / 2;
        //Serial.println(distance);
        //return distance;
        return distance > distanceClosed;

    }

    bool Is_lid_open() {
    
        // Blocks buzzer from making sound if the switch for the buzzer is turned off
        if (Test_distance_sensor(trigPin1, echoPin1) or Test_distance_sensor(trigPin2, echoPin2)) {
            return true;
            delay(100);
        }
        else{         // Does not sound alarm
            return false;
        }
    }

    uint32_t Getdistance(int trigPin, int echoPin){
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
}