#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "failSafe.h"

//Refer to the last 8 rows of the table https://vortex.a2hosted.com/index.php/ASV_Fail_Safe#Teensy_connections_(SW)
#define HARDWAREKILLSWITCHTRIG_OUT 2
#define SOFTWAREKILLSWITCHTRIG_OUT 3
#define HARDWAREOPERATINGMODE_OUT 4
#define SOFTWAREOPERATINGMODE_OUT 5
#define HARDWAREKILLSWITCHTRIG_IN 20
#define SOFTWAREKILLSWITCHTRIG_IN 21
#define HARDWAREOPERATINGMODE_IN 22
#define SOFTWAREOPERATINGMODE_IN 23

#define ESC_PIN1 28
#define ESC_PIN2 29
#define ESC_PIN3 36
#define ESC_PIN4 37
#define ARMING_PWM 1500 // 1500 ms
#define STARTUP_DELAY 15000 // 15 s
#define FAILSAFE_CHECK_INTERVAL 500 // 500 ms
#define I2C_SDA_PIN 18
#define I2C_SCL_PIN 19
#define I2C_ADDRESS 0x21


void arm_thrusters();
void disarm_thrusters();
void drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4);
void receiveMessage(int bytes);

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

unsigned long failsafeTimerLastCheck = 0;
bool isArmed = false;

void setup() {
  // Set up debugging
  Serial.begin(9600);
  delay(5000);

  Serial.println("Configuring failsafe pins...");
  pinMode(HARDWAREKILLSWITCHTRIG_IN, INPUT);
  pinMode(SOFTWAREKILLSWITCHTRIG_IN, INPUT);
  pinMode(HARDWAREOPERATINGMODE_IN, INPUT);
  pinMode(SOFTWAREOPERATINGMODE_IN, INPUT);

  pinMode(HARDWAREKILLSWITCHTRIG_OUT, OUTPUT);
  pinMode(SOFTWAREKILLSWITCHTRIG_OUT, OUTPUT);
  pinMode(HARDWAREOPERATINGMODE_OUT, OUTPUT);
  pinMode(SOFTWAREOPERATINGMODE_OUT, OUTPUT);

  Serial.println("Configuring ESCs...");
  ESC1.attach(ESC_PIN1);
  ESC2.attach(ESC_PIN2);
  ESC3.attach(ESC_PIN3);
  ESC4.attach(ESC_PIN4);
  arm_thrusters();

  Serial.println("Gib a sec :)");
  delay(STARTUP_DELAY);

  Serial.println("Setting up I2C communication...");
  Wire.setSDA(I2C_SDA_PIN);
  Wire.setSCL(I2C_SCL_PIN);
  Wire.begin(I2C_ADDRESS); // Join the I2C bus as a slave
  Wire.onReceive(receiveMessage); // Register the receive event handler
}

void loop() {
  if (millis() - failsafeTimerLastCheck > FAILSAFE_CHECK_INTERVAL) {
    /*
    -1: ERROR
    
    0: Hardware operation mode
    1: Software operation mode
    */
    int operationMode = operatingModeStatus(HARDWAREOPERATINGMODE_IN, HARDWAREOPERATINGMODE_OUT, SOFTWAREOPERATINGMODE_IN, SOFTWAREOPERATINGMODE_OUT);

    bool failsafeTriggered = failSafeStatus(HARDWAREKILLSWITCHTRIG_IN, HARDWAREKILLSWITCHTRIG_OUT, SOFTWAREKILLSWITCHTRIG_IN, SOFTWAREKILLSWITCHTRIG_OUT);
    
    if (isArmed && (failsafeTriggered || operationMode != 1)) {
      Serial.println("Disarming!!!");
      disarm_thrusters();
    }
    else if (!isArmed && !failsafeTriggered && operationMode == 1) {
      Serial.println("Arming...");
      arm_thrusters();
    }

    failsafeTimerLastCheck = millis();
  }
}

void arm_thrusters() {
  isArmed = true;
  ESC1.writeMicroseconds(ARMING_PWM);
  ESC2.writeMicroseconds(ARMING_PWM);
  ESC3.writeMicroseconds(ARMING_PWM);
  ESC4.writeMicroseconds(ARMING_PWM);
}

void disarm_thrusters() {
  isArmed = false;
  drive_thrusters(0, 0, 0, 0);
}

void drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4) {
  ESC1.writeMicroseconds(PWM_ESC1);
  ESC2.writeMicroseconds(PWM_ESC2);
  ESC3.writeMicroseconds(PWM_ESC3);
  ESC4.writeMicroseconds(PWM_ESC4);
}

void receiveMessage(int bytes) {
  if (bytes == 8) { // Check if 8 bytes (4 x 16-bit integers) are received
    int PWM_values[4];

    // Read the I2C data and convert bytes to 16-bit integers
    for (int i = 0; i < 4; i++) {
      int msb = Wire.read();
      int lsb = Wire.read();
      PWM_values[i] = (msb << 8) | lsb;
    }

    // Drive thrusters
    if (isArmed) {
      drive_thrusters(PWM_values[0], PWM_values[1], PWM_values[2], PWM_values[3]);

      // Debugging
      Serial.print("PWM values: ");
      for (int i = 0; i < 4; i++) {
        Serial.print(PWM_values[i]);
        Serial.print(" ");
      }
      Serial.println();
    }
    else {
      Serial.println("Thrusters not armed!");
    }  
  } else {
    disarm_thrusters();
    Serial.println("Invalid data length received!");
  }
}
