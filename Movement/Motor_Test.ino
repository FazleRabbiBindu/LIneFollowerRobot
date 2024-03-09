// Define motor control pins
const int motor1Pin1 = 2;  // Motor 1 pin 1
const int motor1Pin2 = 3;  // Motor 1 pin 2
const int motor1SpeedPin = 9;  // Motor 1 speed control pin (PWM)
const int motor2Pin1 = 4;  // Motor 2 pin 1
const int motor2Pin2 = 5;  // Motor 2 pin 2
const int motor2SpeedPin = 10;  // Motor 2 speed control pin (PWM)

void setup() {
  // Initialize motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1SpeedPin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2SpeedPin, OUTPUT);
}

void loop() {

  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  // Move forward for 2 seconds
  moveForward();
  delay(2000);  // Run motors forward for 2 seconds
  
  // Move backward for 2 seconds
  moveBackward();
  delay(2000);  // Run motors backward for 2 seconds

  //Move Right for 2 seconds
  moveRight();
  delay(2000); //Run motors right for 2 seconds

  //Move Left for 2 seconds
  moveLeft();
  delay(2000); //Run motors left for 2 seconds
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  // Full speed
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
   // Full speed
}

// Function to move the robot backward
void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
   // Full speed
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  // Full speed
}

//Function to move the robot Right
void moveRight(){
  
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
   // Full speed
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  // Full speed
}

//Function to move the robot Left
void moveLeft(){
  
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
   // Full speed
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  // Full speed
}
