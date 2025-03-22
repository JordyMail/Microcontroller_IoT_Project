#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <Tone.h> 

const int stepsPerRevolution = 200; 
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

const int trigPin = 12;
const int echoPin = 13;

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int buzzerPin = 7; 
Tone buzzer; 

const int relayPin = 6; 
bool relayClosed = false;

bool motorRotated = false;
bool portalTerbuka = false;

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

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) / 29.1; 

  if (distance < 200 && !motorRotated) {
    myStepper.step(90);
    motorRotated = true; 
    portalTerbuka = true;

    buzzer.play(NOTE_C5, 1000);

    digitalWrite(relayPin, HIGH);
    relayClosed = true;
  }

  if (distance >= 200 && motorRotated) {
    myStepper.step(-90);
    motorRotated = false; 
    portalTerbuka = false; 

    digitalWrite(relayPin, LOW);
    relayClosed = false;
  }

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

  delay(1000); 
}
