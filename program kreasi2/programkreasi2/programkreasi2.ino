#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C LCD, sesuaikan jika berbeda

void setup() {
  lcd.init();                      // Inisialisasi LCD
  lcd.backlight();                 // Nyalakan backlight

  // Set tampilan selama inisialisasi
  lcd.setCursor(0, 0);
  lcd.print("emosi level: ");
  lcd.setCursor(0, 1);
  lcd.print("act: ");
}

void loop() {
  int potValue = analogRead(A0); // Baca nilai potensiometer

  lcd.setCursor(14, 0);
  lcd.print(" "); // Hapus nilai potensiometer sebelumnya
  lcd.setCursor(14, 0);
  lcd.print(potValue);

  lcd.setCursor(10, 1);
  lcd.print("    "); // Hapus kata sebelumnya

  if (potValue <= 100) {
    lcd.setCursor(6, 1);
    lcd.print("hm");
  } 
  else if (potValue > 100 && potValue <= 512) {
    lcd.setCursor(6, 1);
    lcd.print("apa apaan?");
  } else if (potValue > 512 && potValue <= 768) {
    lcd.setCursor(6, 1);
    lcd.print("wtf dude!");
  } else {
    lcd.setCursor(6, 1);
    lcd.print("*Punch*");
  }

  delay(500); // Tunda tampilan untuk mencegah perubahan cepat pada LCD
}
