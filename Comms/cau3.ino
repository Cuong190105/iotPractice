#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Redmi Note 11T Pro";
const char* pass = "1234567888";
const char* broker = "test.mosquitto.org";
const int port = 1883;
const char* topic = "asdfghjklqwertyuiop/test/sua";

WiFiClient wifiClient;
PubSubClient client(wifiClient);


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
    client.publish(topic, "Hello from ESP32");
  } else {
    Serial.println("WiFi not connected");
  }
  delay(10000);
}
