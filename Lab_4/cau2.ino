#include <WiFi.h>

const char* ap_ssid = "MyWifi";
const char* ap_password = "12345678";
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
unsigned long previousMillis = 0;
const long interval = 10000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Set WiFi to Access Point mode.
  WiFi.mode(WIFI_AP);

  // Configure and start the Access Point
  WiFi.softAP(ap_ssid, ap_password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Print AP info every 10 seconds
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    Serial.println("----------Wifi AP Info----------");
    Serial.print("SSID: ");
    Serial.println(WiFi.softAPSSID());
    Serial.print("Number of connected stations: ");
    Serial.println(WiFi.softAPgetStationNum());
    Serial.println("-------------------------------");
  }
}
