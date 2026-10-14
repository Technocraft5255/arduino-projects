#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(4, 5); 

const uint64_t adresse = 0x1111111111;
const int taille = 32;
char message[taille + 1]; 

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Recepteur RF24");
  radio.begin();
  radio.openReadingPipe(1, adresse);
  radio.startListening();
}

void loop(void)
{
  while ( radio.available() )
  {
    radio.read( message, taille );
    Serial.print("Message recu : ");
    Serial.println(message);
  }
}