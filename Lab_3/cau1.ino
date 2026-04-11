int btn[3] = {25, 26, 27};
int redLed = 16;
int greenLed = 15;
int attempt[4] = {0,0,0,0};
int password[4] = {1,2,1,3};
int order = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++) {
    pinMode(btn[i], INPUT_PULLUP);
  }
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
}

void blink(int pin, int time) {
  for (int i = 0; i < time; i++) {
    digitalWrite(pin, LOW);
    delay(100);
    digitalWrite(pin, HIGH);
    delay(100);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 3; i++) {
    int val = digitalRead(btn[i]);
    if (val == LOW) {
      attempt[order] = i + 1;
      blink(redLed, 1);
      order ++;
      delay(200);
    }
  }
  if (order == 4) {
    bool flag = true;
    for (int i = 0; i < 4; i++) {
      if (attempt[i] != password[i]) {
        flag = false;
        break;
      }
    }

    if (flag) {
      digitalWrite(redLed, LOW);
      blink(greenLed, 3);
      delay(5000);
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
    } else {
      blink(redLed, 5);
    }
    order = 0;
  }
}
