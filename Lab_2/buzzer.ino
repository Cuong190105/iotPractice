const int ledPin = 16;
const int buzzerPin = 33;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
}

void signal(int duration) {
  //bat den, tat buzz
  digitalWrite(ledPin, HIGH);
  digitalWrite(buzzrPin, LOW);
  delay(duration);
  //ngc lai
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzrPin, HIGH);
  delay(duration);
}
void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 3; i++) {
    signal(200);
  }
  delay(300);

}
