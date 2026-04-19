#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

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
  // Set WiFi to combined mode (AP + Station).
  WiFi.mode(WIFI_AP_STA);
  
  // Connect to the existing WiFi network (must be done before starting the AP)
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

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
