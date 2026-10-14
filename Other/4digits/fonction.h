#define pinA 12
#define pinB 11
#define pinC 10
#define pinD 9
#define pinE 8
#define pinF 7
#define pinG 6
#define pinDP 5
#define D1 22
#define D2 23
#define D3 24
#define D4 25

/*    A
    ---- 
   |    |  B
 F |  G |
    ----
   |    |
 E |    |  C
    ----
     D      */
void show_num(char num,int display_digit,bool with_dp = false,bool a =0,bool b =0,bool c =0,bool d =0,bool e =0,bool f =0,bool g =0) {
  if (with_dp == true) {
    digitalWrite(pinDP,HIGH);
  }
  else {
    digitalWrite(pinDP,LOW);
  }
  switch(num) {
    case 'c':
      digitalWrite(pinA,a);
      digitalWrite(pinB,b);
      digitalWrite(pinC,c);
      digitalWrite(pinD,d);
      digitalWrite(pinE,e);
      digitalWrite(pinF,f);
      digitalWrite(pinG,g);
      break;
    case 0:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,HIGH);
      digitalWrite(pinE,HIGH);
      digitalWrite(pinF,HIGH);
      digitalWrite(pinG,LOW);
      break;
    case 1:
      digitalWrite(pinA,LOW);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,LOW);
      digitalWrite(pinE,LOW);
      digitalWrite(pinF,LOW);
      digitalWrite(pinG,LOW);
      break;
    case 2:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,LOW);
      digitalWrite(pinD,HIGH);
      digitalWrite(pinE,HIGH);
      digitalWrite(pinF,LOW);
      digitalWrite(pinG,HIGH);
      break;
    case 3:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,HIGH);
      digitalWrite(pinE,LOW);
      digitalWrite(pinF,LOW);
      digitalWrite(pinG,HIGH);
      break;
    case 4:
      digitalWrite(pinA,LOW);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,LOW);
      digitalWrite(pinE,LOW);
      digitalWrite(pinF,HIGH);
      digitalWrite(pinG,HIGH);
      break;
    case 5:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,LOW);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,HIGH);
      digitalWrite(pinE,LOW);
      digitalWrite(pinF,HIGH);
      digitalWrite(pinG,HIGH);
      break;
    case 6:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,LOW);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,HIGH);
      digitalWrite(pinE,HIGH);
      digitalWrite(pinF,HIGH);
      digitalWrite(pinG,HIGH);
      break;
    case 7:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,LOW);
      digitalWrite(pinE,LOW);
      digitalWrite(pinF,LOW);
      digitalWrite(pinG,LOW);
      break;
    case 8:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,HIGH);
      digitalWrite(pinE,HIGH);
      digitalWrite(pinF,HIGH);
      digitalWrite(pinG,HIGH);
      break;
    case 9:
      digitalWrite(pinA,HIGH);
      digitalWrite(pinB,HIGH);
      digitalWrite(pinC,HIGH);
      digitalWrite(pinD,HIGH);
      digitalWrite(pinE,LOW);
      digitalWrite(pinF,HIGH);
      digitalWrite(pinG,HIGH);
      break;
  }
  switch(display_digit) {
    case 1:
      digitalWrite(D1,HIGH);
      digitalWrite(D2,LOW);
      digitalWrite(D3,LOW);
      digitalWrite(D4,LOW);
      delay(4);
      break;
    case 2:
      digitalWrite(D1,LOW);
      digitalWrite(D2,HIGH);
      digitalWrite(D3,LOW);
      digitalWrite(D4,LOW);
      delay(4);
      break;
    case 3:
      digitalWrite(D1,LOW);
      digitalWrite(D2,LOW);
      digitalWrite(D3,HIGH);
      digitalWrite(D4,LOW);
      delay(4);
      break;
    case 4:
      digitalWrite(D1,LOW);
      digitalWrite(D2,LOW);
      digitalWrite(D3,LOW);
      digitalWrite(D4,HIGH);
      delay(4);
      break;
  }
}
