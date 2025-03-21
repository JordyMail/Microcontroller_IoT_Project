#include<Keypad.h>

char keys[4][4] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'}
};

byte rowPins[] = {4, 5, 6, 7};
byte colPins[] = {8, 9, 10, 11};

Keypad myKey = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
void setup()
{
 Serial.begin(9600);
}

void loop()
{
 char inputKey = myKey.getKey();
 if (inputKey) {
   Serial.println(inputKey);
 }
}
