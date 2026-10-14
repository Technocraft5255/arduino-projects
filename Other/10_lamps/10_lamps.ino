#define L1 2
#define L2 3
#define L3 4
#define L4 5
#define L5 6
#define L6 7
#define L7 8
#define L8 9
#define L9 10
#define L10 11


void setup() {
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
  pinMode(L5,OUTPUT);
  pinMode(L6,OUTPUT);
  pinMode(L7,OUTPUT);
  pinMode(L8,OUTPUT);
  pinMode(L9,OUTPUT);
  pinMode(L10,OUTPUT);
  
}

void loop() {
  for (int i=2;i<12;i++) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW);
  }
  for (int i=11;i>1;i--) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW);
  }
}
