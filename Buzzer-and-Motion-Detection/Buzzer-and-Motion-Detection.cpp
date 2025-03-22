#include <Arduino.h>

#define buzzer 3
#define sensor 2
#define red 11
#define green 12

int pirstate = LOW; // Previous state of sensor
int pirval;         // Stores the current sensor reading
unsigned long previousMillis = 0;
const long times = 3000; // 3 seconds 
bool isRedLightOn = true;   // Start with red light on

void setup()
{
  Serial.begin(9600);

  // Output
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  // Input
  pinMode(sensor, INPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  // Check if 3 seconds have passed to switch the lights
  if (currentMillis - previousMillis >= times)
  {
    previousMillis = currentMillis;
    isRedLightOn = !isRedLightOn; // Toggle the light state

    if (isRedLightOn)
    {
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
    }
    else
    {
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
    }
  }

  // If red light is on, check for motion and sound the buzzer
  if (isRedLightOn)
  {
    pirval = digitalRead(sensor);

    if (pirval == HIGH)
    {
      tone(buzzer, 200);
      if (pirstate == LOW)
      {
        Serial.println("MOTION DETECTED");
        pirstate = HIGH;
      }
    }
    else
    {
      noTone(buzzer);
      if (pirstate == HIGH)
      {
        Serial.println("MOTION STOPPED");
        pirstate = LOW;
      }
    }
  }
  else
  {
    // If green light is on, the buzzer and sensor will off
    noTone(buzzer);
  }
}