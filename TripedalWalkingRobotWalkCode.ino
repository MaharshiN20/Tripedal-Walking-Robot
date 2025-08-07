#include <Servo.h>

const int trigPin = 11;
const int echoPin = 2;
const int distanceThreshold = 55;  // cm
int u = 70;
int pos = 0;
const int servoPin =9;
Servo s1;

volatile unsigned long startTime = 0;
volatile unsigned long echoDuration = 0;
volatile bool isEchoHigh = false;

unsigned long lastMeasurement = 0;
int distance = 0;
bool obstacleDetected = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  // Attach the single servo
  s1.attach(servoPin);
  for (int i =0; i <=(u); i++) {
    s1.write(i);
    delay(5);
} // Neutral position

  // Attach interrupt to echo pin
  attachInterrupt(digitalPinToInterrupt(echoPin), echoISR, CHANGE);
}

void loop() {
  // Trigger ultrasonic sensor every 50ms
  if (millis() - lastMeasurement >= 50) {
    triggerSensor();
    lastMeasurement = millis();
    noInterrupts();
    unsigned long duration = echoDuration;
    interrupts();
    distance = duration * 0.0343 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < distanceThreshold && distance > 0) {
      if (!obstacleDetected) {
        resetPos();  // Stop movement
        obstacleDetected = true;
      }
      return;
    }
     else {
      obstacleDetected = false;
      servoUp();
      delay(1000)   ; // Step forward
        // Prepare next step
    }
  }
}

void triggerSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void echoISR() {
  if (digitalRead(echoPin) == HIGH) {
    startTime = micros();
    isEchoHigh = true;
  } else {
    if (isEchoHigh) {
      echoDuration = micros() - startTime;
      isEchoHigh = false;
    }
  }
}

// === Servo control functions ===
void servoUp() {
    for (pos = u; pos >=(u-25); pos--) {
    s1.write(pos);
    delay(1);
      }
  delay(1000);
      for(int i = pos; i <= (u+3);i++){
        s1.write(i);
        delay(7);
}
}

void resetPos() {
  for (int i =u; i <=(u+3); i++) {
    s1.write(i);
    delay(5);
}
exit(0);
}