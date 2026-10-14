/*     A
     ----
  B |    | C
    | D  |
     ----
  E |    | F
    |    |
     ----   • H
      G         */

#define pinA 12
#define pinB 11
#define pinC 10
#define pinD 9
#define pinE 8
#define pinF 7
#define pinG 6
#define pinH 5


void setup() {
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  pinMode(pinC,OUTPUT);
  pinMode(pinD,OUTPUT);
  pinMode(pinE,OUTPUT);
  pinMode(pinF,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinH,OUTPUT);
}

void loop() {
  digitalWrite(pinA,HIGH);
  digitalWrite(pinB,LOW);
  digitalWrite(pinC,HIGH);
  digitalWrite(pinD,HIGH);
  digitalWrite(pinE,HIGH);
  digitalWrite(pinF,LOW);
  digitalWrite(pinG,HIGH);
  digitalWrite(pinH,LOW);
  delay(15);
  digitalWrite(pinA,HIGH);
  digitalWrite(pinB,HIGH);
  digitalWrite(pinC,LOW);
  digitalWrite(pinD,HIGH);
  digitalWrite(pinE,LOW);
  digitalWrite(pinF,HIGH);
  digitalWrite(pinG,HIGH);
  digitalWrite(pinH,LOW);
  delay(15);
}
