#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Redmi Note 11T Pro";
const char* pass = "1234567888";
const char* host = "https://9p23b9bz-8000.asse.devtunnels.ms/data";
HTTPClient http;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(host);
    Serial.println("Begin host");
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST("{\"temperature\": 25, \"humidity\": 60}");
    Serial.println("Sending");
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
  delay(10000);
}
