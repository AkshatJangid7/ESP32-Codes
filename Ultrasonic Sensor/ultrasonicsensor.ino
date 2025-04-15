#define TRIG_PIN 4
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  float distance = (duration > 0) ? (duration * 0.0343 / 2.0) : -1;

  if (distance != -1) {
    Serial.print("Distance: ");
    Serial.print(distance, 2);
    Serial.println(" cm");
  } else {
    Serial.println("Out of range");
  }

  delay(500);
}
