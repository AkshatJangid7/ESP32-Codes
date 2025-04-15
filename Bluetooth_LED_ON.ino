#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int ledPin = 2;  

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_LED"); 
  pinMode(ledPin, OUTPUT);
  Serial.println("Bluetooth started. Connect and send '1' or '0'");
}

void loop() {
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(incomingChar);

    if (incomingChar == '1') {
      digitalWrite(ledPin, HIGH);  // Turn LED on
      Serial.println("LED ON");
    } else if (incomingChar == '0') {
      digitalWrite(ledPin, LOW);   // Turn LED off
      Serial.println("LED OFF");
    }
  }
  delay(20);
}
