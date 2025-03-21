# Seven Segment Display with Arduino

## Overview
This Arduino project controls a 7-segment display by setting digital pins as outputs and defining number representations using an array. The `printNum` function takes an array of binary values and sends signals to the corresponding pins to display numbers sequentially.

## Components Required
- Arduino board (e.g., Arduino Uno)
- 7-segment display (common cathode or anode)
- Resistors (if necessary, depending on display type)
- Jumper wires

## Circuit Connections
The seven-segment display is connected to Arduino digital pins 2 to 9. Each segment of the display is controlled by one of these pins.

## Code Explanation
1. **Number Representation:**
   - Each number (1-9) is represented as an array of 8 binary values.
   - Each value corresponds to a specific segment in the display.

2. **Functions:**
   - `printNum(int num[])`: Loops through 8 pins and writes HIGH or LOW based on the provided array.
   - `setup()`: Sets digital pins 2-9 as OUTPUT.
   - `loop()`: Displays numbers sequentially with a 1-second delay.

## Mathematical Representation
Each number is stored as an array of 8 bits (0 or 1), representing the segments of the 7-segment display. These bits can be interpreted as a binary number.

For example:
- **Number 1:** `{0, 1, 1, 0, 0, 0, 0, 0}` → Binary: `01100000` → Decimal: `96`
- **Number 2:** `{1, 1, 0, 1, 1, 0, 1, 0}` → Binary: `11011010` → Decimal: `218`
- **Number 3:** `{1, 1, 1, 1, 0, 0, 1, 0}` → Binary: `11110010` → Decimal: `242`
- **Number 4:** `{0, 1, 1, 0, 0, 1, 1, 0}` → Binary: `01100110` → Decimal: `102`
- **Number 5:** `{1, 0, 1, 1, 0, 1, 1, 0}` → Binary: `10110110` → Decimal: `182`
- **Number 6:** `{1, 0, 1, 1, 1, 1, 1, 0}` → Binary: `10111110` → Decimal: `190`
- **Number 7:** `{1, 1, 1, 0, 0, 0, 0, 0}` → Binary: `11100000` → Decimal: `224`
- **Number 8:** `{1, 1, 1, 1, 1, 1, 1, 0}` → Binary: `11111110` → Decimal: `254`
- **Number 9:** `{1, 1, 1, 1, 0, 1, 1, 0}` → Binary: `11110110` → Decimal: `246`

This conversion helps in debugging and understanding the binary representation of each digit in the 7-segment display.

## Installation & Usage
1. Connect the seven-segment display to the Arduino as per the circuit diagram.
2. Upload the provided code to the Arduino board using the Arduino IDE.
3. The display will cycle through numbers 1 to 9 every second.

## Future Improvements
- Add support for displaying `0`.
- Implement user input to display custom numbers.
- Integrate with a shift register to minimize pin usage.

## License
This project is open-source. Feel free to modify and improve it!

