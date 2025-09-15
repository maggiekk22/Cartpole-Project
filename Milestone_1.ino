#include <AccelStepper.h>



// Pin definitions
#define DIR_PIN 2
#define STEP_PIN 3
#define ENCODER_A 4
#define ENCODER_B 5

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

volatile long encoderPos = 0;

void setup() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderISR, CHANGE);
  
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void loop() {
  // Read encoder position
  long currentPos = encoderPos;

  // Simple control logic (move to center)
  long target = 0; // Center position
  long error = target - currentPos;

  stepper.moveTo(error);
  stepper.run();
}

void encoderISR() {
  // Basic quadrature decoder
  int a = digitalRead(ENCODER_A);
  int b = digitalRead(ENCODER_B);
  if (a == b) encoderPos++;
  else encoderPos--;
}
