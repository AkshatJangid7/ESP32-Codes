#include <ESP32Servo.h>

Servo myServo;
String input = "";
int angle = 0;

void setup() {
  Serial.begin(115200);
  myServo.attach(13);
  myServo.write(0);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      angle = input.toInt();
      if (angle >= 0 && angle <= 360) {
        myServo.write(angle);
      }
      input = "";
    } else {
      input += c;
    }
  }
}
