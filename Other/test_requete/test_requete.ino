#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const char* ssid = "SMeteo";
const char* password = ")43200StationMeteo43200(";

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);

  Wire.begin(4, 5); // SDA, SCL

  if (!bme.begin(0x76)) { // 0x76 ou 0x77
    Serial.println("Capteur BME280 non trouvé !");
    while (1);
  }
  Serial.println("BME280 prêt !");
  WiFi.begin(ssid, password);
  Serial.print("Connexion WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnecté !");
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String url = "http://192.168.1.26:8080/?temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&pressure=" + String(pressure);

    http.begin(client, url);
    int httpResponseCode = http.GET();

    Serial.print("Requête envoyée : ");
    Serial.println(url);
    Serial.print("Code réponse : ");
    Serial.println(httpResponseCode);

    http.end();
  }
  delay(120000); // 2 min
}