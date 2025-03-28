#include <Arduino.h>
#include "SevSeg.h"

#define ADCPIN A0
#define RED A1
#define BUZZER A2

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;

// Common pins
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;
int Dot = 13;

double Temperature = 0;
int temp = 0;
int placeValuesOfTemp[4];

int tempRefresh = 1000; // refresh temperature every 1 second
int sevSegRefresh = 5;

unsigned long time_now = 0;

void setup() {
    analogReference(INTERNAL);
    
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(pinE, OUTPUT);
    pinMode(pinF, OUTPUT);
    pinMode(pinG, OUTPUT);
    
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(Dot, OUTPUT);
    
    pinMode(RED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    
    Serial.begin(9600);
}

void loop() {
    if (millis() > time_now + tempRefresh) {
        time_now = millis();

        Temperature = analogRead(ADCPIN);
        Temperature = Temperature * 1100 / (1024 * 10);
        Serial.print("Temperature: ");
        Serial.println(Temperature);
        
        temp = Temperature * 100;

        placeValuesOfTemp[3] = (temp) % 10;      // Units
        placeValuesOfTemp[2] = (temp / 10) % 10; // Tens
        placeValuesOfTemp[1] = (temp / 100) % 10; // Hundreds
        placeValuesOfTemp[0] = (temp / 1000) % 10; // Thousands
    }

    int number[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 0, 0, 1, 1, 0, 0}, // 1
        {1, 0, 1, 1, 0, 1, 1}, // 2
        {1, 0, 0, 1, 1, 1, 1}, // 3
        {0, 1, 0, 1, 1, 0, 1}, // 4
        {1, 1, 0, 0, 1, 1, 1}, // 5
        {1, 1, 1, 0, 1, 1, 1}, // 6
        {1, 0, 0, 1, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 0, 1, 1, 1, 1}  // 9
    };

    int commonPin[5][4] = {
        {0, 1, 1, 1}, // Enable digit 1
        {1, 0, 1, 1}, // Enable digit 2
        {1, 1, 0, 1}, // Enable digit 3
        {1, 1, 1, 0}, // Enable digit 4
        {0, 0, 0, 0}  // Enable all
    };

    for (int n = 0; n < 4; n++) {
        for (int x = 0; x < 4; x++) {
            digitalWrite(x + 9, commonPin[n][x]);
        }

        if (n == 1)
            digitalWrite(Dot, 1);
        else
            digitalWrite(Dot, 0);

        for (int j = 0; j < 7; j++) {
            digitalWrite(j + 2, number[placeValuesOfTemp[n]][j]);
        }

        if (Temperature > 30) {
            digitalWrite(RED, HIGH);
            tone(BUZZER, 1000);
        } else {
            digitalWrite(RED, LOW);
            noTone(BUZZER);
        }

        delay(sevSegRefresh);
    }
}
