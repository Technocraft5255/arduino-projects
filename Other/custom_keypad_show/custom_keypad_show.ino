#include <LiquidCrystal.h>
#include <Keypad.h>

const String secret = "12547";

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


char hexaKeys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
int attemps = 3;
String code;
boolean locked = false;
byte rowPins[4] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[4] = {31, 33, 35, 37}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, 4, 4);

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    if (customKey == 'D' && not locked) {
      lcd.clear();
      code = "";
    }
    else if (customKey == '#') {
      if (code == secret) {
        lcd.clear();
        lcd.print("Code Valide");
        code = "";
      }
      else {
        lcd.clear();
        if (attemps > 1) {
          attemps = attemps - 1;
          lcd.print("Code Incorrect");
          lcd.setCursor(0, 1);
          lcd.print("  essais restants");
          lcd.setCursor(0, 1);
          lcd.print(attemps);
          code = "";
          delay(3000);
          lcd.clear();

        }
        else {
          lcd.print("Code Bloque");
          lcd.setCursor(16, 1);
          locked = true;
        }
      }
    }
    else if (not locked) {
      lcd.print(customKey);
      String str_customKey = String(customKey);
      code = code + customKey;
    }
  }
}
