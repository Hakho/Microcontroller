// Pin yang digunakan
const int trigPin = 9; // Pin Trigger sensor ultrasonik
const int echoPin = 10; // Pin Echo sensor ultrasonik
const int kipasPin = 5; // Pin untuk mengontrol kipas DC

// Konstanta dan variabel
const int jarakAktif = 20; // Jarak sensor ultrasonik untuk mengaktifkan kipas (dalam cm)

void setup() {
  // Inisialisasi pin-pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(kipasPin, OUTPUT);

  // Kipas dimatikan awalnya
  digitalWrite(kipasPin, LOW);

  Serial.begin(9600); // Inisialisasi komunikasi serial untuk pemantauan
}

void loop() {
  // Mengukur jarak menggunakan sensor ultrasonik
  long duration, jarak;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration * 0.034 / 2;

  // Menampilkan jarak pada Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  // Mengontrol kipas berdasarkan jarak
  if (jarak > 0 && jarak <= jarakAktif) {
    // Jika objek mendekati sensor, kipas menyala
    digitalWrite(kipasPin, HIGH);
    Serial.println("Kipas Menyala");
  } else {
    // Jika objek menjauhi sensor, kipas dimatikan
    digitalWrite(kipasPin, LOW);
    Serial.println("Kipas Mati");
  }

  delay(500); // Delay untuk stabilitas pembacaan jarak
}
