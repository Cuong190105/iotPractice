// A0: chan 34
// Den canh bao: chan 18

const int Soil_analog = 34;
const int Soil_digital = 5;
const int LEDPIN = 18;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  pinMode(Soil_analog, INPUT);
  pinMode(Soil_digital, INPUT);
  digitalWrite(LEDPIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int real_value = 0;
  for (int i = 0; i < 10; i++) {
    real_value += analogRead(Soil_analog);
  }
  real_value /= 10;
  int percent = map(real_value, 0, 4095, 0, 100);
  percent = 100 - percent; // Đảo ngược giá trị để 0% là khô và 100% là ướt
  int soil_moisture_digital = digitalRead(Soil_digital);
  Serial.print("Soil Moisture: ");
  Serial.println(percent);

  if (soil_moisture_digital == 0) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }
  delay(2000);
}
