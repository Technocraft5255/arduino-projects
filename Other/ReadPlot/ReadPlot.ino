#include <BMP280_DEV.h> 
#include <DHT11.h>

DHT11 dht11(2);
BMP280_DEV bmp280(10);


float temperatureB1, pressureB1, altitudeB1;
void setup() {
    Serial.begin(9600);
    bmp280.begin();
    bmp280.setTimeStandby(TIME_STANDBY_2000MS);
    bmp280.startNormalConversion();
}

void loop() {
    int temperatureDH, humidityDH;
    int result = dht11.readTemperatureHumidity(temperatureDH, humidityDH);
    if (result == 0) {
        Serial.print("Temperature with DHT11:");
        Serial.print(temperatureDH);
        Serial.print(",Humidity with DHT11:");
        Serial.println(humidityDH);
    }

    if (bmp280.getMeasurements(temperatureB1, pressureB1, altitudeB1))    // Check if the measurement is complete
  {
    Serial.print(temperatureB1);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressureB1);    
    Serial.print(F("hPa   "));
    Serial.print(altitudeB1);
    Serial.println(F("m"));  
  }
}
