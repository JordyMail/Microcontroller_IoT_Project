 # Potentiometer-Controlled LED Brightness

## Code Breakdown

### Define the Pins
```cpp
int potPin = A0;
int ledPin = 6;
```
- `potPin = A0`: Assigns the analog pin `A0` to read input from a **potentiometer**.
- `ledPin = 6`: Assigns the digital pin `6` (PWM capable) to control an **LED**.

### Setup Function
```cpp
void setup() {
    pinMode(ledPin, OUTPUT);
}
```
- `pinMode(ledPin, OUTPUT)`: Configures the **LED pin** as an output, allowing it to receive signals.

### Loop Function
```cpp
void loop() {
    int potValue = analogRead(potPin);
```
- `analogRead(potPin)`: Reads the **potentiometer value**, which ranges from **0 to 1023**.

```cpp
    int brightness = potValue / 4;
```
- The potentiometer value (0–1023) is divided by `4` to scale it down to a range of **0 to 255** (since `analogWrite()` uses an 8-bit PWM signal).

```cpp
    analogWrite(ledPin, brightness);
```
- `analogWrite(ledPin, brightness)`: Sends a **PWM signal** to the LED, controlling its brightness.

```cpp
    delay(10);
}
```
- `delay(10)`: Introduces a **short delay (10ms)** to ensure smooth brightness transitions.

## How It Works
1. The **potentiometer** acts as a variable resistor, changing its voltage output.
2. The **Arduino reads the voltage** using `analogRead()`, which gives a value from 0 to 1023.
3. The value is **scaled to 0–255** (PWM range) and sent to the **LED**.
4. As you **turn the potentiometer**, the LED brightness **increases or decreases**.

## Applications
- **LED dimming control**
- **Motor speed control** (using PWM)
- **Analog sensor-based input systems**

## Image
WOKWI LINK: [https://wokwi.com/projects/420079624926797825]


![1lamp](https://github.com/user-attachments/assets/a4654e76-8f63-4d41-953a-e8273eddf136)
