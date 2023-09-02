#include <WiFiNINA.h>

// Please enter your sensitive data in the Secret tab
char ssid[] = "N"; // Change to your Wi-Fi network SSID
char pass[] = "nirmit123"; // Change to your Wi-Fi network password

WiFiClient client;

char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME = "/trigger/detect_light/with/key/gTa7_PX_22fSf49CG3y0OcU-Z0wNgQGzjpas9Rr6Wp4"; // Change to your IFTTT event and key
String queryString = "?value1=";

void setup() {
  // Initialize WiFi connection
  WiFi.begin(ssid, pass);

  Serial.begin(9600);
  while (!Serial);

  // Connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // If connected:
    Serial.println("Connected to server");
  } else {
    // If not connected:
    Serial.println("Connection failed");
  }
}

void loop() {
  int value = analogRead(A0);
  Serial.print("Light Intensity: ");
  Serial.println(value);

  if (value < 500) {
    sendIFTTTRequest("Sunlight hits the terrarium.");
  } else {
    sendIFTTTRequest("Sunlight stops.");
  }
  delay(1500);
}

void sendIFTTTRequest(String message) {
  // Make an HTTP request:
  // Send HTTP header
  client.print("GET " + PATH_NAME + queryString + message);
  client.println(" HTTP/1.1");
  client.println("Host: " + String(HOST_NAME));
  client.println("Connection: close");
  client.println();


  // The server's disconnected, stop the client:
  client.stop();
  Serial.println();
  Serial.println("Disconnected");
}
