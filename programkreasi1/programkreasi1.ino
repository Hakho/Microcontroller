// Deklarasi pin yang digunakan
const int potPin = A0;
const int fan1Pin = 2;
const int fan2Pin = 3;
const int fan3Pin = 4;

void setup() {
  // Set pin kipas DC sebagai OUTPUT
  pinMode(fan1Pin, OUTPUT);
  pinMode(fan2Pin, OUTPUT);
  pinMode(fan3Pin, OUTPUT);
}

void loop() {
  // Baca nilai dari potensiometer (0-1023)
  int potValue = analogRead(potPin);

  // Map nilai potensiometer ke kecepatan kipas (0-255)
  int fanSpeed = map(potValue, 0, 1023, 0, 255);

  // Mengatur kecepatan kipas berdasarkan nilai potensiometer
  analogWrite(fan1Pin, fanSpeed);

  // Mengatur kipas 2 sesuai dengan potensiometer setengah putaran
  if (potValue >= 512) {
    analogWrite(fan2Pin, fanSpeed);
  } else {
    analogWrite(fan2Pin, 0); // Matikan kipas 2 jika potensiometer belum setengah putaran
  }

  // Mengatur kipas 3 sesuai dengan potensiometer penuh putaran
  if (potValue == 1023) {
    analogWrite(fan3Pin, fanSpeed);
  } else {
    analogWrite(fan3Pin, 0); // Matikan kipas 3 jika potensiometer belum penuh putaran
  }
}
