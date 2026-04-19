// D0: 5
// A0: chan 34
// Den canh bao: chan 18

const int GasDigital = 5;
const int GasAnalog = 34;
const int LEDPIN = 18;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  pinMode(GasAnalog, INPUT);
  pinMode(GasDigital, INPUT);
  digitalWrite(LEDPIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int gas_sensor_analog = analogRead(GasAnalog);
  int gas_sensor_digital = digitalRead(GasDigital);
  Serial.print("Gas Sensor Analog: ");
  Serial.println(gas_sensor_analog);
  Serial.print("Gas Sensor Digital: ");
  Serial.println(gas_sensor_digital);

  if (gas_sensor_analog > 2000) {
    digitalWrite(LEDPIN, HIGH);
    Serial.println("Phat hien khi ga!");
  } else {
    digitalWrite(LEDPIN, LOW);
    Serial.println("Binh thuong.");
  }
  delay(2000);
}
