// for first joystick
const int VRx1 = A4;  // X-axis
const int VRy1 = A5;  // Y-axis
const int SW1 = 4;    // Switch

// for second joystick
const int VRx2 = A6;  // X-axis
const int VRy2 = A7;  // Y-axis
const int SW2 = 5;    // Switch

int SwitchVariable1 = 0;
int SwitchVariable2 = 0;

bool previousSwitchState1 = HIGH;
bool previousSwitchState2 = HIGH; 

String previousCarModeClawMode1 = "S";
String previousCarModeClawMode2 = "S";
String previousCarModeClawJointMode = "S";
String previousCarModeArmJoint1Mode = "S";
String previousCarModeArmJoint2Mode = "S";
String previousClawModeClawJointMode = "S";
String previousClawModeArmJoint1Mode = "S";
String previousClawModeArmJoint2Mode = "S";
void setup() {
  Serial.begin(9600);
  // for first joystick
  pinMode(SW1, INPUT_PULLUP);  // Set the switch pin as input with internal pull-up resistor
  // for second joystick
  pinMode(SW2, INPUT_PULLUP);  // Set the switch pin as input with internal pull-up resistor
}

void loop() {
  // for first joystick
  int xValue1 = analogRead(VRx1);  // Read X-axis value
  int yValue1 = analogRead(VRy1);  // Read Y-axis value
  int switchState1 = digitalRead(SW1);  // Read the switch state

  // for second joystick
  int yValue2 = analogRead(VRx2);  // Read X-axis value
  int xValue2 = analogRead(VRy2);  // Read Y-axis value
  int switchState2 = digitalRead(SW2);  // Read the switch state

  // Handle first joystick switch press
  if (switchState1 == LOW && previousSwitchState1 == HIGH) {
    SwitchVariable1++;
    Serial.print("SwitchVarible1: ");
    Serial.println(SwitchVariable1);
  }
  previousSwitchState1 = switchState1;

  // Handle second joystick switch press
  if (switchState2 == LOW && previousSwitchState2 == HIGH) {
    SwitchVariable2++;
    Serial.print("SwitchVarible2: ");
    Serial.println(SwitchVariable2);
  }
  previousSwitchState2 = switchState2;

  // Reset SwitchVarible1 every 2 presses
  if (SwitchVariable1 == 2) {
    SwitchVariable1 = 0;
    Serial.print("SwitchVarible1 reset to: ");
    Serial.println(SwitchVariable1);
  }

  // Reset SwitchVarible2 every 4 presses
  if (SwitchVariable2 == 2) {
    SwitchVariable2 = 0;
    Serial.print("SwitchVarible2 reset to: ");
    Serial.println(SwitchVariable2);
  }

  // Assuming xValue1, yValue1, xValue2, yValue2, SwitchVariable1, and SwitchVariable2 are defined and updated elsewhere
  if (SwitchVariable1 == 0 && SwitchVariable2 == 0) {
  car_mode_and_claw_joint_mode(xValue1,yValue1,xValue2,yValue2); 
  } else if (SwitchVariable1 == 0 && SwitchVariable2 == 1) {
  car_mode_and_claw_mode_1(xValue1,yValue1,xValue2,yValue2);
  } else if (SwitchVariable1 == 1 && SwitchVariable2 == 0) {
    
  } else if (SwitchVariable1 == 1 && SwitchVariable2 == 1) {
  
  }
  delay(100);  // Small delay to make the output readable
}

