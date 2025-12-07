#include <Servo.h>        // Includes the library for controlling servo motors.
#include <AFMotor.h>      // Includes the library for controlling DC motors via the Adafruit Motor Shield.

// --- Pin Definitions ---
#define Echo A0           // Defines the Echo pin of the ultrasonic sensor on analog pin A0.
#define Trig A1           // Defines the Trig pin of the ultrasonic sensor on analog pin A1.
#define motor 10          // Defines the pin used for the servo motor control (usually a PWM pin).
#define IR_LEFT A2        // Defines the pin for the Left IR line sensor on A2.
#define IR_RIGHT A3       // Defines the pin for the Right IR line sensor on A3.

// --- Constants Definitions ---
#define Speed 100         // Sets the base speed for all DC motors (range 0 to 255).
#define spoint 103        // The angle the servo returns to after scanning (center position).

// --- Global Variables ---
char value;               // Variable to store the character received via Bluetooth/Serial.
int distance;             // Variable to store the measured distance in centimeters.
int Left;                 // Variable to store the distance measured when scanning left.
int Right;                // Variable to store the distance measured when scanning right.
int L = 0;                // Variable to hold the final distance value from the left scan for obstacle avoidance.
int R = 0;                // Variable to hold the final distance value from the right scan for obstacle avoidance.
int L1 = 0;               // Unused variable.
int R1 = 0;               // Unused variable.

// --- Object Initialization ---
Servo servo;              // Creates the 'servo' object to control the servo motor.
// Creates objects for the four DC motors connected to the Adafruit Motor Shield ports.
AF_DCMotor M1(1);         // Motor 1 (typically Front Left).
AF_DCMotor M2(2);         // Motor 2 (typically Front Right).
AF_DCMotor M3(3);         // Motor 3 (typically Rear Left).
AF_DCMotor M4(4);         // Motor 4 (typically Rear Right).

void setup() {
  Serial.begin(9600);     // Initializes serial communication at 9600 baud (for debugging and Bluetooth).

  // --- Pin Mode Configuration ---
  pinMode(IR_LEFT, INPUT);  // Sets the left IR sensor pin as an input.
  pinMode(IR_RIGHT, INPUT); // Sets the right IR sensor pin as an input.
  pinMode(Trig, OUTPUT);    // Sets the ultrasonic sensor Trig pin as an output.
  pinMode(Echo, INPUT);     // Sets the ultrasonic sensor Echo pin as an input.

  // --- Device Setup ---
  servo.attach(motor);    // Attaches the 'servo' object to the 'motor' pin (D10).

  // Sets the base speed for all four motors.
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);
}

void loop() {
  // LineFollowing();  // Uncomment to enable Line Following mode.
  // Obstacle();       // Uncomment to enable Obstacle Avoidance mode.
  // Bluetoothcontrol(); // Uncomment to enable Bluetooth control mode.

  // In the current state, the robot does nothing, as all operational modes are commented out.
  // You must uncomment ONE of the functions to make the robot operate.
}
 // --- LINE FOLLOWING ---
void LineFollowing() {
  int leftIR = analogRead(IR_LEFT);   // Reads the analog value from the left IR sensor.
  int rightIR = analogRead(IR_RIGHT); // Reads the analog value from the right IR sensor.

  // Determines if the sensor is over the line (assuming values < 700 mean "on line").
  bool leftOnLine = (leftIR < 700);
  bool rightOnLine = (rightIR < 700);

  if (leftOnLine && rightOnLine) {
    forward(); // Both sensors are on the line. Move straight ahead.
  }
  else if (leftOnLine && !rightOnLine) {
    left();    // Left sensor is on the line, right is not. Turn left to correct the path.
  }
  else if (!leftOnLine && rightOnLine) {
    right();   // Right sensor is on the line, left is not. Turn right to correct the path.
  }
  else {
    Stop();    // Both sensors are off the line (line lost). Stop the robot.
  }
}

 // --- BLUETHOOTH CONTROL---
