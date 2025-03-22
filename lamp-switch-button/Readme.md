# LED Button Toggle

This Arduino project demonstrates how to toggle an LED using a button. When the button is pressed, the LED state changes (ON/OFF) and remains in that state until the button is pressed again.

## Components Required
- Arduino board
- LED
- Push button
- Resistors (if needed)
- Jumper wires

## Circuit Diagram
- Connect the LED to pin **3**.
- Connect the button to pin **2** with an internal pull-up resistor enabled.

## Code Explanation
```cpp
#define LED 3  // Define pin 3 for the LED
#define BTN 2  // Define pin 2 for the button

bool ledState = false, lastButtonState = false; // Initialize LED and button state

void setup() {
  pinMode(LED, OUTPUT);      // Set LED pin as output
  pinMode(BTN, INPUT_PULLUP); // Set button pin as input with internal pull-up resistor
}

void loop() {
  if (!digitalRead(BTN) && !lastButtonState) { // Check if button is pressed and wasn't pressed before
    ledState = !ledState;  // Toggle LED state
    digitalWrite(LED, ledState); // Apply the new LED state
  }
  lastButtonState = !digitalRead(BTN); // Store the button state
  delay(50); // Debounce delay to avoid false triggers
}
```

### Code Breakdown
1. **`#define LED 3` & `#define BTN 2`**: Define the LED and button pins.
2. **`bool ledState = false, lastButtonState = false;`**: Variables to track the LED state and previous button state.
3. **`void setup()`**:
   - Set **LED** as an output.
   - Set **BTN** as an input with an internal pull-up resistor (avoids the need for an external resistor).
4. **`void loop()`**:
   - Checks if the button is pressed and wasn't previously pressed.
   - Toggles the LED state and updates its output.
   - Stores the last button state to prevent multiple triggers due to bouncing.
   - Uses a **50ms debounce delay** to avoid unintended rapid toggling.

## How to Use
1. Upload the provided code to your Arduino board.
2. Connect the circuit as per the diagram.
3. Press the button to toggle the LED state.

## Notes
- Ensure the button is wired correctly to avoid floating pin issues.
- Adjust the debounce delay if necessary to match the button's response time.

##Image

WOKWI LINK: [https://wokwi.com/projects/420079545229773825]

![image](https://github.com/user-attachments/assets/e05178c8-9410-47d9-bcb5-8e99dcc9fc5b)




