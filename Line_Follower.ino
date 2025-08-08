// --- Motor Driver Pins (TB6612FNG) ---
const int IN1 = 3;
const int IN2 = 4;
const int PWMA = 9;

const int IN3 = 5;
const int IN4 = 6;
const int PWMB = 10;

const int STBY = 8;

// --- IR Sensor Pins ---
const int IR_LEFT = 7;
const int IR_RIGHT = 12;


const int speed = 50;
// --- Speeds (0 to 255) ---
const int FORWARD_SPEED = 70;
const int LEFT_TURN_SPEED = 120;
const int RIGHT_TURN_SPEED = 120;

// --- Delays (ms) ---
const int FORWARD_DELAY = 60;
const int LEFT_TURN_DELAY = 10;
const int RIGHT_TURN_DELAY = 10;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(STBY, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  digitalWrite(STBY, HIGH);
}

void loop() {
  int leftIR = digitalRead(IR_LEFT);
  int rightIR = digitalRead(IR_RIGHT);

  if (leftIR == 0 && rightIR == 0) {
    moveForward(FORWARD_SPEED, FORWARD_DELAY);
  } 
  else if (leftIR == 0 && rightIR == 1) {
    turnLeft(LEFT_TURN_SPEED, LEFT_TURN_DELAY);
  } 
  else if (leftIR == 1 && rightIR == 0) {
    turnRight(RIGHT_TURN_SPEED, RIGHT_TURN_DELAY);
  } 
  else {
    stopMotors();
  }
}

// --- Movement Functions with Speed + Delay ---

void moveForward(int speed, int duration) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(PWMA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWMB, speed);

  delay(duration);
}

void turnLeft(int speed, int duration) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(PWMA, 0);  // Stop left motor

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWMB, speed);  // Right motor forward

  delay(duration);
}

void turnRight(int speed, int duration) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(PWMA, speed);  // Left motor forward

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(PWMB, 0);  // Stop right motor

  delay(duration);
}

void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}