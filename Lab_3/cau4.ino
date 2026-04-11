#include <vector>

int led[3] = {16, 17, 18};
int btn[3] = {25, 26, 27};
int lastDebounce[3] = {0, 0, 0};
int lastState[3] = {HIGH, HIGH, HIGH};
int stableState[3] = {HIGH, HIGH, HIGH};
int hitCount[3] = {false, false, false};
int pos, level, stage;
int lastBlink = 0, ledState = LOW, wait = 0;

std::vector<uint8_t> sequence = {};

void gameOver() {
    sequence.clear();
    pos = 0;
    stage = 0;
    level = 0;
}

void buttonState(int button) {
    int state = digitalRead(btn[button]);
    if (state != lastState[button]) {
        lastDebounce[button] = millis();
    }
    if (millis() - lastDebounce[button] > 50) {
        if (state != stableState[button]) {
            stableState[button] = state;
            if (stage == 1) {
                if (state == LOW) {
                    digitalWrite(led[button], HIGH);
                } else {
                    hitCount[button] = true;
                    digitalWrite(led[button], LOW);
                }
            }
        }
    }
    lastState[button] = state;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  randomSeed(analogRead(35));
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(btn[i], INPUT_PULLUP);
  }
  gameOver();
}

void updateVisual() {
    if (stage == 0) {
        // randomly blink
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 3; j++) {
                digitalWrite(led[j], random(0, 2));
            }
            delay(100);
            for (int j = 0; j < 3; j++) {
                digitalWrite(led[j], LOW);
            }
        }
    } else if (stage == 2) {
        // show sequence
        delay(1000);
        for (int i = 0; i < level; i++) {
            digitalWrite(led[sequence[i]], HIGH);
            delay(250);
            digitalWrite(led[sequence[i]], LOW);
            delay(250);
        }
        stage = 1;
    }
}

void generateNext() {
    stage = 2;
    level ++;
    sequence.push_back(random(0, 3));
    wait = millis();
    pos = 0;
}

void logic() {
    if (pos == sequence.size()) {
        generateNext();
    } else {
        for (int i = 0; i < 3; i++) {
            if (hitCount[i]) {
                hitCount[i] = false;
                if (i == sequence[pos]) {
                    pos++;
                } else {
                    gameOver();
                }
            }
        }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i = 0; i < 3; i++) {
        buttonState(i);
    }
    logic();
    updateVisual();
}
