#include <LiquidCrystal.h>

#define b1 3
#define b2 2

boolean start = false;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int centisecondes = 0;
int desisecondes = 0;
int secondes = 0;
int minutes = 0;
int heures = 0;


void setup() {
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  lcd.begin(16, 2);
}

void loop() {
  if (digitalRead(b1)==HIGH) {
    start = true;
  }
  if (start==true) {
    centisecondes++;
    if (centisecondes == 10) {
      centisecondes = 0;
      desisecondes++;
    }
    if (desisecondes == 10) {
      desisecondes = 0;
      secondes++;
    }
    if (secondes == 60) {
      secondes = 0;
      minutes++;
    }
    if (minutes == 60) {
      minutes = 0;
      heures++;
    }
    if (heures < 10) {
      lcd.print(0);
    }
    lcd.print(heures);
    lcd.print(':');
    if (minutes < 10) {
      lcd.print(0);
    }
    lcd.print(minutes);
    lcd.print(':');
    if (secondes < 10) {
      lcd.print(0);
    }
    lcd.print(secondes);
    lcd.print('.');
    lcd.print(desisecondes);
    lcd.print(centisecondes);
    lcd.setCursor(0,0);
    delay(5);
  }
}
