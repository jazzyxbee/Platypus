#include <Stepper.h>  // Include the stepper motor library - in arduino

// Define the number of steps per revolution for stepper motor
const int stepsPerRevolution = 200;  // Adjust this based on  motor

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // Specify the motor pins

// Define the camera trigger pin
const int cameraTriggerPin = 12;  // Adjust this based on setup

void setup() {
  // Set up the stepper motor
  myStepper.setSpeed(60);  // Set the motor speed (adjust as needed)

  // Initialize the serial communication (for debugging)
  Serial.begin(9600);

  // Set the camera trigger pin as an output
  pinMode(cameraTriggerPin, OUTPUT);

}

void loop() {
  int stepSize;
  int numSteps;
  
  // Ask the user for the step size and number of steps
  // Serial.println("Enter step size (in mm): ");
  // while (!Serial.available()) {}  // Wait for user input
  stepSize = 10;
  
  // Serial.println("Enter number of steps: ");
  // while (!Serial.available()) {}  // Wait for user input
  numSteps = 500;

  // Move the stepper motor based on user input
  moveMotor(stepSize, numSteps);
  
  // Trigger the camera
  triggerCamera();
  
  // Delay for some time (adjust as needed)
  delay(800);
}

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
}
