#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

#define buzzer 49

const byte carteEmilien[4] = {21, 151, 120, 222};
const byte carteErnest[4] = {9, 96, 108, 68};

const int pinRST = 5;
const int pinSDA = 53;

int argentEmilien = 200;
int argentErnest = 200;

int EmiEEPROMaddress = 0;
int ErnEEPROMaddress = 2;

MFRC522 rfid(pinSDA, pinRST);


void intEEPROMwrite(int address , int number){
  byte byte1 = (number >> 8) & 0xFF;
  byte byte2 = number & 0xFF;

  EEPROM.write(address , byte1);
  EEPROM.write(address + 1 , byte2);
}

int intEEPROMread(int address){
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  
  int result = (byte1 << 8) + byte2;
  return result;
}

void setup(){
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  SPI.begin();
  rfid.PCD_Init();

  argentEmilien = intEEPROMread(EmiEEPROMaddress);
  argentErnest = intEEPROMread(ErnEEPROMaddress);

}
void loop(){
  int carteEmiAccept = 0;
  int carteErnAccept = 0;

  if (rfid.PICC_IsNewCardPresent())
  {
    if (rfid.PICC_ReadCardSerial())
    {
      for (byte i = 0; i < rfid.uid.size; i++)
      {
        if (rfid.uid.uidByte[i] != carteEmilien[i]) {
          carteEmiAccept++;
        }
        if (rfid.uid.uidByte[i] != carteErnest[i]) {
          carteErnAccept++;
        }
      }
      if (carteEmiAccept == 0) {
        String argent = Serial.readString();
        if (argent != "") {
          int int_argent = argent.toInt();
          argentEmilien = argentEmilien + int_argent;
          intEEPROMwrite(EmiEEPROMaddress , argentEmilien);
          digitalWrite(buzzer, HIGH);
          delay(150);
          digitalWrite(buzzer, LOW);
          Serial.print("Il reste ");
          Serial.print(argentEmilien);
          Serial.println(" Euros a Emilien");
        }

      }
      else if (carteErnAccept == 0) {
        String argent = Serial.readString();
        if (argent != "") {
          int int_argent = argent.toInt();
          argentErnest = argentErnest + int_argent;
          intEEPROMwrite(ErnEEPROMaddress , argentErnest);
          digitalWrite(buzzer, HIGH);
          delay(150);
          digitalWrite(buzzer, LOW);
          Serial.print("Il reste ");
          Serial.print(argentErnest);
          Serial.println(" Euros a Ernest");
          }
        
      }
      else {
        Serial.println("invalid card");
      }
    }
  }
}
