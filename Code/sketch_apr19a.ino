// ============================================================================
//  TECH FAIRIES ROBOT — LINE FOLLOWING SYSTEM (4 ANALOG IR SENSORS)
//  Motor Driver: Adafruit Motor Shield V1
//  This code is fully documented so ANY reader can understand the logic.
// ============================================================================

#include <AFMotor.h>

// ============================================================================
//  MOTOR DEFINITIONS
//  Motor ports on Adafruit Motor Shield:
//  M1 — Front Left
//  M2 — Front Right
//  M3 — Rear Left
//  M4 — Rear Right
// ============================================================================
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// ============================================================================
//  IR SENSOR INPUTS (4 analog sensors)
//  Placement:
//     OUTSIDE LEFT  (A4) — val3
//     INSIDE LEFT   (A0) — val1
//     INSIDE RIGHT  (A2) — val2
//     OUTSIDE RIGHT (A1) — val4
//  Inside sensors detect main line.
//  Outside sensors detect sharp turns and edges.
// ============================================================================
int val1, val2, val3, val4;

// ============================================================================
//  SETUP
// ============================================================================
void setup() {
  Serial.begin(9600);

  int defaultSpeed = 100;

  // Set initial speeds
  motor1.setSpeed(defaultSpeed);
  motor2.setSpeed(defaultSpeed);
  motor3.setSpeed(defaultSpeed);
  motor4.setSpeed(defaultSpeed);

  // Motors off by default
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}


// ============================================================================
//  MAIN LOOP
// ============================================================================
void loop() {

  // --------------------------------------------------------------------------
  //  READ SENSOR VALUES
  // --------------------------------------------------------------------------
  val1 = analogRead(A0); // Inside Left
  val2 = analogRead(A2); // Inside Right
  val3 = analogRead(A4); // Outside Left
  val4 = analogRead(A1); // Outside Right

  // Adjust base speed
  int baseSpeed = 80;
  motor1.setSpeed(baseSpeed);
  motor2.setSpeed(baseSpeed);
  motor3.setSpeed(baseSpeed);
  motor4.setSpeed(baseSpeed);


  // ========================================================================
  //   DECISION LOGIC OVERVIEW
  //
  //     1) FULL STOP  → if robot sees too much black everywhere
  //     2) HARD RIGHT → strong black on OUTSIDE RIGHT sensor
  //     3) HARD LEFT  → strong black on OUTSIDE LEFT sensor
  //     4) SOFT RIGHT → inside right sees line
  //     5) SOFT LEFT  → inside left sees line
  //     6) SPECIAL STOP → left inside + left outside triggered
  //     7) DEFAULT     → move forward
  //
  //   “>= 1000” means strong black reading.
  // ========================================================================


  // ============================================================================
  //  (1) FULL STOP — Robot has lost the line or reached special area
  //  When both inner sensors AND outer sensors see black → stop everything.
  // ============================================================================
  if (val2 >= 1000 && val1 >= 1000 && val3 >= 100 && val4 >= 100) {

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }


  // ============================================================================
  //  (2) HARD RIGHT TURN — OUTSIDE RIGHT sensor detects black
  //  This means the line is sharply turning right.
  //  Robot should pivot strongly.
  // ============================================================================
  else if (val4 >= 1000) {

    int turnSpeed = 255; // max speed for sharp turn

    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);

    motor1.setSpeed(turnSpeed);
    motor2.setSpeed(turnSpeed);
    motor3.setSpeed(turnSpeed);
    motor4.setSpeed(turnSpeed);
  }


  // ============================================================================
  //  (3) HARD LEFT TURN — OUTSIDE LEFT sensor detects black
  //  Sharp left turn detected.
  // ============================================================================
  else if (val3 >= 1000) {

    int turnSpeed = 255;

    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);

    motor1.setSpeed(turnSpeed);
    motor2.setSpeed(turnSpeed);
    motor3.setSpeed(turnSpeed);
    motor4.setSpeed(turnSpeed);
  }


  // ============================================================================
  //  (4) SOFT RIGHT TURN — RIGHT inside sensor sees line
  //  Minor correction to the right.
  // ============================================================================
  else if (val2 >= 1000) {

    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
  }


  // ============================================================================
  //  (5) SOFT LEFT TURN — LEFT inside sensor sees line
  //  Minor correction to the left.
  // ============================================================================
  else if (val1 >= 1000) {

    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
  }


  // ============================================================================
  //  (6) SPECIAL STOP CASE
  //  If both LEFT sensors trigger strongly → stop
  //  Often used as checkpoint or final marker.
  // ============================================================================
  else if (val3 >= 1000 && val1 >= 1000) {

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }


  // ============================================================================
  //  (7) DEFAULT — MOVE FORWARD
  //  If no turning conditions are active, continue following the line.
  // ============================================================================
  else {

    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
}
