#define LED 3
#define BTN 2

bool ledState = false, lastButtonState = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(BTN) && !lastButtonState) {
    ledState = !ledState;
    digitalWrite(LED, ledState);
  }
  lastButtonState = !digitalRead(BTN);
  delay(50); // Debounce delay
}