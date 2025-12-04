#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int val1, val2, val3, val4;

void setup() {
  Serial.begin(9600);
  int speed = 100;

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
  val1 = analogRead(A0); // left in
  val2 = analogRead(A2); // right in
  val3 = analogRead(A4); // left out 
  val4 = analogRead(A1); // right out

  int speed = 80;
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  if (val2 >= 1000 and val1 >= 1000 and val3 >= 100 and val4 >= 100)
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
    else if (val4 >= 1000) // turning right
  {
    int speed1 = 255;
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(speed1);
    motor2.setSpeed(speed1);
    motor3.setSpeed(speed1);
    motor4.setSpeed(speed1);
  }
    else if (val3 >= 1000) // turning left 
  {
    int speed2 = 255;
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(speed2);
    motor2.setSpeed(speed2);
    motor3.setSpeed(speed2);
    motor4.setSpeed(speed2);
  }
  else if (val2 >= 1000) // turning right
  {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
  }
  else if (val1 >= 1000) // turning left 
  {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
  }
  else if (val3 >= 1000 and val1 >= 1000)
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
  else 
  {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
}