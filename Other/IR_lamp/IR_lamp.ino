#include "IRremote.h"
#include "IR.h"

#define redPin 4
#define greenPin 3
#define bluePin 2

IRrecv irrecv(RECEIVER);
decode_results results;

String tempTouch;

void setup() {
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
}

void loop()
{
  int tmpValue;
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0xFFA25D: Serial.println("POWER");         tempTouch = "POWER";         break;
      case 0xFFE21D: Serial.println("FUNC/STOP");     tempTouch = "FUNC/STOP";     break;
      case 0xFF629D: Serial.println("VOL+");          tempTouch = "VOL+";          break;
      case 0xFF22DD: Serial.println("FAST BACK");     tempTouch = "FAST BACK";     break;
      case 0xFF02FD: Serial.println("PAUSE");         tempTouch = "PAUSE";         break;
      case 0xFFC23D: Serial.println("FAST FORWARD");  tempTouch = "FAST FORWARD";  break;
      case 0xFFE01F: Serial.println("DOWN");          tempTouch = "DOWN";          break;
      case 0xFFA857: Serial.println("VOL-");          tempTouch = "VOL-";          break;
      case 0xFF906F: Serial.println("UP");            tempTouch = "UP";            break;
      case 0xFF9867: Serial.println("EQ");            tempTouch = "EQ";            break;
      case 0xFFB04F: Serial.println("ST/REPT");       tempTouch = "ST/REPT";       break;
      case 0xFF6897: Serial.println("0");             tempTouch = "0";             break;
      case 0xFF30CF: Serial.println("1");             tempTouch = "1";             break;
      case 0xFF18E7: Serial.println("2");             tempTouch = "2";             break;
      case 0xFF7A85: Serial.println("3");             tempTouch = "3";             break;
      case 0xFF10EF: Serial.println("4");             tempTouch = "4";             break;
      case 0xFF38C7: Serial.println("5");             tempTouch = "5";             break;
      case 0xFF5AA5: Serial.println("6");             tempTouch = "6";             break;
      case 0xFF42BD: Serial.println("7");             tempTouch = "7";             break;
      case 0xFF4AB5: Serial.println("8");             tempTouch = "8";             break;
      case 0xFF52AD: Serial.println("9");             tempTouch = "9";             break;
    }
    results.value = tmpValue;
    irrecv.resume();
  }
  if (tempTouch == "1") {
    digitalWrite(redPin,HIGH);
    digitalWrite(bluePin,LOW);
    digitalWrite(greenPin,LOW); 
  }
  else if (tempTouch == "2") {
    digitalWrite(redPin,LOW);
    digitalWrite(bluePin,HIGH);
    digitalWrite(greenPin,LOW);
  }
  else if (tempTouch == "3") {
    digitalWrite(redPin,LOW);
    digitalWrite(bluePin,LOW);
    digitalWrite(greenPin,HIGH);
  }
  else if (tempTouch == "4") {
    digitalWrite(redPin,HIGH);
    digitalWrite(bluePin,HIGH);
    digitalWrite(greenPin,LOW);
  }
  else if (tempTouch == "5") {
    digitalWrite(redPin,LOW);
    digitalWrite(bluePin,HIGH);
    digitalWrite(greenPin,HIGH);
  }
  else if (tempTouch == "6") {
    digitalWrite(redPin,HIGH);
    digitalWrite(bluePin,LOW);
    digitalWrite(greenPin,HIGH);
  }
  else if (tempTouch == "7") {
    digitalWrite(redPin,HIGH);
    digitalWrite(bluePin,HIGH);
    digitalWrite(greenPin,HIGH);
  }
  else if (tempTouch == "8") {
    digitalWrite(redPin,LOW);
    digitalWrite(bluePin,LOW);
    digitalWrite(greenPin,LOW);
  }
}