void car_mode_and_claw_mode_1(int xValue1, int yValue1, int xValue2, int yValue2) {
  String currentCarModeClawMode1 = "S";  // Default to 'S' for stop
  if (xValue1 > 900 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawMode1 = "R";  // Right
  } 
  else if (xValue1 < 100 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawMode1 = "L";  // Left
  }
  else if (xValue2 < 100 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawMode1 = "Z";  // Left
  } 
  else if (xValue2 > 900 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawMode1 = "Y";  // Left
  } 
  else if (xValue1 > 900 && yValue2 > 900) {
    currentCarModeClawMode1 = "RC";
  }
  else if (xValue1 > 900 && yValue2 < 100) {
    currentCarModeClawMode1 = "RO";
  }
  else if (xValue1 > 900 && xValue2 > 900) {
    currentCarModeClawMode1 = "RY";
  }
  else if (xValue1 > 900 && xValue2 < 100) {
    currentCarModeClawMode1 = "RZ";
  }
  else if (xValue1 < 100 && yValue2 > 900) {
    currentCarModeClawMode1 = "LC";
  }
  else if (xValue1 < 100 && yValue2 < 100) {
    currentCarModeClawMode1 = "LO";
  }
  else if (xValue1 < 100 && xValue2 > 900) {
    currentCarModeClawMode1 = "LY";
  }
  else if (xValue1 < 100 && xValue2 < 100) {
    currentCarModeClawMode1 = "LZ";
  }
  else if (yValue1 > 900 && yValue2 > 900) {
    currentCarModeClawMode1 = "FC";
  }
  else if (yValue1 > 900 && yValue2 < 100) {
    currentCarModeClawMode1 = "FO";
  }
  else if (yValue1 < 100 && yValue2 > 900) {
    currentCarModeClawMode1 = "BC";
  }
  else if (yValue1 < 100 && yValue2 < 100) {
    currentCarModeClawMode1 = "BO";
  }
  else if (yValue1 > 900 && xValue2 > 900) {
    currentCarModeClawMode1 = "FY";
  }
  else if (yValue1 > 900 && xValue2 < 100) {
    currentCarModeClawMode1 = "FZ";
  }
  else if (yValue1 < 100 && xValue2 > 900) {
    currentCarModeClawMode1 = "BY";
  }
  else if (yValue1 < 100 && xValue2 < 100) {
    currentCarModeClawMode1 = "BZ";
  }
  else if (yValue1 > 900 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawMode1 = "F";  // Forward
  }
  else if (yValue1 < 100 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawMode1 = "B";  // Backward
  }
  else if (yValue2 > 900 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawMode1 = "C";
  }
  else if (yValue2 < 100 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawMode1 = "O";
  }
  else {
    currentCarModeClawMode1 = "S"; 
  }
    Serial.println(currentCarModeClawMode1);

}

void car_mode_and_claw_joint_mode(int xValue1, int yValue1, int xValue2, int yValue2) {
  String currentCarModeClawJointMode = "S";  // Default to 'S' for stop
  if (xValue1 > 900 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawJointMode = "Y";  // Right
  } 
  else if (xValue1 < 100 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawJointMode = "Z";  // Left
  }
  else if (xValue2 < 100 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawJointMode = "D";  // Left
  } 
  else if (xValue2 > 900 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawJointMode = "U";  // Left
  }
  else if(xValue1 > 900 && yValue2 > 900 ) {
    currentCarModeClawJointMode = "RD";
  }
  else if(xValue1 > 900 && yValue2 < 100 ) {
    currentCarModeClawJointMode = "RU";
  }
  else if(xValue1 < 100 && yValue2 > 900 ) {
    currentCarModeClawJointMode = "LD";
  }
  else if(xValue1 < 100 && yValue2 < 100 ) {
    currentCarModeClawJointMode = "LU";
  }
  else if(yValue1 > 900 && yValue2 > 900 ) {
    currentCarModeClawJointMode = "FD";
  }
  else if(yValue1 > 900 && yValue2 < 100 ) {
    currentCarModeClawJointMode = "FU";
  }
  else if(yValue1 < 100 && yValue2 > 900 ) {
    currentCarModeClawJointMode = "BD";
  }
  else if(yValue1 < 100 && yValue2 < 100 ) {
    currentCarModeClawJointMode = "BU";
  }
  else if(yValue1 > 900 && xValue2 > 900 ) {
    currentCarModeClawJointMode = "FR";
  }
  else if(yValue1 > 900 && xValue2 < 100 ) {
    currentCarModeClawJointMode = "FL";
  }
  else if(yValue1 < 100 && xValue2 > 900 ) {
    currentCarModeClawJointMode = "BR";
  }
  else if(yValue1 < 100 && xValue2 < 100 ) {
    currentCarModeClawJointMode = "BL";
  }
  else if (yValue1 > 900 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawJointMode = "J";  // Forward
  } else if (yValue1 < 100 && xValue2 < 600 && xValue2 > 400 && yValue2 < 600 && yValue2 > 400) {
    currentCarModeClawJointMode = "K";  // Backward
  }
  else if (yValue2 > 900 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawJointMode = "M";  // Forward
  } else if (yValue2 < 100 && xValue1 < 600 && xValue1 > 400 && yValue1 < 600 && yValue1 > 400) {
    currentCarModeClawJointMode = "N";  // Backward
  }
  else{
    currentCarModeClawJointMode = "S";
  }
    Serial.println(currentCarModeClawJointMode);

}

