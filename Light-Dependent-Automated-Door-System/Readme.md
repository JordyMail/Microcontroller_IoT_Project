Here is a `README.md` file for your Arduino project:

---

# Light-Dependent Automated Door System

## Description

This Arduino project automates a door system using a **Light Dependent Resistor (LDR)** sensor. The system detects darkness and automatically opens the door while providing warnings through an **LCD display, buzzer, and LED indicators**. When light is detected again, the door closes.

## Features

- **Detects darkness** using an LDR sensor.
- **Triggers a warning** (buzzer sound, yellow LED, and LCD alert) when it gets dark.
- **Automatically opens the door** when the warning period ends.
- **Closes the door** when light is detected again.
- **Displays real-time status** on an LCD screen.
- **Uses stepper motor** for door movement.

## Components Required

- **Arduino Board**
- **Stepper Motor** with Driver
- **LDR Sensor**
- **Buzzer**
- **LEDs (Red, Green, Yellow)**
- **LCD Display (I2C)**
- **Resistors & Jumper Wires**

## Wiring Diagram

| Component       | Arduino Pin |
|----------------|------------|
| Stepper Motor DIR | **8** |
| Stepper Motor STEP | **9** |
| LDR Sensor | **5** |
| LED Yellow | **4** |
| LED Green | **7** |
| LED Red | **10** |
| Buzzer | **3** |
| LCD (I2C) | **SDA, SCL** |

## Code Explanation

### 1. **Setup Function (`setup()`)**
- Initializes the **serial monitor**, **LCD display**, and **pins**.
- Checks **initial light condition** to determine door state.

### 2. **Motor Control (`stepMotor()`)**
- Controls the **stepper motor** to move **90 degrees** in **either direction**.

### 3. **Warning System (`startWarning()` & `stopWarning()`)**
- Activates when darkness is detected.
- Displays **"WARNING! Dark Detected"** on the LCD.
- Turns **on yellow LED** and plays a **buzzer alert**.
- Stops after **3 seconds**.

### 4. **Main Loop (`loop()`)**
- Continuously reads **LDR sensor** to check light conditions.
- If **darkness is detected**, the **warning system** activates.
- After **3 seconds**, the **door opens**.
- If **light is detected**, the **door closes**.

## Usage

1. **Upload the code** to your Arduino.
2. **Connect all components** as per the wiring diagram.
3. The door **closes when it's bright** and **opens when it's dark**.
4. The **buzzer and LED indicators** provide real-time status updates.

## Future Improvements

- **Add Bluetooth/Wi-Fi control** for remote operation.
- **Integrate a PIR sensor** to detect motion.
- **Use a servo motor** instead of a stepper motor for smoother movement.

## Author

Developed by **Jordy Mail**  
For educational and automation purposes.
