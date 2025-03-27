Here is a `README.md` file for this Arduino project:

---

# Temperature-Based Automated Door System

## Description

This Arduino project automates a door system based on **temperature readings** from a **DHT22 sensor**. If the temperature exceeds a set threshold (**27°C**), the system issues a warning and then **opens the door** after a delay. When the temperature falls below the threshold, the door **closes automatically**.

## Features

- **Monitors temperature** using a **DHT22 sensor**.
- **Triggers a warning** (buzzer, yellow LED, and LCD message) when the temperature is too high.
- **Opens the door** when the warning period ends.
- **Closes the door** when the temperature returns to normal.
- **Displays real-time temperature** on an **LCD screen**.
- **Uses a stepper motor** for door movement.

## Components Required

- **Arduino Board**
- **Stepper Motor** with Driver
- **DHT22 Temperature Sensor**
- **Buzzer**
- **LEDs (Red, Green, Yellow)**
- **LCD Display (I2C)**
- **Resistors & Jumper Wires**

## Wiring Diagram

| Component       | Arduino Pin |
|----------------|------------|
| Stepper Motor DIR | **8** |
| Stepper Motor STEP | **9** |
| DHT22 Sensor Data | **5** |
| LED Yellow | **4** |
| LED Green | **7** |
| LED Red | **10** |
| Buzzer | **3** |
| LCD (I2C) | **SDA, SCL** |

## Code Explanation

### 1. **Setup Function (`setup()`)**
- Initializes the **serial monitor**, **LCD display**, and **pins**.
- Initializes the **DHT22 temperature sensor**.

### 2. **Motor Control (`stepMotor()`)**
- Controls the **stepper motor** to move **90 degrees** in **either direction**.

### 3. **Warning System (`startWarning()` & `stopWarning()`)**
- Activates if **temperature exceeds 27°C**.
- Displays **"WARNING! Temp High"** on the LCD.
- Turns **on the yellow LED** and plays a **buzzer alert**.
- Stops after **3 seconds**.

### 4. **Main Loop (`loop()`)**
- Continuously reads **temperature** from the **DHT22 sensor**.
- If the temperature **exceeds 27°C**, the **warning system activates**.
- After **3 seconds**, the **door opens**.
- If the temperature **drops below 27°C**, the **door closes**.

## Usage

1. **Upload the code** to your Arduino.
2. **Connect all components** as per the wiring diagram.
3. The door **closes when the temperature is normal** and **opens when the temperature is too high**.
4. The **buzzer and LED indicators** provide real-time status updates.

## Future Improvements

- **Add Wi-Fi/MQTT integration** for remote monitoring.
- **Use a fan cooling system** to reduce temperature instead of opening a door.
- **Adjust threshold dynamically** based on user input.
