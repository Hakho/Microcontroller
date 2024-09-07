#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define LED_WHITE 9
#define LED_GREEN 10

int objectCount = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Objek masuk: ");
}

void loop() {
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

    // Meningkatkan hitungan objek saat objek terdeteksi
    objectCount++;
    lcd.setCursor(12, 0);
    lcd.print("  ");
    lcd.setCursor(12, 0);
    lcd.print(objectCount);
    delay(1000); // Hindari menghitung ulang objek yang sama dalam waktu singkat
  } else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_WHITE, HIGH);
  }
}
