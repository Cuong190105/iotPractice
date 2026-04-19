// A0: chan 34
// Relay dieu khien bom: 5
// Thay relay bang LED de test.

// He thong tuoi cay tu dong

#include "DHT.h"
#define DHTTYPE DHT11

const int DHTPIN = 4;
DHT dht(DHTPIN, DHTTYPE); // DHT11 connected to pin 4

const int PUMP = 5;
const int SoilAnalog = 34;

// Nguong canh bao, dieu chinh tuy moi truong thuc te. Gia tri cam bien tu 0-4095

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SoilAnalog, INPUT);
  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, LOW); // Ban dau tat bom nuoc
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read soil moisture sensor values
  int real_value = 0;
  for (int i = 0; i < 10; i++) {
    real_value += analogRead(SoilAnalog);
  }
  real_value /= 10;
  int percent = map(real_value, 0, 4095, 0, 100);
  percent = 100 - percent; // Đảo ngược giá trị để 0% là khô và 100% là ướt
  Serial.print("Soil Moisture: ");
  Serial.println(percent);

  // Read DHT11 sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (temperature > 35) {
    Serial.println("High temperature! Plant shouldn't be watered.");
    digitalWrite(PUMP, LOW);
  } else if (humidity > 80) {
    Serial.println("High air humidity! No need to water the plant.");
    digitalWrite(PUMP, LOW);
  } else if (percent > 70) {
    Serial.println("Soil is wet.");
    digitalWrite(PUMP, LOW);
  } else if (percent < 30) {
    Serial.println("Soil is dry.");
    digitalWrite(PUMP, HIGH);
  }
  delay(2000);
}
