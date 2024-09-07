#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 5, 4, 3}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int total = 0;
bool isTambahMode = true; // Mode awal adalah penambahan

void setup() {
  lcd.init(); // 
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  lcd.print("Hasil: ");
  lcd.setCursor(7, 0);
  lcd.print(total);
  lcd.setCursor(0, 1);
  lcd.print("Pilih:+/-");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == 'A') {
      isTambahMode = true;
      lcd.setCursor(7, 1);
      lcd.print("tambah  ");
    } else if (key == 'B') {
      isTambahMode = false;
      lcd.setCursor(7, 1);
      lcd.print("kurang");
    }
    
    if (isTambahMode && (key >= '0' && key <= '9')) {
      total += (key - '0');
      lcd.setCursor(7, 0);
      lcd.print(total);
    } else if (!isTambahMode && (key >= '0' && key <= '9')) {
      if (total >= (key - '0')) {
        total -= (key - '0');
        lcd.setCursor(7, 0);
        lcd.print(total);
   }
}
}
}