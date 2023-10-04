#include <Stepper.h>

const int stepsPerRevolution = 2048;
const int cameraTriggerPin = 12; // 13?

Stepper myStepperBackwards(stepsPerRevolution, 2, 3, 4, 5); // Forwards Direction
Stepper myStepperForwards(stepsPerRevolution, 5, 2, 3, 4);  // Backwards Direction

void setup() {
  myStepperForwards.setSpeed(10);
  myStepperBackwards.setSpeed(10);
  Serial.begin(9600);
  pinMode(cameraTriggerPin, OUTPUT);
}

void clearInputBuffer() {
  while (Serial.available() > 0) {
    char c = Serial.read();
  }
}

void loop() {
  float stepSize = 0.0;
  float numSteps = 0.0;
  int counter = 0; // keep track of origin
  bool shouldExit = false;

  Serial.println(" ");
  Serial.println("Press any key to start...");
  while (!Serial.available()) {} // Wait for any key press to start
  clearInputBuffer(); // Clear any residual input

  while (!shouldExit) {
    // Ask the user for the step size
    Serial.println("Enter step size (in mm): ");
    while (!Serial.available()) {} // Wait for user input
    stepSize = Serial.parseFloat(); // Read user input
    clearInputBuffer(); // Clear input buffer

    // Ask the user for the number of steps
    Serial.println("Enter number of steps (maximum 7): ");
    while (!Serial.available()) {}
    numSteps = Serial.parseFloat();
    clearInputBuffer(); // Clear input buffer

    // Ask the user for direction
    Serial.println("Forwards (F) or backwards (B)?: ");
    while (!Serial.available()) {}
    String directionString = Serial.readString(); // Read user input as a string
    directionString.trim(); // Remove leading/trailing whitespace
    directionString.toLowerCase(); // Convert the user input to lowercase

    // Move the stepper motor based on user input
    if (directionString.equals("f") && numSteps < 8) {
      for (int i = 0; i < numSteps; i++) {
        moveMotorForwards(stepSize, 1, 0); // Move forward by 1 step
        counter++;
      }
      Serial.println("Returning to origin...");
      resetBackwards(stepSize, numSteps); // Return to origin
      counter = 0; // Reset counter to the origin
    } else if (directionString.equals("b") && numSteps < 8) {
      for (int i = 0; i < numSteps; i++) {
        moveMotorBackwards(stepSize, 1, 0); // Move backward by 1 step
        counter--;
      }
      Serial.println("Returning to origin...");
      resetForwards(stepSize, numSteps); // Return to origin
      counter = 0; // Reset counter to the origin
    } else {
      Serial.println("Invalid input or maximum steps reached.");
    }
    
    // Ask the user if they want to continue
  Serial.println("Press any key to continue...");
  while (!Serial.available()) {} // Wait for any key press to start
  clearInputBuffer(); // Clear any residual input
  }
}

void moveMotorForwards(float stepSize, float numSteps, float stepsMoved) {
  float steps_mm = 2048.0; // 1 revolution, 1 mm

  // Calculate the number of steps needed for the specified distance
  for (int i = 0; i < numSteps; i++) {
    float stepsToMove = stepSize * steps_mm;

    // Rotate the stepper motor
    myStepperForwards.step(stepsToMove);
    stepsMoved = stepsMoved + 1;
    Serial.print("Moved ");
    Serial.print(stepsMoved);
    Serial.println(" steps, triggering camera..");
    triggerCamera();
    delay(1000);
  }
}

void moveMotorBackwards(float stepSize, float numSteps, float stepsMoved) {
  float steps_mm = 2048.0;

  // Calculate the number of steps needed for the specified distance
  for (int i = 0; i < numSteps; i++) {
    float stepsToMove = stepSize * steps_mm;

    // Rotate the stepper motor
    myStepperBackwards.step(stepsToMove);
    stepsMoved = stepsMoved + 1;
    Serial.print("Moved ");
    Serial.print(stepsMoved);
    Serial.println(" steps, triggering camera..");
    triggerCamera();
    delay(1000);
  }
}

void triggerCamera() {
  // Send a 5V electric pulse to trigger the camera
  digitalWrite(cameraTriggerPin, HIGH);
  delay(10);
  digitalWrite(cameraTriggerPin, LOW);
  Serial.println("Camera triggered.");
}

void resetForwards(float stepSize, float numSteps){
  float steps_mm = 2048.0;
  float stepsToMove = numSteps * (stepSize * steps_mm);
  myStepperForwards.step(stepsToMove);
  Serial.println("Finished");
}

void resetBackwards(float stepSize, float numSteps){
  float steps_mm = 2048.0;
  float stepsToMove = numSteps * (stepSize * steps_mm);
  myStepperBackwards.step(stepsToMove);
  Serial.println("Finished");
}
