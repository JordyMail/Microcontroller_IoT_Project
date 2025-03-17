// Define the pins
int potPin = A0; 
int ledPin = 6;  

void setup() {
  // Set up the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the value from the potentiometer (0 to 1023)
  int potValue = analogRead(potPin);
  
  // Convert the potentiometer value to a range for the LED (0 to 255)
  int brightness = potValue / 4; // 1023 divided by 4 equals 255

  analogWrite(ledPin, brightness);
  delay(10);
}
