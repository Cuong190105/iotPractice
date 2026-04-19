// D0: 5
// A0: chan 34
// Den canh bao xanh, vang, do: chan 16, 17, 18

const int GasDigital = 5;
const int GasAnalog = 34;
const int LEDPIN[3] = {16, 17, 18};
int current_led = 0, previous_led = 0;

// Nguong canh bao, dieu chinh tuy moi truong thuc te. Gia tri cam bien tu 0-4095
const int warning_threshold = 2800;
const int danger_threshold = 3700;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < 3; i++) {
    pinMode(LEDPIN[i], OUTPUT);
  }
  pinMode(GasAnalog, INPUT);
  pinMode(GasDigital, INPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LEDPIN[i], LOW);
  }
}

// Control the LEDs. Only update on change.
void controlLed() {
  if (current_led != previous_led) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(LEDPIN[i], LOW);
    }
    digitalWrite(LEDPIN[current_led], HIGH);
    previous_led = current_led;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read gas sensor values
  int gas_sensor_analog = analogRead(GasAnalog);
  int gas_sensor_digital = digitalRead(GasDigital);
  Serial.print("Gas Sensor Analog: ");
  Serial.println(gas_sensor_analog);
  Serial.print("Gas Sensor Digital: ");
  Serial.println(gas_sensor_digital);

  // Determine LED state based on thresholds
  if (gas_sensor_analog > danger_threshold) {
    current_led = 2;
    Serial.println("Phat hien khi ga!");
  } else if (gas_sensor_analog > warning_threshold) {
    current_led = 1;
    Serial.println("Canh bao!");
  } else {
    current_led = 0;
    Serial.println("Binh thuong.");
  }
  controlLed();
  delay(1000);
}
