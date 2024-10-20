#include <Servo.h>

Servo clawJaw;      // Servo for the claw jaw
Servo clawRotation; // Servo for rotating the claw
Servo clawUpDown;   // Servo for moving the claw up and down

Servo joint1a;      // First servo for the first joint
Servo joint1b;      // Second servo for the first joint (opposite direction)

Servo joint2a;      // First servo for the second joint
Servo joint2b;      // Second servo for the second joint (opposite direction)

// Define pin numbers for the servos
const int clawJawPin = 2;
const int clawRotationPin = 3;
const int clawUpDownPin = 4;

const int joint1aPin = 12;
const int joint1bPin = 13;

const int joint2aPin = 14;
const int joint2bPin = 19;

#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10

#define ENA 6
#define ENB 11

#define IN5 16
#define IN6 15
#define IN7 17
#define IN8 18

#define ENC 5
#define END 20

int Speed1 = 120;
int Speed2 = 200;
int clawRotationAngle = 90;
int clawJawAngle = 35;
int clawJointAngle = 90;
int Joint1Angle = 90;
int Joint2Angle = 90;
char lastCommand = 'X';

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Attach servos to their respective pins
  clawJaw.attach(clawJawPin);
  clawRotation.attach(clawRotationPin);
  clawUpDown.attach(clawUpDownPin);
  
  joint1a.attach(joint1aPin);
  joint1b.attach(joint1bPin);

  joint2a.attach(joint2aPin);
  joint2b.attach(joint2bPin);
}

void loop() {
  if (Serial.available()) { // Check if data is available to read
    lastCommand = Serial.read(); // Read the message
    Serial.println(lastCommand); // Print the received message
  }

  if (lastCommand == 'F') {
    
    analogWrite(ENA, Speed1);
    analogWrite(ENB, Speed1);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    analogWrite(ENC, Speed2);
    analogWrite(END, Speed2);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
  } else if (lastCommand == 'B') {
    
    analogWrite(ENA, Speed1);
    analogWrite(ENB, Speed1);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(ENC, Speed2);
    analogWrite(END, Speed2);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, HIGH);
  } else if (lastCommand == 'S') {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
  } else if (lastCommand == 'L') {
    
    analogWrite(ENA, Speed1);
    analogWrite(ENB, Speed1);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(ENC, Speed2);
    analogWrite(END, Speed2);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, HIGH);
  } else if (lastCommand == 'R') {
    
    analogWrite(ENA, Speed1);
    analogWrite(ENB, Speed1);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    analogWrite(ENC, Speed2);
    analogWrite(END, Speed2);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
  } else if (lastCommand == 'Y' && clawRotationAngle < 180) {
    clawRotationAngle += 4;
    clawRotation.write(clawRotationAngle);
    delay(100);
  } else if (lastCommand == 'Z' && clawRotationAngle > 0) {
    clawRotationAngle -= 4;
    clawRotation.write(clawRotationAngle);
    delay(100);
  } else if (lastCommand == 'C' && clawJawAngle < 180) {
    clawJawAngle += 2;
    clawJaw.write(clawJawAngle);
    delay(100);
  } else if (lastCommand == 'O' && clawJawAngle > 0) {
    clawJawAngle -= 2;
    clawJaw.write(clawJawAngle);
    delay(100);
  } else if (lastCommand == 'U' && clawJointAngle < 180) {
    clawJointAngle += 2;
    clawUpDown.write(clawJointAngle);
    delay(100);
  } else if (lastCommand == 'D' && clawJointAngle > 0) {
    clawJointAngle -= 2;
    clawUpDown.write(clawJointAngle);
    delay(100);
  } else if (lastCommand == 'N' && Joint1Angle < 180) {
    Joint1Angle += 2;
    joint1a.write(Joint1Angle);
    joint1b.write(180 - Joint1Angle);
    delay(100);
  } else if (lastCommand == 'M' && Joint1Angle > 0) {
    Joint1Angle -= 2;
    joint1a.write(Joint1Angle);
    joint1b.write(180 - Joint1Angle);
    delay(100);
  } else if (lastCommand == 'J' && Joint2Angle < 180) {
    Joint2Angle += 2;
    joint2a.write(Joint2Angle);
    joint2b.write(180 - Joint2Angle);
    delay(100);
  } else if (lastCommand == 'K' && Joint2Angle > 0) {
    Joint2Angle -= 2;
    joint2a.write(Joint2Angle);
    joint2b.write(180 - Joint2Angle);
    delay(100);
  }
}