void Bluetoothcontrol() {
  if (Serial.available() > 0) { // Checks if there is data available in the serial buffer (from Bluetooth).
    value = Serial.read();      // Reads the incoming character and stores it in 'value'.
    Serial.println(value);      // Sends the received character back (for debugging).
  }

  // Executes the corresponding movement based on the received character.
  if (value == 'F') {       // 'F' - Forward
    forward();
  } else if (value == 'B') { // 'B' - Backward
    backward();
  } else if (value == 'L') { // 'L' - Turn Left
    left();
  } else if (value == 'R') { // 'R' - Turn Right
  right();
  } else if (value == 'S') { // 'S' - Stop
    Stop();
  }
}
// --- OBSTACLE AVOIDING CAR---
void Obstacle() {
  distance = ultrasonic(); // Measures the distance to any object in front.

  if (distance <= 12) {    // If an obstacle is detected within 12 cm.
    Stop();                // Stop immediately.
    backward();            // Move backward slightly.
    delay(100);
    Stop();                // Stop again.

    // --- Scanning for clearance ---
    L = leftsee();         // Turn sensor left and measure distance (stored in 'L').
    servo.write(spoint);   // Return the servo to the center position (103 degrees).
    delay(800);            // Wait for the servo to move.
    R = rightsee();        // Turn sensor right and measure distance (stored in 'R').
    servo.write(spoint);   // Return the servo to the center position.

    // --- Decision making ---
    if (L < R) {           // If the right path has more clearance (R > L).
      right();             // Turn right to avoid the obstacle.
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {    // If the left path has more clearance (L > R).
      left();              // Turn left to avoid the obstacle.
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();             // No obstacle detected. Move forward.
  }
}

// Ultrasonic sensor distance reading function
int ultrasonic() {
  // 1. Ensures the Trig pin is low for a clean start.
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);

  // 2. Sends a 10µs high pulse to the Trig pin to start the sonar burst.
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  // 3. Measures the duration (in µs) of the echo pulse (time taken for the sound to return).
  long t = pulseIn(Echo, HIGH);

  // 4. Converts the time duration into distance (cm).
  // Formula: Distance (cm) = (Time in µs) / 29 / 2
  // We divide by 2 because the time measured is for the travel "there and back".
  long cm = t / 29 / 2;
  return cm;
}

void forward() {          // Moves forward: all motors run FORWARD.
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void backward() {         // Moves backward: all motors run BACKWARD.
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void right() {            // Turns right on the spot (Tank Turn): right side backward, left side forward.
  M1.run(BACKWARD);       // Left Front
  M2.run(BACKWARD);       // Left Rear
  M3.run(FORWARD);        // Right Front
  M4.run(FORWARD);        // Right Rear
  // NOTE: This setup means the left side pushes backward and the right side pulls forward.
}
void left() {             // Turns left on the spot (Tank Turn): left side backward, right side forward.
  M1.run(FORWARD);        // Left Front
  M2.run(FORWARD);        // Left Rear
  M3.run(BACKWARD);       // Right Front
  M4.run(BACKWARD);       // Right Rear
  // NOTE: This setup means the left side pulls forward and the right side pushes backward.
}
void Stop() {             // Stops all motors by setting them to RELEASE (coast to stop).
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

int rightsee() {          // Function to scan distance to the right.
  servo.write(20);        // Swings the servo to 20 degrees (Right).
  delay(800);             // Wait for the servo to reach the position.
  Left = ultrasonic();    // Measures the distance. (Note: Stored in 'Left' variable, which might be confusing).
  return Left;            // Returns the measured distance.
}
int leftsee() {           // Function to scan distance to the left.
  servo.write(180);       // Swings the servo to 180 degrees (Left).
  delay(800);             // Wait for the servo to reach the position.
  Right = ultrasonic();   // Measures the distance. (Note: Stored in 'Right' variable, which might be confusing).
  return Right;           // Returns the measured distance.
}