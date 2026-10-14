#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  int sensorValue = analogRead(A0);
  radio.write(&sensorValue, sizeof(sensorValue));
  delay(50);  // petite pause pour éviter de saturer le lien
}
