#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#define BLYNK_TEMPLATE_ID "TMPL6Kc0PwF_x"
#define BLYNK_TEMPLATE_NAME "Jasmine Security"
#define BLYNK_AUTH_TOKEN "Pwz5sfnm36MZtkzXW_Zm2v-8ujrCXeLN"

const char* ssid = "Mockingbird";
const char* password = "bakakaitou";

// inisialisasi Bot Token
#define BOTtoken "6629124355:AAFXra1rPAE6Ebx-t3s5V55D5T62cK4jyrE"  // Bot Token dari BotFather

// chat id dari @myidbot
#define CHAT_ID "1202228467"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 100;
unsigned long lastTimeBotRan;

#include <TinyGPS++.h>
#include <HardwareSerial.h>

HardwareSerial GPSSerial(1);
TinyGPSPlus gps;

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>

#define DOOR_SENSOR  4
#define buzzer 2
BlynkTimer timer;
char auth[] = "Pwz5sfnm36MZtkzXW_Zm2v-8ujrCXeLN"; //Enter the authentication code sent by Blynk to your Email
char pass[] = "bakakaitou"; //password WiFi
int flag=0;

void notifyOnButtonPress()
{
  int isButtonPressed = digitalRead(DOOR_SENSOR);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("ANCAMAN!!!");
    Blynk.logEvent("security_alert","Seseorang dalam BAHAYA");
    digitalWrite(buzzer, HIGH);
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
    Serial.println("Tertutup");
    digitalWrite(buzzer, LOW);
  }
}

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
    while(GPSSerial.available()) {
    gps.encode(GPSSerial.read());
  }
   if (gps.charsProcessed() > 10) {
    float currentLat = gps.location.lat();
    float currentLng = gps.location.lng();

    if (text == "/start") {
      String control = "Selamat Datang, " + from_name + ".\n";
      control += "Jasmine siap membantumu menemukannya\n\n";
      control += "/Lokasi Untuk Mengetahui lokasi saat ini \n";
      bot.sendMessage(chat_id, control, "");
    }

      
  if (text == "/Lokasi"){
     String lokasi = "Lokasi : https://www.google.com/maps/@";
      lokasi +=String(currentLat,6);
      lokasi +=",";
      lokasi +=String(currentLng,6);
      lokasi +=",21z?entry=ttu";
      bot.sendMessage(chat_id, lokasi, "");
  }  
 
   }
 
  }
}

void setup() {
  Serial.begin(115200);
  GPSSerial.begin(9600, SERIAL_8N1, 16, 17);
  // Koneksi Ke Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(DOOR_SENSOR,INPUT_PULLUP);
pinMode(buzzer, OUTPUT);
timer.setInterval(5000L,notifyOnButtonPress); 
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  Blynk.run();
  timer.run();
}