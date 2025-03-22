# Motion Sensor with Buzzer and Traffic Light System

## Description
This code implements a motion detection system using an Arduino, a PIR sensor, a buzzer, and two LEDs (red and green). The system works as follows:
- The red and green lights alternate every 3 seconds.
- When the red light is on, the PIR sensor is active and detects motion.
- If motion is detected while the red light is on, the buzzer sounds, and a message is displayed on the Serial Monitor.
- When the green light is on, the motion sensor and buzzer are disabled.

## Components Required
- Arduino Board
- PIR Motion Sensor
- Buzzer
- Red LED
- Green LED
- Resistors (if necessary)
- Jumper Wires

## Library Used
- `Arduino.h` (default library for Arduino projects)

## Pin Configuration
| Component | Arduino Pin |
|-----------|------------|
| Buzzer    | 3          |
| PIR Sensor | 2         |
| Red LED   | 11         |
| Green LED | 12         |

## Code Explanation
1. **Define Pins and Variables**
   ```cpp
   #define buzzer 3
   #define sensor 2
   #define red 11
   #define green 12
   ```
   Defines the pins for the buzzer, PIR sensor, and LEDs.

2. **Setup Function**
   ```cpp
   void setup()
   {
     Serial.begin(9600);
     pinMode(buzzer, OUTPUT);
     pinMode(red, OUTPUT);
     pinMode(green, OUTPUT);
     pinMode(sensor, INPUT);
   }
   ```
   - Initializes serial communication.
   - Configures the pins as input or output.

3. **Loop Function**
   ```cpp
   void loop()
   {
     unsigned long currentMillis = millis();
   ```
   - Uses `millis()` to track time without delaying execution.

4. **Alternating the Red and Green Lights**
   ```cpp
   if (currentMillis - previousMillis >= times)
   {
     previousMillis = currentMillis;
     isRedLightOn = !isRedLightOn;
   ```
   - Every 3 seconds, toggles between red and green lights.

5. **Motion Detection and Buzzer Activation**
   ```cpp
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
   ```
   - If the red light is on and motion is detected, the buzzer sounds and prints "MOTION DETECTED" to the Serial Monitor.

6. **Deactivating Sensor When Green Light is On**
   ```cpp
   else
   {
     noTone(buzzer);
   }
   ```
   - When the green light is on, the buzzer is turned off and the motion sensor is ignored.

## Usage Instructions
1. Connect the components according to the pin configuration.
2. Upload the code to your Arduino board.
3. Open the Serial Monitor to view motion detection messages.
4. Observe how the red and green lights alternate every 3 seconds.
5. When the red light is on, move in front of the PIR sensor to trigger the buzzer.

## Expected Output
- Every 3 seconds, the LED color changes.
- When the red light is on, if motion is detected, the Serial Monitor displays:
  ```
  MOTION DETECTED
  ```
- When motion stops, the Serial Monitor displays:
  ```
  MOTION STOPPED
  ```

## Notes
- Ensure the PIR sensor is properly connected and has time to stabilize upon power-up.
- Modify the `times` variable if a different switching interval is needed.

![image](https://github.com/user-attachments/assets/8248da99-422a-44ff-be18-608fe5e818c2)
