#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int cameraTriggerPin = 12;  // Out of the way

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);  // Forwards Direction
Stepper myStepperBackwards(stepsPerRevolution, 5, 2, 3, 4); // Backwards Direction

void setup() {
	myStepperBackwards.setSpeed(10);
	Serial.begin(9600); // initialize the serial port
	pinMode(cameraTriggerPin, OUTPUT);
}

void loop() {
  float stepSize = 0.0;
  float numSteps = 0.0; // 1 mm per rotation of screw

  // Ask the user for the step size and number of steps
   Serial.println("Enter step size (in mm): ");
   while (!Serial.available()) {}  // Wait for user input
   stepSize = Serial.parseFloat(); // Read user input
   while (Serial.available()) Serial.read(); // Clear input buffer

  Serial.println("Enter number of steps: ");
  while (!Serial.available()) {}  // Wait for user input
  numSteps = Serial.parseFloat(); // Read user input
  while (Serial.available()) Serial.read(); // Clear input buffer
	
  // Move the stepper motor based on user input
  moveMotor(stepSize, numSteps);

  // Trigger the camera
  // triggerCamera();

  delay(1000);
}


void moveMotor(float stepSize, float numSteps) {
  float steps_mm = 256.0;
	// Calculate the number of steps needed for the specified distance
  for(int i = 0; i < numSteps; i++){
    float stepsToMove = stepSize * steps_mm;
    Serial.println(stepsToMove);

	// Rotate the stepper motor
	  myStepperBackwards.step(stepsToMove);
    delay(1000);
  }
  Serial.println("it move");
}

void triggerCamera() {
	// Send a 5V electric pulse to trigger the camera
	digitalWrite(cameraTriggerPin, HIGH);
	delay(10);  
	digitalWrite(cameraTriggerPin, LOW);
	
  // step one revolution in the other direction:
	Serial.println("counterclockwise");
	myStepper.step(stepsPerRevolution);
	delay(1000);
}
