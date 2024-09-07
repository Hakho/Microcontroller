#include <Servo.h>
#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>

#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11
#define MotorInterfaceType 8
#define button 5

LiquidCrystal_I2C lcd(0x27, 16, 2);
AccelStepper stepper(MotorInterfaceType, motorPin4, motorPin2, motorPin3, motorPin1);
Servo motor;

int numStep = 4096;
bool kondisi = false;

void setup() {
  motor.attach(6);
  pinMode(button, INPUT_PULLUP);
  stepper.setMaxSpeed(700);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void bukaAtap() {
  lcd.setCursor(0, 0);
  lcd.print("Cuaca Cerah");
  lcd.setCursor(0, 1);
  lcd.print("Atap Terbuka");

  motor.write(0);

  // Bergerak ke kiri 3 kali
  for (int i = 0; i < 3; i++) {
    stepper.setSpeed(-700);
    stepper.runSpeed();
    while (stepper.currentPosition() != -numStep) {
      stepper.runSpeed();
    }
    stepper.setCurrentPosition(0);
  }
}

void tutupAtap() {
  lcd.setCursor(0, 0);
  lcd.print("Cuaca Hujan");
  lcd.setCursor(0, 1);
  lcd.print("Atap Tertutup");

  motor.write(180);

  // Bergerak ke kanan 3 kali
  for (int i = 0; i < 3; i++) {
    stepper.setSpeed(700);
    stepper.runSpeed();
    while (stepper.currentPosition() != numStep) {
      stepper.runSpeed();
    }
    stepper.setCurrentPosition(0);
  }
}

void loop() {
  int btn = digitalRead(button);
  if (btn == LOW) {
    kondisi = !kondisi;
    delay(500); // Tambahkan delay untuk menghindari bouncing tombol
  }

  if (kondisi == 0) {
    bukaAtap();
  } else {
    tutupAtap();
  }

  delay(1000);
}
