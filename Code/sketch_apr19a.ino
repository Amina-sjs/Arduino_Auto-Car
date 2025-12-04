void Obstacle() {
  distance = ultrasonic();
  if (distance <= 12) {
    Stop();
    backward();
    delay(100);
    Stop();
    int L = leftsee();
    servo.write(spoint);
    delay(800);
    int R = rightsee();
    servo.write(spoint);
    if (L < R) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

// Ultrasonic sensor distance reading function
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; 
  return cm;
}

// Servo scanning
int rightsee() {
  servo.write(20);
  delay(800);
  return ultrasonic();
}

int leftsee() {
  servo.write(180);
  delay(800);
  return ultrasonic();
}

// Basic motor control
void forward() {
  M1.run(FORWARD); M2.run(FORWARD); M3.run(FORWARD); M4.run(FORWARD);
}
void backward() {
  M1.run(BACKWARD); M2.run(BACKWARD); M3.run(BACKWARD); M4.run(BACKWARD);
}
void right() {
  M1.run(BACKWARD); M2.run(BACKWARD); M3.run(FORWARD); M4.run(FORWARD);
}
void left() {
  M1.run(FORWARD); M2.run(FORWARD); M3.run(BACKWARD); M4.run(BACKWARD);
}
void Stop() {
  M1.run(RELEASE); M2.run(RELEASE); M3.run(RELEASE); M4.run(RELEASE);
}
