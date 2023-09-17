// defines pins numbers
const int trigPin = 1;
const int echoPin = 2;
const int buzzer = 6;

//Distance when cover is on 
const int distanceClosed = 1;

// defines variables
long duration;
int distance;

bool isClosed();

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  if (isClosed()) {
    tone(buzzer, 1000);
    delay(1000);
  }
}

bool isClosed() {
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
  distance = duration * 0.034 / 2;
  return distance>distanceClosed;
}
