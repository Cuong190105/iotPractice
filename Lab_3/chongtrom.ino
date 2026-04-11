#include <vector>

int led[3] = {16, 17, 18};
int btn[4] = {25, 26, 27, 32};
int buzzer = 19;
int masterBtn = 3;

bool isTriggered[3] = {false, false, false};
unsigned long lastDebounce = 0;
int lastState = HIGH, stableState = HIGH, click = 0;
int stage = 0, ledState = LOW, isAnyTriggered = false;
unsigned long wait = 0, lastBlink = 0;

void buttonState() {
  int state = digitalRead(btn[masterBtn]);
  if (state != lastState) {
    lastDebounce = millis();
  }
  if (millis() - lastDebounce > 50) {
    if (state != stableState) {
      stableState = state;
      if (stableState == LOW) {
        wait = millis();
      } else {
        click += 1;
      }
    }
  }
  lastState = state;
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
    pinMode(btn[i], INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);
  pinMode(btn[masterBtn], INPUT_PULLUP);
}

void controlOutput() {
  if (stage == 0 && ledState) {
    ledState = LOW;
    for (int i = 0; i < 3; i++) {
      digitalWrite(led[i], ledState);
    }
    digitalWrite(buzzer, ledState);
  } else if (stage == 1) {
    if (millis() - lastBlink > 500) {
      ledState = !ledState;
      lastBlink = millis();
      for (int i = 0; i < 3; i++) {
        digitalWrite(led[i], ledState);
      }
    }
  } else {
    if (isAnyTriggered && millis() - lastBlink > 500) {
      ledState = !ledState;
      lastBlink = millis();
      for (int i = 0; i < 3; i++) {
        if (isTriggered[i]) {
          digitalWrite(led[i], ledState);
        }
      }
      // active buzzer
      digitalWrite(buzzer, ledState);

      // passive buzzer (wokwi)
      // if (ledState) {
      //   tone(buzzer, 1000);
      // } else {
      //   noTone(buzzer);
      // }
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState();
  if (stage == 0) {
    if (click == 1) {
      stage = 1;
    }

  } else {
    if (stage == 1) {
      if (millis() - wait > 5000) {
        stage = 2;
        for (int i = 0; i < 3; i++) {
          digitalWrite(led[i], LOW);
        }
      }
    } else if (stage == 2) {
      for (int i = 0; i < 3; i++) {
        if (digitalRead(btn[i]) == LOW) {
          isTriggered[i] = true;
          isAnyTriggered = true;
        }
      }
    }
    if (stableState == LOW && millis() - wait > 3000) {
      stage = 0;
      click = -1;
      for (int i = 0; i < 3; i++) {
        isTriggered[i] = false;
        isAnyTriggered = false;
      }
    }
    controlOutput();
  }
}
