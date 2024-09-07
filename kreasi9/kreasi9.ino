#define BLYNK_TEMPLATE_ID "TMPL6Z0BTSzp1"
#define BLYNK_TEMPLATE_NAME "Kendali LED dan Buzzer"
#define BLYNK_AUTH_TOKEN "8wsa0JCKfz__HikYki5scnbdD3rjmnnG"
#define BLYNK_PRINT Serial // inisialisasi Komunikasi serial blynk
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "8wsa0JCKfz__HikYki5scnbdD3rjmnnG"; // masukan auth token yng didapatkan
char ssid[] = "Mockingbird"; //masukan nama hotspot/Wifi yang digunakan
char pass[] = "bakakaitou"; //password WiFi
#define LED 2
#define BUZZER 14
#define DHTPIN 15  // Pin tempat Anda menghubungkan output sensor DHT11
#define DHTTYPE DHT11  // Jenis sensor DHT yang Anda gunakan (DHT11, DHT22, AM2302, dll.)
DHT dht(DHTPIN, DHTTYPE);

//pengiriman data untuk Virtual pin di blynk iot
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  digitalWrite(LED, pinValue);
}

BLYNK_WRITE(V1)
{
  int pinValue1 = param.asInt();
  digitalWrite(BUZZER, pinValue1);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  Blynk.begin(auth, ssid, pass); //memulai Blynk
  dht.begin();
}

void loop()
{
  Blynk.run();

  // Membaca data dari sensor DHT11
float t = dht.readTemperature(); //pembacaan sensor
float h = dht.readHumidity();

  // Menampilkan data ke Serial Monitor
Serial.print("% Temperature: ");
Serial.print(t);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(h);
Serial.println("% ");

  // Mengirim data ke Blynk
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, t);

  delay(2000); // Menghindari pembacaan yang terlalu cepat
}
