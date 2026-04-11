int led = 16;
int btn = 25;
int click = 0;
unsigned long lastPressDown = 0;
unsigned long lastClick = 0;
float brightness = 0;
float step = 2.55;
int lastState = HIGH;
int stableState = HIGH;
int mode = 0;
int lastDebounce = 0;
long cur = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  digitalWrite(led, LOW);
}

void buttonState() {
  int state = digitalRead(btn);
  if (state != lastState) {
    lastDebounce = millis();
  }
  if (millis() - lastDebounce > 50) {
    if (state != stableState) {
      stableState = state;
      if (stableState == HIGH) {
        if (click == 0) {
          lastClick = millis();
        }
        click += 1;
      } else {
        lastPressDown = millis();
      }
    }
  }
  lastState = state;
}

void switchMode() {
  if (mode == 0) {
    if (stableState == LOW && millis() - lastPressDown > 1000) {
      mode = 3;
      click = 0;
    } else if (click == 2 || (click > 0 && millis() - lastClick > 500)) {
      pinMode(led, OUTPUT);
      mode = click;
      click = 0;
    }
  } else if (click > 0) {
    if (mode == 2) {
      digitalWrite(led, LOW);
    }
    mode = 0;
    click = 0;
  }
}

void mode1() {
  brightness = (255 - (int)brightness) / 255 * 255;
  digitalWrite(led, brightness / 255);
  mode = 0;
}

void mode2() {
  if (millis() - cur > 500) {
    cur = millis();
    brightness = (255 - (int)brightness) / 255 * 255;
    digitalWrite(led, brightness / 255);
  }
}

void mode3() {
  long now = millis();
  if (now - cur >= 20) {
    cur = now;
    brightness += step;
    if (brightness >= 255) {
      brightness = 255;
      step = -step;
    } else if (brightness <= 0) {
      brightness = 0;
      step = -step;
    }
    Serial.println(brightness);
    analogWrite(led, (int)brightness);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState();
  switchMode();
  if (mode == 1) {
    mode1();
  } else if (mode == 2) {
    mode2();
  } else if (mode == 3) {
    mode3();
  }
}
