char value;

void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
  if (value == 'F') forward();
  else if (value == 'B') backward();
  else if (value == 'L') left();
  else if (value == 'R') right();
  else if (value == 'S') Stop();
}
