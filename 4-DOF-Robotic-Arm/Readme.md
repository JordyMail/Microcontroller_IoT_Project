# 4-DOF MeArm Robot

Building and programming a 4-degree-of-freedom robotic arm (MeArm Robot Kit) using Arduino Uno and a joystick.

## Robot Arm

### Hardware
#### List of Hardware:
- **Arduino Uno**
- **4-DOF Robot Arm DIY Acrylic Kit**
- **Servo Motors (9G Micro Servo Motor x 4)**
- **Joystick Module**

### Hardware Overview
The following fasteners are included in the MeArm Robot kit:

- 4 pcs x M3 - 30mm
- 8 pcs x M3 - 12mm
- 6 pcs x M3 - 10mm
- 19 pcs x M3 - 8mm
- 13 pcs x M3 - 6mm
- 13 pcs x M3 hex nuts

### Calibrating Servo Motors
**Servo Motor Pinout**
- Brown: Ground
- Red: +5V Supply
- Orange: Signal (PWM)

The servo motor position changes from **0°** to **180°** depending on the duty cycle of the PWM signal given to the Orange wire.

The duty cycle corresponding to the minimum and maximum position must be found during the calibration process.

### Connecting the Hardware
Connect the Joystick and Servo Motors to the Arduino Uno as follows:

| Arduino Uno Pin | Component |
|---------------|-------------|
| 5V | Servo Motors (Power) & Joystick VCC |
| GND | Servo Motors (GND) & Joystick GND |
| Pin 8 | Base Servo |
| Pin 9 | Elbow Servo |
| Pin 12 | Wrist Servo |
| Pin 11 | Shoulder Servo |
| A1 | Joystick X-axis |
| A2 | Joystick Y-axis |
| A3 | Potentiometer for Wrist |

The power for the servo motors should be provided using an external 5V power supply capable of sourcing ~2A current.

### Calibration Process
The duty cycle corresponding to minimum and maximum servo positions was found using an analog potentiometer with the "servo_test" code.

Servos were set to the required position using the "servo_calib" code.

### Assembly Process
Several assembly tutorials are available online. This kit differs slightly from other commonly available kits, as some linkages are missing. Take care during assembly, as the acrylic parts (particularly the servo motor holders) are fragile.

**If a servo holder breaks, it can be mended using superglue, but be aware that it is prone to breaking again.**

### Dimensions
Accurate measurements of the dimensions are essential for proper calculation of inverse and forward kinematics.

The dimensions of the kit used in this project are given below:

| Parameter | Value (mm) |
|-----------|-----------|
| l0 | 0 |
| h1 | 64 |
| l1 | 15 |
| l2 | 80 |
| l3 | 80 |
| l3I | 35 |
| l3O | 35 |
| l4 | 80 |
| l5 | 65 |
| d5 | 5 |

Before calculating configurations using inverse kinematics, the angles of the servo motors must be verified. This can be done by setting all servos to **90°** and checking with the given diagram.

## Code
Here’s a detailed explanation of your code in a structured way, similar to your example:

---

## **Code Breakdown**

### **1. Including Libraries and Defining Pins**
```cpp
#include <Servo.h>
```
- This library allows the Arduino to control servo motors.

```cpp
#define ServoOne 8     // Base servo
#define ServoTwo 9     // Elbow servo
#define ServoThree 12  // Wrist servo (controlled by potentiometer)
#define ServoFour 11   // Shoulder servo
#define JoyX A1        // Joystick X-axis
#define JoyY A2        // Joystick Y-axis
#define PotentiometerPin A3 // Potentiometer for wrist (ServoThree)
```
- Defines pin numbers for servos and joystick controls.

---

### **2. Declaring Servo Objects and Variables**
```cpp
Servo servo1, servo2, servo3, servo4;
```
- Creates four servo objects to control the MeArm.

```cpp
int lastPos1 = 90, lastPos2 = 90, lastPos3 = 90, lastPos4 = 90;
int joyX, joyY, potValue;
float smoothFactor = 0.1;
int deadZone = 20;
```
- `lastPosX`: Stores the last position of each servo.
- `joyX, joyY`: Stores the joystick readings.
- `potValue`: Stores the potentiometer reading.
- `smoothFactor`: Controls how smoothly servos move.
- `deadZone`: Prevents unnecessary small movements in the joystick.

