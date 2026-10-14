#include <SoftwareSerial.h>
SoftwareSerial esp(2, 3);

void setup() {
  Serial.begin(9600);
  esp.begin(74880); // on testera d'autres valeurs si besoin
}

void loop() {
  if (esp.available()) Serial.write(esp.read());
  if (Serial.available()) esp.write(Serial.read());
}