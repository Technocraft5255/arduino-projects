/*
  Fichier :       temp_reader.ino
  
  Description :   Le programme donne la pression, la température, l'humidité, le niveau de pluie, la vitesse et l'orientation du vent.
                  Version avec Light Sleep (ESP32)

  Auteur :        Emilien Mariau, basé sur les programmes de Jérôme TOMSKI
  Créé le :       13:06:2026
*/

#include <Adafruit_BME280.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "esp_sleep.h"

// Constantes du programme
#define BME_280_address 0x76
#define dataResfreshDelay 60000
#define pluvioPin 32
#define gyroPin 33
#define anemoPin 25
#define bmePinSDA 16
#define bmePinSCL 4
#define serialBaudRate 115200
#define debounceTime 5000

Adafruit_BME280 bme;

const char* ssid = "SMeteo";
const char* password = ")43200StationMeteo43200(";

volatile uint32_t pulseRainCount = 0;
volatile uint32_t pulseWindCount = 0;
volatile unsigned long lastRainMicros = 0;
volatile unsigned long lastWindMicros = 0;

float temperature;
float humidity;
float pressure;
int wind_direction_raw_value;
float wind_speed;
float rain_gauge;
String wind_direction;

esp_sleep_wakeup_cause_t wakeup_reason;

String directionNames[8] = { "N", "NE", "E", "SE", "S", "SO", "O", "NO" };
int weatherVaneValues[8] = { 3157, 1865, 379, 750, 1165, 2539, 3785, 3557 };

String gyroGetDirection(int measureValue) {
  int ecartMin = 4095;
  String direction;

  for (int i = 0; i < 8; i++) {
    int ecart = abs(measureValue - weatherVaneValues[i]);
    if (ecart < ecartMin) {
      ecartMin = ecart;
      direction = directionNames[i];
    }
  }
  return direction;
}

void IRAM_ATTR handleRainInterrupt() {
  unsigned long now = micros();
  if (now - lastRainMicros > debounceTime) {
    pulseRainCount++;
    lastRainMicros = now;
  }
}

void IRAM_ATTR handleWindInterrupt() {
  unsigned long now = micros();
  if (now - lastWindMicros > debounceTime) {
    pulseWindCount++;
    lastWindMicros = now;
  }
}

void sendDataToServer(float temperature, float humidity, float pressure,
                       float wind_speed, String wind_direction, float rain_gauge) {

  String url =
    "http://192.168.1.26:43880/"
    "?temperature=" + String(temperature, 3) +
    "&humidity=" + String(humidity, 3) +
    "&pressure=" + String(pressure, 3) +
    "&wind_speed=" + String(wind_speed, 3) +
    "&wind_direction=" + wind_direction +
    "&rain=" + String(rain_gauge, 3);

  HTTPClient http;
  http.begin(url);
  http.GET();
  http.end();
}

void setup() {
  Serial.begin(serialBaudRate);
  Wire.begin(bmePinSDA, bmePinSCL);

  pinMode(pluvioPin, INPUT_PULLUP);
  pinMode(gyroPin, INPUT);
  pinMode(anemoPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pluvioPin), handleRainInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(anemoPin), handleWindInterrupt, FALLING);

  if (!bme.begin(BME_280_address)) {
    while (1);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}

void loop() {
  wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_TIMER) {
    // Lecture capteurs
    temperature = bme.readTemperature();
    humidity = bme.readHumidity();
    pressure = bme.readPressure() / 100.0F;

    wind_speed = 2.4 * pulseWindCount / dataResfreshDelay * 1000;
    wind_direction_raw_value = analogRead(gyroPin);
    wind_direction = gyroGetDirection(wind_direction_raw_value);
    rain_gauge = 0.2794 * pulseRainCount;

    // Envoi serveur
    sendDataToServer(temperature, humidity, pressure,
                    wind_speed, wind_direction, rain_gauge);

    // Reset compteurs
    pulseWindCount = 0;
    pulseRainCount = 0;
  }

  // -----------------------------
  // CONFIG LIGHT SLEEP ESP32
  // -----------------------------

  // Réveil par timer (1 minute)
  esp_sleep_enable_timer_wakeup((uint64_t)dataResfreshDelay * 1000ULL);

  // Réveil par pluie + vent (GPIO)
  uint64_t mask = (1ULL << pluvioPin) | (1ULL << anemoPin);
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW);

  // Passage en light sleep
  esp_light_sleep_start();
}