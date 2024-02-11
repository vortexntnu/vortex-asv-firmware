#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

#define ESC_PIN1 5
#define ESC_PIN2 6
#define ESC_PIN3 9
#define ESC_PIN4 10
#define ARMING_PWM 1500 // 1500 ms
#define STARTUP_DELAY 1500 // 1.5 s
#define I2C_ADDRESS 0x21

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

void arm_thrusters();
void drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4);
void receiveMessage(int bytes);

void setup() {
  Serial.begin(9600);
  delay(5000);

  Serial.println("Configuring ESCs...");
  ESC1.attach(ESC_PIN1);
  ESC2.attach(ESC_PIN2);
  ESC3.attach(ESC_PIN3);
  ESC4.attach(ESC_PIN4);
  arm_thrusters();

  Serial.println("Gib a sec :)");
  delay(STARTUP_DELAY);

  Serial.println("Setting up I2C communication...");
  Wire.begin(I2C_ADDRESS); // Join the I2C bus as a slave at the specified address
  Wire.onReceive(receiveMessage); // Register the receive event handler
}

void loop() {
  // Main loop remains empty; all actions are handled in receiveMessage
}

void arm_thrusters() {
  ESC1.writeMicroseconds(ARMING_PWM);
  ESC2.writeMicroseconds(ARMING_PWM);
  ESC3.writeMicroseconds(ARMING_PWM);
  ESC4.writeMicroseconds(ARMING_PWM);
}

void drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4) {
  ESC1.writeMicroseconds(PWM_ESC1);
  ESC2.writeMicroseconds(PWM_ESC2);
  ESC3.writeMicroseconds(PWM_ESC3);
  ESC4.writeMicroseconds(PWM_ESC4);
}

// This function is called automatically whenever I2C data is received.
void receiveMessage(int bytes) {
  // Check if the received data is exactly 8 bytes long, as expected
  if (bytes == 8) {
    // Loop to read the 8 bytes (4 x 16-bit values) from the I2C buffer
    int PWM_values[4];
    for (int i = 0; i < 4; i++) {
      // Read the most significant byte (MSB) and least significant byte (LSB) for each value
      int msb = Wire.read();
      int lsb = Wire.read();
      // Combine MSB and LSB to form the 16-bit integer PWM value
      PWM_values[i] = (msb << 8) | lsb;
    }

    // Drive the thrusters with the received PWM values
    drive_thrusters(PWM_values[0], PWM_values[1], PWM_values[2], PWM_values[3]);

    // Log the PWM values for debugging purposes
    Serial.print("PWM values: ");
    for (int i = 0; i < 4; i++) {
      Serial.print(PWM_values[i]);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    // If the received data length does not match the expected 8 bytes, log an error and clear the buffer to reset I2C data transfer
    Serial.println("Invalid data length received!");
    while(Wire.available() > 0) {
      Wire.read();
    }
  }
}
