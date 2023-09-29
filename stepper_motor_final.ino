#include <Stepper.h>

const int stepsPerRevolution = 2048; 
const int cameraTriggerPin = 12; // 13?

Stepper myStepperBackwards(stepsPerRevolution, 2, 3, 4, 5);  // Forwards Direction
Stepper myStepperForwards(stepsPerRevolution, 5, 2, 3, 4); // Backwards Direction

void setup() {
  myStepperForwards.setSpeed(5);
  myStepperBacckwards.setSpeed(5);
  Serial.begin(9600); 
  pinMode(cameraTriggerPin, OUTPUT);
}

void loop() {
  float stepSize = 0.0;
  float numSteps = 0.0; 
  float directions = 0.0;
  int counter = 0; // keep track of origin

   Serial.println("If you are finished photographing the sample, please type 'done'");

  // Ask the user for the step size
   Serial.println("Enter step size (in mm): ");
   while(!Serial.available()) {}  // Wait for user input
   stepSize = Serial.parseFloat(); // Read user input
   while(Serial.available()) Serial.read(); // Clear input buffer

  // Ask the user for the number of steps
  Serial.println("Enter number of steps (maximum 7): ");
  while(!Serial.available()) {}  
  numSteps = Serial.parseFloat(); 
  while(Serial.available()) Serial.read(); 

  // Ask the user for direction
  Serial.println("Forwards (F) or backwards (B)?: ");
  while(!Serial.available()) {}  
  String directionString = Serial.readString(); // Read user input as a string
  directionString.trim(); // Remove leading/trailing whitespace
  directionString.toLowerCase(); // Convert the user input to lowercase

  if(Serial.available()) {
    userInput = Serial.readString();
    userInput.trim(); 
    if(userInput.equalsIgnoreCase("done")) {
      Serial.println("Moving back to the 0 position...");
      if(counter > 0){ moveMotorBackwards(stepSize, counter); }
      Serial.println("Exiting the program.");
      return; // Exit the loop and the program
    }
  }
  
  // Move the stepper motor based on user input
  if(directionString.equals("f") && numSteps < 7){ 
    counter = counter + numSteps;
    if(counter < 7){ moveMotorForwards(stepSize, numSteps); }
  
  } else if(directionString.equals("b") && numSteps < 7){
    counter = counter - numSteps;
    if(counter >= 0 && < 7){ moveMotorBackwards(stepSize, numSteps); }
  
  } else if(counter > 7){ Serial.println("The maximum number of steps forwards has been reached. You must now go the other direction.");
  
  } else if(counter < 0){ Serial.println("The maximum number of steps backwards has been reached. You must now go the other direction");
  }
}


void moveMotorForwards(float stepSize, float numSteps) {
  float steps_mm = 2048.0; // 1 revolution, 1 cm
  
  // Calculate the number of steps needed for the specified distance
  Serial.println("Moving ", numSteps, " steps forwards");
  for(int i = 0; i < numSteps; i++){
    float stepsToMove = stepSize * steps_mm;

  // Rotate the stepper motor
    myStepperForwards.step(stepsToMove);
    Serial.println("Moved ", i, " steps, triggering camera..");
    triggerCamera();
    delay(1000);
  }
  Serial.println("Finished moving");
}

void moveMotorBackwards(float stepSize, float numSteps) {
  float steps_mm = 2048.0; 

  // Calculate the number of steps needed for the specified distance
  Serial.println("Moving ", numSteps, " steps backwards");
  for(int i = 0; i < numSteps; i++){
    float stepsToMove = stepSize * steps_mm;
    Serial.println(stepsToMove);

  // Rotate the stepper motor
    myStepperBackwards.step(stepsToMove);
    Serial.println("Moved ", i, " steps, triggering camera..");
    triggerCamera();
    delay(1000);
  }
  Serial.println("Finished moving");
}

void triggerCamera() {
  // Send a 5V electric pulse to trigger the camera
  digitalWrite(cameraTriggerPin, HIGH);
  delay(10);  
  digitalWrite(cameraTriggerPin, LOW);

}
