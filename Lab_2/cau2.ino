int numPin = 3;
int pinOut[] = {13, 27, 32};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numPin; i++) {
    pinMode(pinOut[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < numPin; i++) {
    for (int j = 0; j < numPin; j++) {
      digitalWrite(pinOut[j], i == j ? HIGH : LOW);
    }
    delay(1000);
  }
}