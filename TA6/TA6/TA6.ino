#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat LCD I2C
const int pin_ss = 10;
const int pin_rst = 9;
MFRC522 rfid(pin_ss, pin_rst);
int buzzerPin = 3;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  lcd.init();                      // Inisialisasi LCD
  lcd.backlight();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String id = "";
    for (byte i = 0; i < 4; i++) {
      id += String(rfid.uid.uidByte[i], HEX);
    }

    Serial.println("ID Anda: ");
    Serial.println(id);

    lcd.clear();  // Menghapus tampilan LCD
    lcd.setCursor(0, 1);
    lcd.print("ID :");
    lcd.setCursor(4, 1);
    lcd.print(id);

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    // Check if the ID matches a specific value
    if (id.equals("5a33b089")) {
      Serial.println("Selamat datang!");
      lcd.setCursor(0, 0);
      lcd.print("Selamat datang!");
    } else {
      Serial.println("Kartu tidak dikenal.");
      lcd.setCursor(0, 0);
      lcd.print("tidak dikenal.");
      tone(buzzerPin, 1000); 
      delay(1000); 
      noTone(buzzerPin);
    }

    delay(2000);  // Delay untuk menahan tampilan di LCD selama 2 detik
}
}