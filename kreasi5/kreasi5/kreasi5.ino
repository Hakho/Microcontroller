#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Inisialisasi LCD 1602 I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inisialisasi Keypad 4x4
const byte ROW_NUM    = 4; 
const byte COLUMN_NUM = 4; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM]    = {10, 9, 8, 7}; 
byte pin_column[COLUMN_NUM] = {6, 5, 4, 3}; 

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

// Pin buzzer
int buzzerPin = 13;

// Konstanta password
const String correctPassword = "4554";

void setup() {
  lcd.backlight();
  lcd.begin(16,2); 
  lcd.print("Enter Password:");

  pinMode(buzzerPin, OUTPUT); 
}

void loop() {
  // Baca tombol yang ditekan pada keypad
  char key = keypad.getKey();

  if (key) {
    checkPassword(key);
  }
}

void checkPassword(char key) {
  static String enteredPassword = ""; // Variabel untuk menyimpan password yang dimasukkan

  // Memeriksa apakah tombol yang ditekan adalah tombol khusus (non-digit)
  if (key == '#') {
    // Memeriksa apakah password yang dimasukkan benar
    if (enteredPassword == correctPassword) {
      lcd.clear();
      lcd.print("Access granted");
      delay(2000); // 
      lcd.clear();
      lcd.print("Enter Password:");
      enteredPassword = ""; // Reset password setelah akses diberikan
    } else {
      // Menampilkan pesan kesalahan jika password salah
      lcd.clear();
      lcd.print("WRONG");
      tone(buzzerPin, 1000); 
      delay(1000); 
      lcd.clear();
      lcd.print("Enter Password:");
      noTone(buzzerPin); // Berhenti bunyi buzzer setelah 1 detik
      enteredPassword = ""; // Reset password setelah kesalahan
    }
  } else {
    // Menambahkan karakter ke password yang dimasukkan
    enteredPassword += key;
  }
}
