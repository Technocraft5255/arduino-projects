#include "tetris_forms.h"
#include <LedControl.h>
LedControl lc = LedControl(12, 10, 11, 1);
#define SW_pin 2
#define Y_pin 0
#define X_pin 1
int Y_value = 0;
int X_value = 0;
  
void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
}
void create_form() {
  return;
}

void loop() {
  Y_value = analogRead(Y_pin);
  X_value = analogRead(X_pin);
  Switch = 
}
