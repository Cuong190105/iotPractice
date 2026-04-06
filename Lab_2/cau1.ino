#define GREEN_LED_PIN 17
#define YELLOW_LED_PIN 18
#define RED_LED_PIN 2
#define LED_NUMBER 3

unsigned long previousMillis = 0;
int currentStage = 0; // 0: Xanh, 1: Vàng, 2: Đỏ
unsigned long durations[] = {3000, 3000, 3000}; 
int pins[] = {GREEN_LED_PIN, YELLOW_LED_PIN, RED_LED_PIN};

void setup() {
  Serial.begin(115200);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  //updateLights();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= durations[currentStage]) {
    previousMillis = currentMillis;
    updateLights();
  }
}

void updateLights() {
  digitalWrite(pins[i], LOW);
  currentStage = (currentStage + 1) % LED_NUMBER;
  digitalWrite(pins[i], HIGH);
}