```cpp
unsigned long previousMillis = 0;
const long loopDelay = 15;
```
- `previousMillis`: Stores the last time the loop executed.
- `loopDelay`: Ensures loop runs every 15ms for smooth control.

---

### **3. Setup Function**
```cpp
void setup() {
  servo1.attach(ServoOne);
  servo2.attach(ServoTwo);
  servo3.attach(ServoThree);
  servo4.attach(ServoFour);
```
- Attaches each servo to the defined pins.

```cpp
  servo1.write(lastPos1);
  servo2.write(lastPos2);
  servo3.write(lastPos3);
  servo4.write(lastPos4);
```
- Initializes servos to the middle position (90°).

```cpp
  Serial.begin(9600);
```
- Starts serial communication for debugging.

---

### **4. Loop Function**
```cpp
void loop() {
  unsigned long currentMillis = millis();
```
- `millis()` returns the time in milliseconds since the Arduino started.
- Helps ensure the loop executes at a consistent speed.

```cpp
  if (currentMillis - previousMillis >= loopDelay) {
    previousMillis = currentMillis;
```
- Checks if 15ms has passed before running the next cycle.

```cpp
    joyX = analogRead(JoyX);
    joyY = analogRead(JoyY);
```
- Reads the joystick's analog values (0-1023).

```cpp
    int targetPos1 = map(joyX, 0, 1023, 0, 180);
    int targetPos2 = map(joyY, 0, 1023, 0, 180);
```
- `map(value, fromLow, fromHigh, toLow, toHigh)`
  - Converts `joyX` and `joyY` (0-1023) into servo positions (0-180°).
  - `1023` represents the maximum analog value (10-bit ADC in Arduino).

```cpp
    potValue = analogRead(PotentiometerPin);
    int targetPos3 = map(potValue, 0, 1023, 0, 180);
```
- Reads the potentiometer value and maps it to servo angles.

---

### **5. Applying Dead Zone and Moving Servos Smoothly**
```cpp
    if (abs(joyX - 512) > deadZone) {
      lastPos1 = (int)lerp(lastPos1, targetPos1, smoothFactor);
      servo1.write(lastPos1);
    }

    if (abs(joyY - 512) > deadZone) {
      lastPos2 = (int)lerp(lastPos2, targetPos2, smoothFactor);
      servo2.write(lastPos2);
    }
```
- `abs(joyX - 512) > deadZone` ensures the joystick has moved significantly before updating the servo.
- `lerp(lastPos1, targetPos1, smoothFactor)`: Smoothly transitions the servo movement instead of jumping to the new position.

```cpp
    lastPos3 = (int)lerp(lastPos3, targetPos3, smoothFactor);
    servo3.write(lastPos3);
```
- The wrist servo moves smoothly based on the potentiometer.

---

### **6. Printing Debug Information**
```cpp
    Serial.print("JoyX: "); Serial.print(joyX);
    Serial.print("  JoyY: "); Serial.print(joyY);
    Serial.print("  Pot: "); Serial.print(potValue);
    Serial.print("  Servo1: "); Serial.print(lastPos1);
    Serial.print("  Servo2: "); Serial.print(lastPos2);
    Serial.print("  Servo3: "); Serial.println(lastPos3);
  }
}
```
- Prints joystick and servo positions to the serial monitor for debugging.

---

### **7. Linear Interpolation Function**
```cpp
float lerp(float start, float end, float t) {
  return start + (end - start) * t;
}
```
- This function smooths movements:
  - `start`: Current position.
  - `end`: Target position.
  - `t`: Smoothing factor (0.1 means 10% of the distance is moved per cycle).
- Helps prevent jerky motion in servos.

---
This project enables control of the 4-DOF MeArm Robot using an **Arduino Uno** and a **joystick**. The wrist servo (Servo 3) is controlled using a potentiometer. Ensure all components are correctly connected and powered before running the code.

