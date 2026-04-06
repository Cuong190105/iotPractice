#define GREEN_LED_PIN 17
#define YELLOW_LED_PIN 18
#define RED_LED_PIN 2
#define LED_NUMBER 3

int pins[] = {GREEN_LED_PIN, YELLOW_LED_PIN, RED_LED_PIN};
int current = -1;

void setup() {
  Serial.begin(115200);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  
  //updateLights();
}

void loop() {

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '0') {
      Serial.println("Tắt");
      for(int i = 0; i < LED_NUMBER; i++) {
        digitalWrite(pins[i], LOW);
      }
      current = -1;
    } else {
      if (current >= 0) {
        digitalWrite(pins[current], LOW);
      }
      current = command - '1';
      digitalWrite(pins[current], HIGH);
    }
  }

}
