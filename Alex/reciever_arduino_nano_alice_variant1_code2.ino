#include <Servo.h>

// Define the servos
Servo clawServo;
Servo clawRotationServo;
Servo clawJointServo;
Servo middleJointServo1;
Servo middleJointServo2;
Servo baseJointServo1;
Servo baseJointServo2;

// Initial coordinates
float x = 20.0;
float y = 20.0;

// Define lengths of arm segments
const float L1 = 15.0;
const float L2 = 20.0;
const float L3 = 20.0;

// Pin assignments for servos
const int clawPin = 8;
const int clawRotationPin = 9;
const int clawJointPin = 10;
const int middleJointPin1 = 11;
const int middleJointPin2 = 12;
const int baseJointPin1 = 13;
const int baseJointPin2 = 14;

// Function to calculate angles using inverse kinematics
void calculateIK(float x, float y, float &theta1, float &theta2) {
    float r = sqrt(x * x + y * y);

    // Ensure the target point is reachable
    if (r > (L2 + L3) || r < abs(L2 - L3)) {
        Serial.println("Target point is out of reach");
        return;
    }

    float D = (r * r - L2 * L2 - L3 * L3) / (2 * L2 * L3);
    theta2 = atan2(sqrt(1 - D * D), D);
    theta1 = atan2(y, x) - atan2(L3 * sin(theta2), L2 + L3 * cos(theta2));
}

// Function to move servos to calculated angles
void moveServos(float theta1, float theta2) {
    int angle1 = constrain(theta1 * 180.0 / PI, 0, 180);
    int angle2 = constrain(theta2 * 180.0 / PI, 0, 180);

    baseJointServo1.write(angle1);
    baseJointServo2.write(180 - angle1); // Opposite direction

    middleJointServo1.write(angle2);
    middleJointServo2.write(180 - angle2); // Opposite direction
}

void setup() {
    // Attach the servos to the pins
    clawServo.attach(clawPin);
    clawRotationServo.attach(clawRotationPin);
    clawJointServo.attach(clawJointPin);
    middleJointServo1.attach(middleJointPin1);
    middleJointServo2.attach(middleJointPin2);
    baseJointServo1.attach(baseJointPin1);
    baseJointServo2.attach(baseJointPin2);

    // Initialize servos to default positions
    clawServo.write(90);
    clawRotationServo.write(90);
    clawJointServo.write(90);
    middleJointServo1.write(90);
    middleJointServo2.write(90);
    baseJointServo1.write(90);
    baseJointServo2.write(90);

    // Initialize serial communication
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        char received = Serial.read();
        Serial.println(received);

        if (received == 'F') {
            y += 0.3;
        } else if (received == 'B') {
            y -= 0.3;
        } else if (received == 'R') {
            x += 0.3;
        } else if (received == 'L') {
            x -= 0.3;
        }

        // Constrain the coordinates to avoid reaching unreachable points
        x = constrain(x, -40, 40);
        y = constrain(y, 0, 40);

        float theta1 = 0, theta2 = 0;
        calculateIK(x, y, theta1, theta2);
        moveServos(theta1, theta2); // Small delay to avoid multiple commands being processed too quickly
    }
}

// Function to control the claw
void controlClaw(bool open) {
    if (open) {
        clawServo.write(0); // Open position
    } else {
        clawServo.write(90); // Close position
    }
}

// Function to control claw rotation
void controlClawRotation(int angle) {
    clawRotationServo.write(angle);
}
