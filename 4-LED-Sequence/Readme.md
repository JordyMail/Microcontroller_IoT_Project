# Button-Controlled LED Sequence

## Description
This Arduino program controls a sequence of LEDs using a button. Each button press advances the LED pattern through different states until it resets back to off.

## Components Required
- Arduino Board
- 4 LEDs
- 1 Push Button
- Resistors (220Ω for LEDs, 10kΩ for the button if not using `INPUT_PULLUP`)
- Jumper Wires

## Pin Configuration
| Component | Arduino Pin |
|-----------|------------|
| Button    | 2          |
| LED1      | 3          |
| LED2      | 4          |
| LED3      | 7          |
| LED4      | 6          |

## Code Explanation

### 1. **Defining Pins and Variables**
```cpp
#define BUTTON_PIN 2
#define LED1 3
#define LED2 4
#define LED3 7
#define LED4 6

int buttonState = 0;
int lastButtonState = 0;
int ledState = 0;
```
- Defines the button and LED pins.
- Initializes variables for tracking button state and LED sequence.

### 2. **Setup Function**
```cpp
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}
```
- Configures the button as an `INPUT_PULLUP` to avoid using an external pull-down resistor.
- Sets the LED pins as outputs.

### 3. **Loop Function**
```cpp
void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    ledState++;
    if (ledState > 4) {
      ledState = 0;
    }

    updateLEDs(ledState);
    delay(300);
  }
  lastButtonState = buttonState;
}
```
- Reads the button state.
- When the button is pressed, it increments `ledState`.
- Resets `ledState` after reaching 4.
- Calls `updateLEDs()` to update the LED pattern.

### 4. **LED Control Function**
```cpp
void updateLEDs(int state) {
  switch (state) {
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 1:
      digitalWrite(LED1, HIGH);
      break;
    case 2:
      digitalWrite(LED2, HIGH);
      break;
    case 3:
      digitalWrite(LED3, HIGH);
      break;
    case 4:
      digitalWrite(LED4, HIGH);
      delay(300);
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        delay(200);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        delay(200);
      }
      break;
  }
}
```
- Updates LED patterns based on `ledState`:
  - **State 0:** All LEDs OFF.
  - **State 1-3:** LEDs turn ON sequentially.
  - **State 4:** LED4 turns on, then all LEDs blink 5 times before resetting.

## How to Use
1. Connect the components according to the pin configuration.
2. Upload the code to the Arduino board.
3. Press the button to cycle through LED states.
4. When reaching state 4, all LEDs blink before resetting.

## Expected Output
- **Press 1:** LED1 ON.
- **Press 2:** LED2 ON.
- **Press 3:** LED3 ON.
- **Press 4:** LED4 ON, then all LEDs blink.
- **Press 5:** All LEDs OFF (reset).

## Notes
- The `delay(300);` prevents button bouncing issues.
- Modify `updateLEDs()` to add more patterns if needed.

## Image 

WOKWI LINK: [https://wokwi.com/projects/422017152204355585]


![image](https://github.com/user-attachments/assets/f3e1fab5-650f-43fc-b482-7bb98bd84169)
