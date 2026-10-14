#include <LiquidCrystal.h>
#include "forms.h"
#include "tableau.h"

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  lcd.createChar(0,player);
  lcd.createChar(1,orb);
  lcd.begin(20,4);
  lcd.write(byte(0));
  lcd.write(byte(1));
}

void loop() {
  
}
