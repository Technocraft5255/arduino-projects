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
#define dataResfreshDelay 15000  // Délai de rafraîchissement de l'affichage (en millisecondes)
#define pluvioPin 35
#define gyroPin 32
#define anemoPin 33
#define bmePinSDA 16
#define bmePinSCL 4
#define serialBaudRate 115200
#define strFormat(a) F(a)

Adafruit_BME280 bme;

const char* ssid = "SMeteo";
const char* password = ")43200StationMeteo43200(";


volatile u_int pulseRainCount = 0;
volatile u_int pulseWindCount = 0;
volatile u_int pulseRainTime[50];
volatile u_int pulseRainTimeCount = 0;


unsigned long lastSendTime = 0;

float temperature;
float humidity;
float pressure;
int wind_direction_raw_value;
float wind_speed;
float rain_gauge;
String wind_direction;

String directionNames[8] = { "N", "NE", "E", "SE", "S", "SO", "O", "NO" };
int weatherVaneValues[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
int angleValues[8] = { 0, 45, 90, 135, 180, 225, 270, 315 };

int gyroGetAngle(int measureValue) {
  int nearestValueIndex = -1;
  int minimalDifference = 32000;

  for (int i = 0; i < 8; i++) {
    if (abs(measureValue - weatherVaneValues[i]) < minimalDifference) {
      minimalDifference = abs(measureValue - weatherVaneValues[i]);
      nearestValueIndex = i;
    }
  }
  return angleValues[nearestValueIndex];
}

void IRAM_ATTR  handleRainInterrupt(){
  // Rain interrupt handling
  pulseRainCount++;
  u_int now = micros();
  pulseRainTime[pulseRainTimeCount] = now;
  pulseRainTimeCount++;
}

void IRAM_ATTR  handleWindInterrupt(){
  // Wind interrupt handling
  pulseWindCount++;
}

void sendDataToServer(float temperature, float humidity, float pressure, float wind_speed, String wind_direction, float rain_gauge) {
  String url =
    "http://192.168.1.26:43880/"
    "?temperature=" + String(temperature, 3) 
    + "&humidity=" + String(humidity, 3) 
    + "&pressure=" + String(pressure, 3) 
    + "&wind_speed=" + String(wind_speed, 3) 
    + "&wind_direction=" + wind_direction 
    + "&rain=" + String(rain_gauge, 3);

  HTTPClient http;

  http.begin(url);

  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("Code HTTP : %d\n", httpCode);
    Serial.println(http.getString());
  } else {
    Serial.printf("Erreur : %s\n",
                  http.errorToString(httpCode).c_str());
  }

  http.end();
}

void setup() {
  // Initialisation du port série (pour l'envoi d'infos via le moniteur série de l'IDE Arduino)
  Serial.begin(serialBaudRate);
  Wire.begin(bmePinSDA, bmePinSCL);  // SDA, SCL

  // Initialisation des capteurs meteo
  pinMode(pluvioPin, INPUT);
  pinMode(gyroPin, INPUT);
  pinMode(anemoPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pluvioPin), handleRainInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(anemoPin), handleWindInterrupt, FALLING);

  if (!bme.begin(BME_280_address)) {
    Serial.println(strFormat("--> ÉCHEC de l'initialistation du BME280"));
    while (1)
      ;  // Arrêt du programme, en cas d'échec de l'initialisation
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connexion WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print(" Status=");
    Serial.println(WiFi.status());
  }

  Serial.println("\nConnecté !");
}


void loop() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  wind_speed = 2.4 * pulseWindCount / dataResfreshDelay * 1000;
  wind_direction_raw_value = analogRead(gyroPin);
  wind_direction = "NE";
  rain_gauge = 0.2794 * pulseRainCount;
  //sendDataToServer(temperature, humidity, pressure, wind_speed, wind_direction, rain_gauge);
  Serial.print(strFormat("Temperature : "));
  Serial.print(temperature);
  Serial.print(strFormat(", Humidity : "));
  Serial.print(humidity);
  Serial.print(strFormat(", Pressure : "));
  Serial.print(pressure);
  Serial.print(strFormat(", Wind Pulse : "));
  Serial.print(pulseWindCount);
  Serial.print(strFormat(", Rain Pulse : "));
  Serial.print(pulseRainCount);
  Serial.print(strFormat(", Wind Direction raw value : "));
  Serial.print(wind_direction_raw_value);
  Serial.print(strFormat(", Wind Real Speed : "));
  Serial.print(wind_speed);
  Serial.print(strFormat(", Rain Real  : "));
  Serial.println(rain_gauge);
  for(int i=0;i<pulseRainTimeCount;i++){
    Serial.print(pulseRainTime[i]);
    Serial.print("    ");
  }
  Serial.println(" //");

  pulseWindCount = 0;
  pulseRainCount = 0;
  delay(dataResfreshDelay);
}