#include <Servo.h>

#define ServoOne 8     // Base servo
#define ServoTwo 9     // Elbow servo
#define ServoThree 12  // Wrist servo (now controlled by potentiometer)
#define ServoFour 11   // Shoulder servo
#define JoyX A1        // Joystick X-axis
#define JoyY A2        // Joystick Y-axis
#define PotentiometerPin A3 // Potentiometer for wrist (ServoThree)

Servo servo1, servo2, servo3, servo4;

int lastPos1 = 90, lastPos2 = 90, lastPos3 = 90, lastPos4 = 90;
int joyX, joyY, potValue;
float smoothFactor = 0.1;
int deadZone = 20;

unsigned long previousMillis = 0;
const long loopDelay = 15;

void setup() {
  servo1.attach(ServoOne);
  servo2.attach(ServoTwo);
  servo3.attach(ServoThree);
  servo4.attach(ServoFour);

  servo1.write(lastPos1);
  servo2.write(lastPos2);
  servo3.write(lastPos3);
  servo4.write(lastPos4);

  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= loopDelay) {
    previousMillis = currentMillis;

    // --- Read Joystick ---
    joyX = analogRead(JoyX);
    joyY = analogRead(JoyY);

    int targetPos1 = map(joyX, 0, 1023, 0, 180);
    int targetPos2 = map(joyY, 0, 1023, 0, 180);

    // --- Read Potentiometer for Wrist Servo ---
    potValue = analogRead(PotentiometerPin);
    int targetPos3 = map(potValue, 0, 1023, 0, 180);

    // --- Control Servos with Joystick ---
    if (abs(joyX - 512) > deadZone) {
      lastPos1 = (int)lerp(lastPos1, targetPos1, smoothFactor);
      servo1.write(lastPos1);
    }

    if (abs(joyY - 512) > deadZone) {
      lastPos2 = (int)lerp(lastPos2, targetPos2, smoothFactor);
      servo2.write(lastPos2);
    }

    // --- Control Wrist Servo (Servo 3) with Potentiometer ---
    lastPos3 = (int)lerp(lastPos3, targetPos3, smoothFactor);
    servo3.write(lastPos3);

    // --- Debugging Output ---
    Serial.print("JoyX: "); Serial.print(joyX);
    Serial.print("  JoyY: "); Serial.print(joyY);
    Serial.print("  Pot: "); Serial.print(potValue);
    Serial.print("  Servo1: "); Serial.print(lastPos1);
    Serial.print("  Servo2: "); Serial.print(lastPos2);
    Serial.print("  Servo3: "); Serial.println(lastPos3);
  }
}

// Linear interpolation function
float lerp(float start, float end, float t) {
  return start + (end - start) * t;
}
