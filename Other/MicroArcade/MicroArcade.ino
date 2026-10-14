#include <LiquidCrystal.h>
#include "display.h"
// initialisiation de la librairie
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int cursor_pos = 0;
String current_page = "menu";

void setup() {
  // initialisation de l'ecran de 20x4 caractères
  lcd.begin(20, 4);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(6, INPUT_PULLUP);
  display_menu();
}

void loop() {
  if (analogRead(A0) > 1000) {
    if (current_page=="menu"){
      lcd.setCursor(0, cursor_pos);
      lcd.print("  ");
      if (cursor_pos == 3) {cursor_pos = 0;}
      else {cursor_pos++;}
      lcd.setCursor(0, cursor_pos);
      lcd.write(0x3E);
    }
    if (current_page=="credits"){
      display_credits(1);
    }
    while (analogRead(A0) > 650);
  }
  
  if (analogRead(A0) < 23) {
    if (current_page=="menu"){
      lcd.setCursor(0, cursor_pos);
      lcd.print("  ");
      if (cursor_pos == 0) {cursor_pos = 3;}
      else {cursor_pos--;}
      lcd.setCursor(0, cursor_pos);
      lcd.write(0x3E);
    }
    if (current_page=="credits"){
      display_credits(0);

    }
    while (analogRead(A0) < 350);
  }
  
  if (analogRead(A1) > 1000&&current_page=="credits"){
    display_menu();
    while (analogRead(A0) > 650);
    }
    
  if ((analogRead(A1) < 23||!digitalRead(6)) && cursor_pos == 3&&current_page=="menu") {
    current_page = "credits";
    cursor_pos = 0;
    display_credits(0);
    while (!digitalRead(6)&&(analogRead(A0) < 350));
  }
}
