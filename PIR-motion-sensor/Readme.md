
# PIR Motion Sensor with LED

## Code Breakdown

### Define the Pins
```cpp
#define PIR 2
#define LED 3
```
- `PIR = 2`: Assigns digital pin `2` to the **PIR motion sensor**.
- `LED = 3`: Assigns digital pin `3` to control an **LED**.

### Variables
```cpp
int pirState = LOW;
int pirVal;
```
- `pirState = LOW`: Stores the current state of motion detection (`LOW` means no motion detected).
- `pirVal`: Stores the **sensor reading** from the PIR sensor.

### Setup Function
```cpp
void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(PIR, INPUT);
}
```
- `Serial.begin(9600)`: Initializes serial communication for debugging.
- `pinMode(LED, OUTPUT)`: Configures the LED pin as an **output**.
- `pinMode(PIR, INPUT)`: Configures the PIR pin as an **input**.

### Loop Function
```cpp
void loop() {
    pirVal = digitalRead(PIR);
```
- `digitalRead(PIR)`: Reads the **motion sensor value** (`HIGH` when motion is detected, `LOW` otherwise).

```cpp
    if (pirVal == HIGH) {
        digitalWrite(LED, HIGH);
        delay(100);
```
- If motion is detected (`pirVal == HIGH`), the **LED turns on**.
- A **100ms delay** is introduced for stability.

```cpp
        if (pirState == LOW) {
            Serial.println("Motion detected");
            digitalWrite(LED, HIGH);
            pirState = HIGH;
        }
    }
```
- If motion was previously **not detected** (`pirState == LOW`), it prints `"Motion detected"` to the serial monitor.
- The LED remains on, and the **pirState is updated to HIGH**.

```cpp
    else {
        digitalWrite(LED, LOW);
        delay(200);
```
- If no motion is detected (`pirVal == LOW`), the **LED turns off**.
- A **200ms delay** is introduced to avoid unnecessary flickering.

```cpp
        if (pirState == HIGH) {
            Serial.println("Motion stopped");
            digitalWrite(LED, LOW);
            pirState = LOW;
        }
    }
}
```
- If motion was previously detected (`pirState == HIGH`), it prints `"Motion stopped"` to the serial monitor.
- The LED remains off, and the **pirState is updated to LOW**.

## How It Works
1. The **PIR sensor** detects movement and sends a **HIGH signal**.
2. The **LED turns on**, and a message `"Motion detected"` is printed.
3. When no movement is detected, the **PIR sensor sends a LOW signal**.
4. The **LED turns off**, and `"Motion stopped"` is printed.
5. The cycle repeats indefinitely in the loop.

## Applications
- **Security systems**
- **Automatic lighting**
- **Intruder detection**
