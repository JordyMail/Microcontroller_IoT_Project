#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define DIR_PIN 8
#define STEP_PIN 9
#define LDR 5
#define LED_YELLOW 4
#define BUZZER_PIN 3
#define LED_GREEN 7
#define LED_RED 10

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int stepsPerRevolution = 200;
const int stepsFor90Degrees = stepsPerRevolution / 4;
const int pulseWidthMicros = 20;
const int millisBetweenSteps = 10;

bool isOpen = false;
bool warningActive = false;
unsigned long warningStartTime = 0;

void setup() {
    Serial.begin(9600);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(LDR, INPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    lcd.init();
    lcd.backlight();

    if (digitalRead(LDR) == HIGH) {
        isOpen = false;
    } else {
        isOpen = true;
    }
}

void stepMotor(int steps, bool dir) {
    digitalWrite(DIR_PIN, dir);
    for (int i = 0; i < steps; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(pulseWidthMicros);
        digitalWrite(STEP_PIN, LOW);
        delay(millisBetweenSteps);
    }
}

void startWarning() {
    warningActive = true;
    warningStartTime = millis();
    digitalWrite(LED_YELLOW, HIGH);

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("WARNING !");
    lcd.setCursor(2, 1);
    lcd.print("Dark Detected");

    for (int i = 0; i < 6; i++) {
        tone(BUZZER_PIN, 1000);
        delay(250);
        noTone(BUZZER_PIN);
        delay(250);
    }
}

void stopWarning() {
    warningActive = false;
    digitalWrite(LED_YELLOW, LOW);
    noTone(BUZZER_PIN);
}

void loop() {
    bool isDark = digitalRead(LDR) == HIGH;

    lcd.setCursor(2, 0);
    lcd.print("Room : ");

    if (isDark && !isOpen && !warningActive) {
        startWarning();
    }

    if (warningActive && millis() - warningStartTime >= 3000) {
        stopWarning();
        stepMotor(stepsFor90Degrees, HIGH);
        isOpen = true;
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Room : Dark");
        lcd.setCursor(2, 1);
        lcd.print("Door Opened");
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
    } else if (!isDark && isOpen) {
        stepMotor(stepsFor90Degrees, LOW);
        isOpen = false;
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Room : Light");
        lcd.setCursor(2, 1);
        lcd.print("Door Closed");
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
    }
}
