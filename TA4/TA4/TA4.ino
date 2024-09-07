#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define LED_WHITE 9
#define LED_GREEN 10

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  lcd.clear();
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0343) / 2;

  if (distance < 10) {
    digitalWrite(LED_WHITE, LOW);
    digitalWrite(LED_GREEN, HIGH);
    lcd.print("Deket bet");
  } else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_WHITE, HIGH);
    lcd.print("Jauh bet");
  }


delay(500);
}