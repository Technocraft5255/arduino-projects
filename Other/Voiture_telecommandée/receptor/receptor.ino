#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7);  // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int receivedValue[2] = { 0, 0 };
    radio.read(&receivedValue, sizeof(receivedValue));
    //forward back control
    if (receivedValue[0] > 0) {
      analogWrite(5, 0);
      analogWrite(3, receivedValue[0]);
    } else if (receivedValue[0] < 0) {
      analogWrite(3, 0);
      analogWrite(5, -receivedValue[0]);
    } else {
      analogWrite(3, 0);
      analogWrite(5, 0);
    }

    //turn control
    if (receivedValue[1] > 0) {
      analogWrite(10, 0);
      analogWrite(9, receivedValue[1]);
    } else if (receivedValue[1] < 0) {
      analogWrite(9, 0);
      analogWrite(10, -receivedValue[1]);
    } else {
      analogWrite(9, 0);
      analogWrite(10, 0);
    }


    Serial.print(receivedValue[0]);
    Serial.print(",");
    Serial.println(receivedValue[1]);
  }
}
