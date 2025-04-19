#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Soumya";
const char* password = "soumya0205";

const int ledPin = 2;

WebServer server(80);

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<title>ESP32 LED Control</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body {font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; padding-top: 50px;}";
  html += "h1 {color: #333;}";
  html += ".button {padding: 15px 40px; font-size: 18px; margin: 20px; border: none; border-radius: 10px;";
  html += "cursor: pointer; box-shadow: 0 4px 6px rgba(0,0,0,0.1); transition: background-color 0.3s ease, transform 0.2s ease;}";
  html += ".button:hover {transform: scale(1.05);}";
  html += ".on {background-color: #28a745; color: white;}";
  html += ".off {background-color: #dc3545; color: white;}";
  html += ".form-container {display: inline-block;}";
  html += "</style></head><body>";
  html += "<h1>ESP32 LED Control Panel</h1>";
  html += "<div class='form-container'>";
  html += "<form action='/LEDOn' method='POST'>";
  html += "<button class='button on' type='submit'>Turn ON</button>";
  html += "</form></div>";
  html += "<div class='form-container'>";
  html += "<form action='/LEDOff' method='POST'>";
  html += "<button class='button off' type='submit'>Turn OFF</button>";
  html += "</form></div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}


void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/LEDOn", HTTP_POST, handleLEDOn);
  server.on("/LEDOff", HTTP_POST, handleLEDOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
