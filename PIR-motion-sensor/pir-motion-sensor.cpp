#define PIR 2
#define LED 3

int pirState = LOW;
int pirVal;

void setup() {
 Serial.begin(9600);
 pinMode(LED, OUTPUT);
 pinMode(PIR, INPUT);
}
void loop() {
 pirVal = digitalRead(PIR);
 if (pirVal == HIGH) {
   digitalWrite(LED, HIGH);
   delay(100);
  
   if (pirState == LOW) {
     Serial.println("Motion detected");
     digitalWrite(LED, HIGH);
     pirState = HIGH;
   }
 } else {
   digitalWrite(LED, LOW);
   delay(200);
  
   if (pirState == HIGH) {
     Serial.println("Motion stopped");
     digitalWrite(LED, LOW);
     pirState = LOW;
   }
 }
}
