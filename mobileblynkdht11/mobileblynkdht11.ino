/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6aQYDujH_"
#define BLYNK_TEMPLATE_NAME "Web Dashboard"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#define APP_DEBUG
#include <DHT.h> //Library untuk DHT
#define DHTPIN D2 //deklarasi pin D2 untuk output dari DHT11
#define DHTTYPE DHT11 //Tipe DHT11
DHT dht(DHTPIN, DHTTYPE);

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
BlynkTimer timer;
#define relay D7
WidgetLED led1(V3);
void sendSensor()
{
float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  if (t > 30 && h > 60)
  {
    led1.on();
    digitalWrite(relay, HIGH);
  }
  else
  {
    led1.off();
    digitalWrite(relay, LOW);
  }
}


void setup()
{
   Serial.begin(115200);
  delay(100);
  dht.begin(); //mengaktifkan DHT11
  BlynkEdgent.begin();
  timer.setInterval(1000L, sendSensor);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
}

void loop() {
  BlynkEdgent.run();
  timer.run(); //menjalankan timer
}

