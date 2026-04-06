const int buttonPin = 26;
const int ledPin = 16;

int ledState = LOW;
int lastButtonState = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);//khi co lenh nay chan 26 se tu dong high, khi nhan nut thi chan 26 noi dat nen tut xuong low
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) // kiem tra bam nut
  {
    //dao nguoc trang thai led
    if (ledState == LOW) {
      leadState = HIGH;
    } 
    else {
      leadState = LOW;
    }
    digitalWrite(ledPin, ledState);
    delay(100);
    lastButtonState = currentButtonState;
  }
}
