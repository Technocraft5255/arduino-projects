#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

const byte bonUID[4] = {169, 96, 148, 179};
const int pinRST = 5; // pin RST du module RC522
const int pinSDA = 53; // pin SDA du module RC522
MFRC522 rfid(pinSDA, pinRST);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
  lcd.begin(16, 2);
  SPI.begin();
  rfid.PCD_Init();

}
void loop()
{
  int refus = 0; // quand cette variable n'est pas nulle, c'est que le code est refusé
  if (rfid.PICC_IsNewCardPresent()) // on a dédecté un tag
  {
    if (rfid.PICC_ReadCardSerial()) // on a lu avec succès son contenu
    {
      for (byte i = 0; i < rfid.uid.size; i++) // comparaison avec le bon UID
      {
        if (rfid.uid.uidByte[i] != bonUID[i]) {
          refus++;
        }
      }
      if (refus == 0) // UID accepté
      {
        // allume LED verte et active relais pendant 3 secondes
        lcd.print("bonjour emilien");
        lcd.setCursor(0,0);
        
      }
      else { // UID refusé
        // allume LED rouge et active buzzer pendant 3 secondes
        lcd.print("scan echoue      ");
        lcd.setCursor(0,0);
      }
    }
  }
}
