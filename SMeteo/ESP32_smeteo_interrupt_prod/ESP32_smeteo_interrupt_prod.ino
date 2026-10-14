/*
  Fichier :       temp_reader.ino
  
  Description :   Le programme donne la pression, la température, l'humidité, le niveau de pluie, la vitesse et l'orientation du vent.

  Auteur :        Emilien Mariau, basé sur les programmes de Jérôme TOMSKI (https://passionelectronique.fr/)
  Créé le :       13:06:2026

*/

#include <Adafruit_BME280.h>  // Inclusion de la librairie BME280 d'Adafruit
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Constantes du programme
#define BME_280_address 0x76
#define dataResfreshDelay 60000  // Délai de rafraîchissement de l'affichage (en millisecondes)
#define pluvioPin 32
#define gyroPin 33
#define anemoPin 25
#define bmePinSDA 16
#define bmePinSCL 4
#define serialBaudRate 115200
#define strFormat(a) F(a)
#define debounceTime 5000  // 5 ms

Adafruit_BME280 bme;

const char* ssid = "SMeteo";
const char* password = ")43200StationMeteo43200(";


volatile u_int pulseRainCount = 0;
volatile u_int pulseWindCount = 0;
volatile unsigned long lastRainMicros = 0;
volatile unsigned long lastWindMicros = 0;


float temperature;
float humidity;
float pressure;
int wind_direction_raw_value;
float wind_speed;
float rain_gauge;
String wind_direction;

String directionNames[8] = { "N", "NE", "E", "SE", "S", "SO", "O", "NO" };
// Analog values calculated by R / ( R + 9.8k) * 4095
int weatherVaneValues[8] = { 3157, 1865, 379, 750, 1165, 2539, 3785, 3557 };

String gyroGetDirection(int measureValue) {
  int ecartMin = 4095;
  String direction;

  for(int angleIndex = 0; angleIndex < 8; angleIndex++){
    int ecart = abs(measureValue - weatherVaneValues[angleIndex]);
    if (ecart < ecartMin){
      ecartMin = ecart;
      direction = directionNames[angleIndex];
    }
  }
  return direction;
}

void IRAM_ATTR handleRainInterrupt() {
  // Rain interrupt handling
  unsigned long now = micros();
  if (now - lastRainMicros > debounceTime) {
    pulseRainCount++;
    lastRainMicros = now;
  }
}

void IRAM_ATTR handleWindInterrupt() {
  // Wind interrupt handling
  unsigned long now = micros();
  if (now - lastWindMicros > debounceTime) {
    pulseWindCount++;
    lastWindMicros = now;
  }
}

void sendDataToServer(float temperature, float humidity, float pressure, float wind_speed, String wind_direction, float rain_gauge) {
  String url =
    "http://192.168.1.26:43880/"
    "?temperature="
    + String(temperature, 3)
    + "&humidity=" + String(humidity, 3)
    + "&pressure=" + String(pressure, 3)
    + "&wind_speed=" + String(wind_speed, 3)
    + "&wind_direction=" + wind_direction
    + "&rain=" + String(rain_gauge, 3);

  HTTPClient http;

  http.begin(url);

  int httpCode = http.GET();

  /*if (httpCode > 0) {
    Serial.printf("Code HTTP : %d\n", httpCode);
    Serial.println(http.getString());
  } else {
    Serial.printf("Erreur : %s\n", http.errorToString(httpCode).c_str());
  }*/

  http.end();
}

void setup() {
  // Initialisation du port série (pour l'envoi d'infos via le moniteur série de l'IDE Arduino)
  Serial.begin(serialBaudRate);
  Wire.begin(bmePinSDA, bmePinSCL);  // SDA, SCL

  // Initialisation des capteurs meteo
  pinMode(pluvioPin, INPUT_PULLUP);
  pinMode(gyroPin, INPUT);
  pinMode(anemoPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pluvioPin), handleRainInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(anemoPin), handleWindInterrupt, FALLING);

  if (!bme.begin(BME_280_address)) {
    //Serial.println(strFormat("--> ÉCHEC de l'initialistation du BME280"));
    while (1)
      ;  // Arrêt du programme, en cas d'échec de l'initialisation
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //Serial.print("Connexion WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    /*Serial.print(".");
    Serial.print(" Status=");
    Serial.println(WiFi.status());*/
  }

  //Serial.println("\nConnecté !");
}


void loop() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  wind_speed = 2.4 * pulseWindCount / dataResfreshDelay * 1000;
  wind_direction_raw_value = analogRead(gyroPin);
  wind_direction = gyroGetDirection(wind_direction_raw_value);
  rain_gauge = 0.2794 * pulseRainCount;
  sendDataToServer(temperature, humidity, pressure, wind_speed, wind_direction, rain_gauge);
  /*Serial.print(strFormat("Temperature : "));
  Serial.print(temperature);
  Serial.print(strFormat(", Humidity : "));
  Serial.print(humidity);
  Serial.print(strFormat(", Pressure : "));
  Serial.print(pressure);
  Serial.print(strFormat(", Wind_Pulse : "));
  Serial.print(pulseWindCount);
  Serial.print(strFormat(", Rain_Pulse : "));
  Serial.print(pulseRainCount);
  Serial.print(strFormat(", Wind_Direction_raw_value : "));
  Serial.print(wind_direction_raw_value);
  Serial.print(strFormat(", Wind_Real_Speed : "));
  Serial.print(wind_speed);
  Serial.print(strFormat(", Rain_Real  : "));
  Serial.print(rain_gauge);
  Serial.print(strFormat(", Angle : "));
  Serial.println();*/

  pulseWindCount = 0;
  pulseRainCount = 0;
  delay(dataResfreshDelay);
}