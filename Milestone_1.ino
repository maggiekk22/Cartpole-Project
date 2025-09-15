#define STEP_PIN 3
#define DIR_PIN 2

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  Serial.begin(9600);  // For serial command input
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'r') { // Command 'r' to move right
      moveCart(1000, true);  // Move 1000 steps to the right
    } else if (cmd == 'l') { // Command 'l' to move left
      moveCart(1000, false); // Move 1000 steps to the left
    }
  }
}

void moveCart(int steps, bool right) {
  digitalWrite(DIR_PIN, right ? HIGH : LOW);
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(800);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(800);
  }
}
