#include <ESP8266WiFi.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5); // SDA, SCL

  if (!bme.begin(0x76)) { // 0x76 ou 0x77
    Serial.println("Capteur BME280 non trouvé !");
    while (1);
  }

  Serial.println("BME280 prêt !");
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidité: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pression: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.println("------------------");

  delay(2000);
}