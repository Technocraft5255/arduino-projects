#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Scan I2C...");
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Trouvé à : 0x");
      Serial.println(address, HEX);
    }
  }
  Serial.println("Scan terminé.");
}
void loop() {}

