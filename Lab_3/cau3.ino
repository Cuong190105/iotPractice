int led[5] = {16, 17, 18, 19, 21};
int btn[2] = {25, 26};
int lastDebounce[2] = {0, 0};
int lastState[2] = {HIGH, HIGH};
int stableState[2] = {HIGH, HIGH};
int hitCount[2] = {false, false};
int speed, pos, dir, stage;
int lastMove = 0;
int ledState = LOW;

void gameOver() {
    stage = 0;
    pos = 2;
    dir = 1;
    speed = 300;
    lastMove = millis();
}

void buttonState(int button) {
    int state = digitalRead(btn[button]);
    if (state != lastState[button]) {
        lastDebounce[button] = millis();
    }
    if (millis() - lastDebounce[button] > 50) {
        if (state != stableState[button]) {
            stableState[button] = state;
            if (state == LOW) {
                hitCount[button] = true;
            }
        }
    }
    lastState[button] = state;
}

int blink() {
    if (millis() - lastMove > 250) {
        lastMove = millis();
        ledState = !ledState;
        for (int i = 0; i < 5; i++) {
            digitalWrite(led[i], ledState);
        }
        return ledState == LOW ? 1 : 0;
    }
    return 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(btn[i], INPUT_PULLUP);
  }
  gameOver();
}

void updateVisual() {
    if (stage == 3) {
        for (int i = 0; i < 5; i++) {
            digitalWrite(led[i], i == pos ? HIGH : LOW);
        }
    } else {
        stage += blink();
    }
}

void logic() {
    for (int i = 0; i < 2; i++) {
        if (hitCount[i]) {
            hitCount[i] = false;
            if ((i + pos) % 5 == 0) {
                dir = -dir;
                speed = max(50, speed - 20);
                lastMove = millis();
            } else {
                gameOver();
            }
        }
    }
    if (millis() - lastMove > speed) {
        lastMove = millis();
        pos += dir;
        if (pos < 0 || pos > 4) {
            gameOver();
        }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i = 0; i < 2; i++) {
        buttonState(i);
    }
    logic();
    updateVisual();
}
