#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define DIR_PIN 8
#define STEP_PIN 9
#define TRIG_PIN 8
#define ECHO_PIN 5
#define BUZZER_PIN 3
#define led_yellow 4
#define led_green 7
#define led_red 10

const int stepsPerRevolution = 200;
const int stepsFor90Degrees = stepsPerRevolution / 4;
const int pulseWidthMicros = 20;
const int millisBetweenSteps = 10;

bool isOpen = false;
unsigned long lastBuzzerTime = 0;
bool buzzerState = false;
bool warningActive = false;
unsigned long warningStartTime = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
    Serial.begin(9600);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(led_yellow, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_red, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    lcd.init();
    lcd.backlight();
}

long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    long distance = duration * 0.034 / 2;

    return distance;
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

void buzzerSong() {
    unsigned long currentMillis = millis();

    if (currentMillis - lastBuzzerTime >= 500) {
        lastBuzzerTime = currentMillis;

        if (buzzerState) {
            noTone(BUZZER_PIN);
        } else {
            tone(BUZZER_PIN, 1000);
        }

        buzzerState = !buzzerState;
    }
}

void loop() {
    long distance = getDistance();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.setCursor(10, 0);
    lcd.print(distance);

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);

    if (distance <= 15 && !isOpen) {
        stepMotor(stepsFor90Degrees, HIGH);
        isOpen = true;
    } else if (distance > 15 && distance <= 25 && isOpen) {
        stepMotor(stepsFor90Degrees, LOW);
        isOpen = false;
    }

    if (distance > 15 && distance <= 25) {
        digitalWrite(led_yellow, HIGH);
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, LOW);
        buzzerSong();
        lcd.print("Object Approaching!");
    } else if (distance <= 15) {
        digitalWrite(led_green, HIGH);
        digitalWrite(led_yellow, LOW);
        digitalWrite(led_red, LOW);
        noTone(BUZZER_PIN);
        lcd.print("Door Opened");
    } else {
        digitalWrite(led_green, LOW);
        digitalWrite(led_yellow, LOW);
        digitalWrite(led_red, HIGH);
        noTone(BUZZER_PIN);
        lcd.print("Door Closed");
    }
}
