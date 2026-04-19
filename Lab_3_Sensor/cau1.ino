// VCC: 3.3V
// Data: chan 34
// GND: GND
// Den canh bao: chan 18

#include "DHT.h"
#define DHTTYPE DHT11

const int DHTPIN = 4;
const int LEDPIN = 18;

DHT dht(DHTPIN, DHTTYPE); // quan ly toan bo qua trinh giao tiep voi cam bien

const float HIGH_TEMP = 26.0;
const float LOW_TEMP = 20.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  Serial.println("Starting read DHT...");
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error!");
    delay(2000);
    return;
  }
  float hif = dht.computeHeatIndex(t, h, false);

  Serial.println("Nhiet do: " + String(t) + " *C");
  Serial.println("Do am: " + String(h) + " %");
  Serial.println("Heat Index: " + String(hif) + " *C");

  if (t > HIGH_TEMP || t < LOW_TEMP) {
    digitalWrite(LEDPIN, HIGH);
    Serial.println("Alert!");
  } else {
    digitalWrite(LEDPIN, LOW);
  }
  delay(2000);
}
