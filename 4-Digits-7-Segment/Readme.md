# Temperature Monitoring System with 7-Segment Display

## Overview
This project is an Arduino-based temperature monitoring system that reads temperature data from an analog sensor and displays it on a 4-digit 7-segment display. If the temperature exceeds 30°C, an LED indicator turns on, and a buzzer alerts the user.

## Features
- Reads temperature using an analog sensor.
- Displays temperature on a 4-digit 7-segment display.
- Activates a buzzer and LED alert if the temperature exceeds 30°C.
- Uses Arduino for processing and control.

## Components Required
- Arduino board (Uno, Mega, etc.)
- 4-digit 7-segment display
- Temperature sensor (e.g., LM35)
- Resistors
- LED (Red)
- Buzzer
- Jumper wires
- Breadboard

## Circuit Connections
- **7-Segment Display Pins:**
  - A = Pin 2
  - B = Pin 3
  - C = Pin 4
  - D = Pin 5
  - E = Pin 6
  - F = Pin 7
  - G = Pin 8
- **Common Pins for Display Digits:**
  - D1 = Pin 9
  - D2 = Pin 10
  - D3 = Pin 11
  - D4 = Pin 12
- **Other Components:**
  - Temperature sensor output = A0
  - LED (Red) = A1
  - Buzzer = A2

## Installation & Usage
1. Connect the components as per the circuit diagram.
2. Upload the provided Arduino code to your Arduino board using the Arduino IDE.
3. Open the Serial Monitor (9600 baud rate) to see the temperature readings.
4. Observe the 7-segment display showing the temperature.
5. If the temperature exceeds 30°C, the LED turns on and the buzzer sounds an alert.

## Code Explanation
- Reads the temperature sensor value using `analogRead(ADCPIN)`.
- Converts the analog reading into temperature in Celsius.
- Splits the temperature value into individual digits for the 7-segment display.
- Continuously updates the display using a loop.
- Activates an LED and buzzer when the temperature exceeds the threshold.

## License
This project is open-source and can be modified and distributed freely.

## Author
[Your Name]

