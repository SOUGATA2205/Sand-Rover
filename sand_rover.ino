#include <BluetoothSerial.h> // Bluetooth library for ESP32

// Initialize Bluetooth
BluetoothSerial SerialBT;

// Motor control pins
const int IN1 = 25;
const int IN2 = 26;
const int IN3 = 27;
const int IN4 = 14;
const int ENA = 32;
const int ENB = 33;

// Speed settings
const int MAX_SPEED = 255;   // Maximum PWM value
const int TURN_SPEED = 160;  // Reduced speed for turning
const int SPEED_OFFSET = 0; // Offset to balance motor speed

// Command definitions
#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize Bluetooth
  SerialBT.begin("SandRover"); // Bluetooth device name
  Serial.println("Bluetooth Started. Waiting for pairing...");

  // Set motor pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Stop motors initially
  stopMotors();
}

void loop() {
  // Check if data is available from the app
  if (SerialBT.available()) {
    char command = SerialBT.read(); // Read the command

    // Debugging: Print the received command
    Serial.println(command);

    // Execute the received command
    executeCommand(command);
  }
}

// Function to execute commands
void executeCommand(char command) {
  switch (command) {
    case FORWARD:
      moveForward();
      break;
    case BACKWARD:
      moveBackward();
      break;
    case LEFT:
      turnLeft();
      break;
    case RIGHT:
      turnRight();
      break;
    case CIRCLE:
    turnRight();
       // Custom movement for circle
      break;
    case CROSS:
      stopMotors(); // Stop immediately
      break;
    case TRIANGLE:
    performCircle();
      // Example: Toggle an LED or another state
      break;
    case SQUARE:
    turnLeft();
      sendStatus(); // Example: Send status information
      break;
    case START:
      startProcess(); // Custom start operation
      break;
    case PAUSE:
      pauseProcess(); // Custom pause operation
      break;
    default:
      stopMotors(); // Default action
      break;
  }
}

// Motor control functions
void moveForward() {
  // Balance motor speeds using SPEED_OFFSET
  setMotorSpeed(MAX_SPEED, MAX_SPEED - SPEED_OFFSET);
  setMotorDirection(LOW, HIGH, HIGH, LOW);
  
}

void moveBackward() {
  // Balance motor speeds using SPEED_OFFSET
  setMotorSpeed(MAX_SPEED, MAX_SPEED - SPEED_OFFSET);
  setMotorDirection(HIGH, LOW, LOW, HIGH);
  
}

void turnLeft() {
  setMotorSpeed(TURN_SPEED, MAX_SPEED);
  setMotorDirection(LOW, HIGH, LOW, HIGH);
}

void turnRight() {
  setMotorSpeed(MAX_SPEED, TURN_SPEED);
  setMotorDirection(HIGH, LOW, HIGH, LOW);
  
}

void stopMotors() {
  setMotorSpeed(0, 0);
  setMotorDirection(LOW, LOW, LOW, LOW);
}

// Helper functions for motor control
void setMotorSpeed(int speedA, int speedB) {
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

void setMotorDirection(int in1, int in2, int in3, int in4) {
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
}

// Custom functions for additional commands
void performCircle() {
  // Example: Spin motors to move in a circle
  setMotorSpeed(TURN_SPEED, MAX_SPEED);
  setMotorDirection(HIGH, LOW, LOW, HIGH);
}

void sendStatus() {
  SerialBT.println("Status: Motors operational, Bluetooth connected.");
}

void startProcess() {
  Serial.println("Starting process...");
}

void pauseProcess() {
  Serial.println("Process paused.");
}
