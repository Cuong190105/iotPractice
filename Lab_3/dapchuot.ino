#include <vector>

int led[4] = {16, 17, 18, 19};
int btn[4] = {25, 26, 27, 32};
int buzzer = 21;

bool hitCount[4] = {false, false, false, false};
unsigned long lastDebounce[4] = {0, 0, 0, 0};
int lastState[4] = {HIGH, HIGH, HIGH, HIGH};
int stableState[4] = {HIGH, HIGH, HIGH, HIGH};
int correct = 0, lightTime = 1000, stage = 0, timer = 0, target = 0;
bool ledState = LOW, hit = false;
int lowPitch = 200, highPitch = 2000;

void buttonState(int idx) {
  int state = digitalRead(btn[idx]);
  if (state != lastState[idx]) {
    lastDebounce[idx] = millis();
  }
  if (millis() - lastDebounce[idx] > 50) {
    if (state != stableState[idx]) {
      stableState[idx] = state;
      if (stableState[idx] == LOW) {
        hitCount[idx] = true;
      }
    }
  }
  lastState[idx] = state;
}

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  for (int i = 0; i < 4; i++) {
    pinMode(led[i], OUTPUT);
    pinMode(btn[i], INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);
}

void controlOutput() {
  if (stage == 1) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(led[j], HIGH);
    }
    for (int i = 3; i >= 0; i--) {
      digitalWrite(led[i], LOW);
      tone(buzzer, i == 0 ? 1000 : 500, 500);
      delay(1000);
    }
    stage = 2;
  } else if (stage == 2) {
    digitalWrite(led[target], HIGH);
    stage = 3;
    timer = millis();
  } else if (stage == 4) {
    if (hit) {
      digitalWrite(led[target], LOW);
      tone(buzzer, highPitch, 100);
      delay(100);
    } else {
      for (int i = 0; i < 4; i++) {
        digitalWrite(led[i], HIGH);
      }
      tone(buzzer, lowPitch, 1000);
      delay(1000);
      for (int i = 0; i < 4; i++) {
        digitalWrite(led[i], LOW);
      }
    }
    delay(500);
    stage = 2;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 4; i++) {
    buttonState(i);
  }
  if (stage == 0) {
    for (int i = 0; i < 4; i++) {
      if (hitCount[i]) {
        stage = 1;
        hitCount[i] = false;
      }
    }
  } else if (stage == 2) {
    target = random(0, 4);
  } else if (stage == 3) {
    for (int i = 0; i < 4; i++) {
      if (hitCount[i]) {
        hitCount[i] = false;
        hit = i == target;
        stage = 4;
        if (!hit) {
          correct = 0;
          lightTime = 1000;
          break;
        } else {
          correct += 1;
          if (correct % 5 == 0) {
            lightTime = max(200, lightTime - 100);
          }
        }
      }
    }
    if (millis() - timer > lightTime) {
      stage = 4;
      hit = false;
      correct = 0;
      lightTime = 1000;
    }
  }
  controlOutput();
}
