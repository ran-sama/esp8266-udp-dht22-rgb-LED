#include "DHT.h"
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

#define DHTTYPE DHT22
#define SHIELD_LED_R 4
#define SHIELD_LED_G 2
#define SHIELD_LED_B 0

const int DHTPin = 5;
const char* ssid = "name";
const char* password = "password";
unsigned int localUdpPort = 4444;

WiFiUDP Udp;
DHT dht(DHTPin, DHTTYPE);

void setup() {
  Udp.begin(localUdpPort);
  pinMode(SHIELD_LED_R, OUTPUT);
  pinMode(SHIELD_LED_G, OUTPUT);
  pinMode(SHIELD_LED_B, OUTPUT);
  delay(10);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  digitalWrite(SHIELD_LED_R, LOW);
  digitalWrite(SHIELD_LED_G, LOW);
  digitalWrite(SHIELD_LED_B, LOW);
  delay(15000);
}

void loop() {
  delay(15000);
  float raw_humidity = dht.readHumidity();
  int humidity = round(dht.readHumidity());

if (humidity > 59)
    {
    digitalWrite(SHIELD_LED_R, HIGH);
    digitalWrite(SHIELD_LED_G, LOW);
    digitalWrite(SHIELD_LED_B, LOW);
    }
else if (humidity >= 41 && humidity <=59)
    {
    digitalWrite(SHIELD_LED_R, LOW);
    digitalWrite(SHIELD_LED_G, HIGH);
    digitalWrite(SHIELD_LED_B, LOW);
    }
else if (humidity < 41)
    {
    digitalWrite(SHIELD_LED_R, LOW);
    digitalWrite(SHIELD_LED_G, LOW);
    digitalWrite(SHIELD_LED_B, HIGH);
    }
else
    {
    delay(1);
    }
 String replyPacket = String(raw_humidity);
 Udp.beginPacket("10.0.0.17", 8888);
 Udp.write(replyPacket.c_str());
 Udp.endPacket();
}

