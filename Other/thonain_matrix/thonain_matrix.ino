#include "LedControl.h"
/*
pin 12 is connected to the DataIn 
pin 11 is connected to the CLK 
pin 10 is connected to LOAD 
Le 1 correspond au nb de matrices à leds utilisé
*/
LedControl lc=LedControl(12,11,10,1);
void setup() {
    lc.shutdown(0,false);
    lc.clearDisplay(0);
}
void loop() { 
    for(int i=11;i>1;i--) {
    lc.setIntensity(0,i);
    lc.setColumn(0,0,B11111000); // gere toute une ligne à la fois
    lc.setColumn(0,1,B00100000);
    lc.setColumn(0,2,B00100000);
    lc.setColumn(0,3,B00100110);
    lc.setColumn(0,4,B00101001);
    lc.setColumn(0,5,B00001111);
    lc.setColumn(0,6,B00001001);
    lc.setColumn(0,7,B00001001);
    delay(30);
    }
    lc.clearDisplay(0);
    delay(80);
 
for(int i=0;i<11;i++) {
    lc.setIntensity(0,i);
    lc.setColumn(0,0,B11111000); // gere toute une ligne à la fois
    lc.setColumn(0,1,B00100000);
    lc.setColumn(0,2,B00100000);
    lc.setColumn(0,3,B00100110);
    lc.setColumn(0,4,B00101001);
    lc.setColumn(0,5,B00001111);
    lc.setColumn(0,6,B00001001);
    lc.setColumn(0,7,B00001001);
    delay(30);
    }  
}
