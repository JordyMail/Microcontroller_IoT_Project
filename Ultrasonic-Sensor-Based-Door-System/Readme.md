Here’s a `README.md` file explaining the code and its functions:

---

# Ultrasonic Sensor-Based Door System with LCD, Stepper Motor, and Buzzer

This Arduino project uses an **ultrasonic sensor** to measure distance, a **stepper motor** to open and close a door, and an **LCD display** to show distance readings. Additionally, an **LED system** and a **buzzer** provide alerts based on the detected distance.

## Features

- Measures distance using an **HC-SR04 ultrasonic sensor**.
- Controls a **stepper motor** to open/close a door.
- Displays distance and status messages on an **I2C LCD**.
- Uses **LED indicators** for different states:
  - Green: Door is **opened**.
  - Yellow: Object is **approaching**.
  - Red: Door is **closed**.
- A **buzzer** sounds when an object is approaching.

## Components Used

- **Arduino Board**
- **HC-SR04 Ultrasonic Sensor**
- **28BYJ-48 Stepper Motor with ULN2003 Driver**
- **I2C LCD Display**
- **LEDs (Red, Yellow, Green)**
- **Buzzer**
- **Wires & Breadboard**

## How It Works

1. The **ultrasonic sensor** continuously measures the distance of objects.
2. The **LCD screen** displays the current distance.
3. Depending on the detected distance:
   - **≤ 15 cm** → The **stepper motor opens** the door (Green LED).
   - **15 - 25 cm** → The **buzzer sounds**, and the **yellow LED** lights up to indicate an approaching object.
   - **> 25 cm** → The **stepper motor closes** the door (Red LED).
4. The **buzzer** beeps when an object is detected between **15 - 25 cm**.

## Code Explanation

### 1. **Pin Definitions**
```cpp
#define TRIG_PIN 8
#define ECHO_PIN 5
#define DIR_PIN 8
#define STEP_PIN 9
#define BUZZER_PIN 3
#define led_yellow 4
#define led_green 7
#define led_red 10
```
- Defines pin assignments for the **ultrasonic sensor, stepper motor, LEDs, and buzzer**.

### 2. **Ultrasonic Sensor Distance Measurement**
```cpp
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
```
- Sends an ultrasonic pulse and calculates **distance in cm**.

### 3. **Stepper Motor Control**
```cpp
void stepMotor(int steps, bool dir) {
    digitalWrite(DIR_PIN, dir);
    for (int i = 0; i < steps; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(20);
        digitalWrite(STEP_PIN, LOW);
        delay(10);
    }
}
```
- Moves the **stepper motor** to open/close the door.

### 4. **Buzzer Alert System**
```cpp
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
```
- The **buzzer beeps every 500ms** when an object is detected within **15 - 25 cm**.

### 5. **Main Loop - Distance Detection and Actions**
```cpp
void loop() {
    long distance = getDistance();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.setCursor(10, 0);
    lcd.print(distance);
    
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
```
- **Controls the stepper motor, LED indicators, and buzzer** based on distance readings.

## Installation & Usage

1. **Connect the components** as per the circuit diagram.
2. **Upload the code** to the Arduino board.
3. **Power on the system** and test the distance detection.
4. Move an object closer to observe **LED changes, buzzer sounds, and door movement**.

## Future Improvements

- **Add Bluetooth or WiFi** for remote control.
- **Improve motor movement** for smoother door transitions.
- **Optimize power consumption** for real-world applications.

## Image

![1](https://github.com/user-attachments/assets/80509a1c-755c-4d96-b4cd-36627908ea2a)
