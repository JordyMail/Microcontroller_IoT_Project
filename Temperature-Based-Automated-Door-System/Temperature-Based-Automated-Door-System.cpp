#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define Pins
#define DIR_PIN 8
#define STEP_PIN 9
#define DHTPIN 5
#define LED_YELLOW 4
#define BUZZER_PIN 3
#define LED_GREEN 7
#define LED_RED 10
#define DHTTYPE DHT22

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize LCD Display
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Stepper Motor Variables
const int stepsPerRevolution = 200;
const int stepsFor90Degrees = stepsPerRevolution / 4;
const int pulseWidthInMicros = 20;
const int millisBetweenSteps = 10;

// System States
bool isOpen = false;
bool warningActive = false;
unsigned long warningStartTime = 0;

// Setup Function
void setup() {
    Serial.begin(9600);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    
    lcd.init();
    lcd.backlight();
    dht.begin();
}

// Function to Move Stepper Motor
void stepMotor(int steps, bool dir) {
    digitalWrite(DIR_PIN, dir);
    for (int i = 0; i < steps; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(pulseWidthInMicros);
        digitalWrite(STEP_PIN, LOW);
        delay(millisBetweenSteps);
    }
}

// Function to Activate Warning
void startWarning() {
    warningActive = true;
    warningStartTime = millis();
    digitalWrite(LED_YELLOW, HIGH);
    
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("WARNING!");
    lcd.setCursor(2, 1);
    lcd.print("Temp High");

    // Buzzer Alarm
    for (int i = 0; i < 6; i++) {
        tone(BUZZER_PIN, 1000);
        delay(250);
        noTone(BUZZER_PIN);
        delay(250);
    }
}

// Function to Stop Warning
void stopWarning() {
    warningActive = false;
    digitalWrite(LED_YELLOW, LOW);
    noTone(BUZZER_PIN);
}

// Main Loop
void loop() {
    float temp = dht.readTemperature();
    
    lcd.setCursor(1, 0);
    lcd.print("Temp = ");
    lcd.print(temp);

    // If temperature is too high, start warning
    if (temp > 27 && !isOpen && !warningActive) {
        startWarning();
    }

    // After warning, open or close the door based on temperature
    if (warningActive && millis() - warningStartTime >= 3000) {
        stopWarning();
        stepMotor(stepsFor90Degrees, HIGH);
        isOpen = true;

        lcd.clear();
        lcd.setCursor(1, 1);
        lcd.print("Door Opened");
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
    } else if (temp < 27 && isOpen) {
        stepMotor(stepsFor90Degrees, LOW);
        isOpen = false;

        lcd.clear();
        lcd.setCursor(1, 1);
        lcd.print("Door Closed");
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
    }

    delay(500);
}
