#include <WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const int ledPin = 2; 

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("\nNew Client Connected");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    if (request.indexOf("favicon.ico") != -1) {
      client.stop();
      Serial.println("Favicon request ignored");
      return;
    }

    if (request.indexOf("/ON") != -1) {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED is ON ");
    } else if (request.indexOf("/OFF") != -1) {
      digitalWrite(ledPin, LOW);
      Serial.println("LED is OFF ");
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'></head>");
    client.println("<body><h2>ESP32 LED Control</h2>");
    client.println("<a href='/ON'><button style='font-size:30px'>LED ON</button></a><br><br>");
    client.println("<a href='/OFF'><button style='font-size:30px'>LED OFF</button></a>");
    client.println("</body></html>");
    client.println();

    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}
