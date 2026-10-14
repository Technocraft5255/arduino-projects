/*
  Generateur de signaux
 */
#include <LiquidCrystal.h>
#include "forms.h"

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int frequency10P0 = 1;
int frequency10P1 = 0;
int frequency10P2 = 0;
int frequency10P3 = 0;
int frequency10P4 = 0;
int frequency10P5 = 0;
int frequency10P6 = 0;
int frequency10P7 = 0;
int frequency10P8 = 0;

//map(0,1023,0,99);
void setup() {
  lcd.begin(16,2);
  lcd.createChar(0,square_N);
  lcd.createChar(1,square_Y);
  lcd.createChar(2,triangle_N);
  lcd.createChar(3,triangle_Y);
  lcd.createChar(4,sinus_N);
  lcd.createChar(5,sinus_Y);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(2,INPUT_PULLUP);
  
}

void loop() {
  test_change_signal();
  lcd.print("F: ");
  lcd.print(frequency10P8);
  lcd.print(frequency10P7);
  lcd.print(frequency10P6);
  lcd.print(" ");
  lcd.print(frequency10P5);
  lcd.print(frequency10P4);
  lcd.print(frequency10P3);
  lcd.print(" ");
  lcd.print(frequency10P2);
  lcd.print(frequency10P1);
  lcd.print(frequency10P0);
  lcd.print("Hz");
  lcd.setCursor(0,1);
  lcd.print("Signal :");
  if (type == "square") {
    lcd.write(byte(1));
    lcd.print(' ');
    lcd.write(byte(2));
    lcd.print(' ');
    lcd.write(byte(4));
  }
  else if (type == "triangle") {
    lcd.write(byte(0));
    lcd.print(' ');
    lcd.write(byte(3));
    lcd.print(' ');
    lcd.write(byte(4));
  }
  else if (type == "square") {
    lcd.write(byte(1));
    lcd.print(' ');
    lcd.write(byte(2));
    lcd.print(' ');
    lcd.write(byte(4));
  }
  lcd.setCursor(0,0);
}
