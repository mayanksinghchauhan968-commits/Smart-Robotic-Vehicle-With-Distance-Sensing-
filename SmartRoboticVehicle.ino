#include <Servo.h>
#include <AFMotor.h>

#define Echo A0
#define Trig A1
#define SERVO_PIN 10
#define SPEED 170
#define SERVO_CENTER 103

// ==============================
// NOTE ON CONTROL MODES
// ==============================
// This car currently runs in BLUETOOTH CONTROL mode only (via mobile app).
// Obstacle() and voicecontrol() are implemented but not currently reliable —
// kept here for future upgrade/debugging. They are intentionally not called
// in loop().

char value;
int distance;
int leftDistance;
int rightDistance;

Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(SERVO_PIN);
  M1.setSpeed(SPEED);
  M2.setSpeed(SPEED);
  M3.setSpeed(SPEED);
  M4.setSpeed(SPEED);
}

void loop() {
  Bluetoothcontrol();

  // Future upgrade — not currently active:
  // Obstacle();
  // voicecontrol();
}

// ==============================
// BLUETOOTH CONTROL (active mode)
// Receives single-character commands from a mobile Bluetooth app
// F = forward, B = backward, L = left, R = right, S = stop
// ==============================
void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }

  if (value == 'F') {
    forward();
  } else if (value == 'B') {
    backward();
  } else if (value == 'L') {
    left();
  } else if (value == 'R') {
    right();
  } else if (value == 'S') {
    Stop();
  }
}

// ==============================
// OBSTACLE AVOIDANCE (WIP — not currently active)
// Uses ultrasonic sensor + servo sweep to check left/right before turning
// ==============================
void Obstacle() {
  distance = ultrasonic();

  if (distance <= 12) {
    Stop();
    backward();
    delay(100);
    Stop();

    leftDistance = checkLeft();
    servo.write(SERVO_CENTER);
    delay(800);

    rightDistance = checkRight();
    servo.write(SERVO_CENTER);

    if (leftDistance < rightDistance) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else if (leftDistance > rightDistance) {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

// ==============================
// VOICE CONTROL (WIP — not currently active)
// Expects symbolic command characters from a voice-to-text app
// ^ = forward, - = backward, < = left, > = right, * = stop
// ==============================
void voicecontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);

    if (value == '^') {
      forward();
    } else if (value == '-') {
      backward();
    } else if (value == '<') {
      leftDistance = checkLeft();
      servo.write(SERVO_CENTER);
      if (leftDistance >= 10) {
        left();
        delay(500);
        Stop();
      } else {
        Stop();
      }
    } else if (value == '>') {
      rightDistance = checkRight();
      servo.write(SERVO_CENTER);
      if (rightDistance >= 10) {
        right();
        delay(500);
        Stop();
      } else {
        Stop();
      }
    } else if (value == '*') {
      Stop();
    }
  }
}

// ==============================
// ULTRASONIC DISTANCE READING
// Returns distance in cm
// ==============================
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2;
  return cm;
}

// ==============================
// MOTOR CONTROL
// ==============================
void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void right() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void left() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

// ==============================
// SERVO SWEEP + DISTANCE CHECK
// checkRight() turns servo to look right and measures distance
// checkLeft() turns servo to look left and measures distance
// ==============================
int checkRight() {
  servo.write(20);
  delay(800);
  return ultrasonic();
}

int checkLeft() {
  servo.write(180);
  delay(800);
  return ultrasonic();
}
