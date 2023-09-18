#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
const int cameraTriggerPin = 12;  // Adjust this based on setup

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);  // Specify the motor pins
Stepper myStepperBackwards(stepsPerRevolution, 5, 2, 3, 4);

void setup() {
	// set the speed at 60 rpm:
	myStepper.setSpeed(50);
	// initialize the serial port:
	Serial.begin(9600);
	pinMode(cameraTriggerPin, OUTPUT);

}

void loop() {
	// step one revolution  in one direction:
	Serial.println("anticlockwise");
	myStepper.step(stepsPerRevolution);
	delay(100);
	
	Serial.println("clockwise");
	myStepperBackwards.step(stepsPerRevolution);
	delay(100);

	// Define the number of steps per revolution for stepper motor
	//  const int stepsPerRevolution = 200;  // Adjust this based on  motor

	// Define the camera trigger pin
	const int cameraTriggerPin = 12;  // Adjust this based on setup
	
}

//  void loop2() {
//    int stepSize;
//    int numSteps;

// 1 mm per rotation of screw
//
//    // Ask the user for the step size and number of steps
//    // Serial.println("Enter step size (in mm): ");
//    // while (!Serial.available()) {}  // Wait for user input
//    stepSize = 10;
//
//    // Serial.println("Enter number of steps: ");
//    // while (!Serial.available()) {}  // Wait for user input
//    numSteps = 500;
//
//    // Move the stepper motor based on user input
//    moveMotor(stepSize, numSteps);
//
//    // Trigger the camera
//    triggerCamera();
//
//    // Delay for some time (adjust as needed)
//    delay(800);
//  }

void moveMotor(int stepSize, int numSteps) {
	// Calculate the number of steps needed for the specified distance
	int stepsToMove = (numSteps * stepsPerRevolution) / (stepSize * 360.0);

	// Rotate the stepper motor
	myStepper.step(stepsToMove);
}

void triggerCamera() {
	// Send a 5V electric pulse to trigger the camera
	digitalWrite(cameraTriggerPin, HIGH);
	delay(10);  // Adjust the delay as needed
	digitalWrite(cameraTriggerPin, LOW);
	// step one revolution in the other direction:
	Serial.println("counterclockwise");
	myStepper.step(stepsPerRevolution);
	delay(1000);
}
