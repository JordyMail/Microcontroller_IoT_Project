#define BUTTON_PIN 2
#define LED1 3
#define LED2 4
#define LED3 7
#define LED4 6

int buttonState = 0;
int lastButtonState = 0;
int ledState = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    ledState++;
    if (ledState > 4) {
      ledState = 0;
    }

    updateLEDs(ledState);
    delay(300);
  }

  lastButtonState = buttonState;
}

void updateLEDs(int state) {
  switch (state) {
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 1:
      digitalWrite(LED1, HIGH);
      break;
    case 2:
      digitalWrite(LED2, HIGH);
      break;
    case 3:
      digitalWrite(LED3, HIGH);
      break;
    case 4:
      digitalWrite(LED4, HIGH);
      delay(300);
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        delay(200);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        delay(200);
      }
      break;
  }
}