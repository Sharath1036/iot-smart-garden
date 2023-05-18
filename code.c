#define BLYNK_TEMPLATE_ID "TMPLVEyXYqgE"
#define BLYNK_TEMPLATE_NAME "IOT Smart Garden"
#define BLYNK_AUTH_TOKEN "-fJ_yoWbm5qAESZ-rLMX4u7xp4n1XZZQ"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 21
#define DHTTYPE DHT11

const int waterLevelSensor = 2;
const int moistureLevelSensor = 15;
const int relay = 23;

int waterLevel;
int moistureLevel;

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

char ssid[] = "POCO X4 Pro 5G";
char pass[] = "arshnirmal";


void sendSensor1() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);

}

void sendSensor2() {
  waterLevel = analogRead(waterLevelSensor);
  waterLevel = map(waterLevel,0,2000,0,20);
  moistureLevel = analogRead(moistureLevelSensor);
  moistureLevel = map(moistureLevel,0,4000,0,20);
  

  Blynk.virtualWrite(V7, waterLevel);
  Blynk.virtualWrite(V8, moistureLevel);
}



void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
   
  dht.begin();

  timer.setInterval(2000L, sendSensor1);
  timer.setInterval(5000L, sendSensor2);

}

void loop() {
  Blynk.run();
//  timer.run();   
}
