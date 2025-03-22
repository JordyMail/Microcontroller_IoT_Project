# Automated Door System with Ultrasonic Sensor, Stepper Motor, and LCD

## Description
This Arduino-based system automates a door using an ultrasonic sensor, a stepper motor, a relay, an LCD display, and a buzzer. The door opens when an object is detected within 200 cm and closes when the object moves away. The LCD displays the current door status and distance measured.

## Components Required
- Arduino Board
- Stepper Motor (e.g., 28BYJ-48) with Driver
- Ultrasonic Sensor (HC-SR04)
- I2C LCD Display (16x2)
- Buzzer
- Relay Module
- Jumper Wires

## Library Dependencies
- `Stepper.h` (for controlling the stepper motor)
- `LiquidCrystal_I2C.h` (for handling the LCD display)
- `Tone.h` (for playing sound on the buzzer)

## Pin Configuration
| Component        | Arduino Pin |
|-----------------|------------|
| Stepper Motor   | 8, 9, 10, 11 |
| Ultrasonic Trigger | 12        |
| Ultrasonic Echo   | 13        |
| Buzzer         | 7          |
| Relay         | 6          |
| LCD I2C Address | 0x27 (Default) |

## Code Explanation

### 1. **Initializing Components**
```cpp
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Tone buzzer;
```
- Initializes the stepper motor, LCD display, and buzzer.

### 2. **Setup Function**
```cpp
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight();
  buzzer.begin(buzzerPin);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  myStepper.setSpeed(60);
}
```
- Configures the pin modes and initializes the LCD and buzzer.

### 3. **Measuring Distance with Ultrasonic Sensor**
```cpp
long duration, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration / 2) / 29.1;
```
- Sends an ultrasonic pulse and calculates the distance.

### 4. **Opening and Closing the Door**
```cpp
if (distance < 200 && !motorRotated) {
  myStepper.step(90);
  motorRotated = true;
  portalTerbuka = true;
  buzzer.play(NOTE_C5, 1000);
  digitalWrite(relayPin, HIGH);
}
if (distance >= 200 && motorRotated) {
  myStepper.step(-90);
  motorRotated = false;
  portalTerbuka = false;
  digitalWrite(relayPin, LOW);
}
```
- The door opens when an object is within 200 cm and closes when it moves away.

### 5. **Displaying Status on LCD**
```cpp
lcd.setCursor(0, 0);
lcd.print("Pintu : ");
if (portalTerbuka) {
  lcd.print("Terbuka   ");
} else {
  lcd.print("Tertutup  ");
}
lcd.setCursor(0, 1);
lcd.print("Jarak: ");
lcd.print(distance);
lcd.print(" cm");
```
- The LCD shows whether the door is open or closed along with the distance measurement.

## How to Use
1. Connect all components according to the pin configuration.
2. Upload the code to the Arduino board.
3. Observe the LCD display for distance and door status.
4. Move an object closer (<200 cm) to trigger the door opening.
5. Move the object away (>=200 cm) to close the door.

## Expected Output
- LCD shows:
  ```
  Pintu : Terbuka
  Jarak: 150 cm
  ```
- If an object moves away:
  ```
  Pintu : Tertutup
  Jarak: 220 cm
  ```
- Buzzer sounds when the door opens.

## Notes
- Ensure the LCD I2C address matches your module (use `I2C Scanner` sketch if needed).
- Adjust the stepper motor steps and speed if necessary for proper door movement.
- Modify the distance threshold in the code if needed.

WOKWI LINK: [https://wokwi.com/projects/421951766750375937]


![image](https://github.com/user-attachments/assets/d5bd8702-9981-4f0d-b6ac-88fc1f587312)
