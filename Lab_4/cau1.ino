#include <WiFi.h>

char* ap_ssid = "MyWifi";
char* password = "12345678";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello, ESP32!");
  delay(2000);
}
