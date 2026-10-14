void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
}
bool pin2 = LOW;
bool pin3 = LOW;
bool pin4 = LOW;
bool pin5 = LOW;
bool pin6 = LOW;
bool pin7 = LOW;
bool pin8 = LOW;
bool pin9 = LOW;
bool pin10 = LOW;
bool pin11 = LOW;
bool pin12 = LOW;

void loop() {
  int num = Serial.parseInt();
  if (num != 0){
    Serial.println(num);
    }
  switch (num){
    case 2:if (pin2){digitalWrite(2,LOW);pin2=LOW;}else{digitalWrite(2,HIGH);pin2=HIGH;}break;
    case 3:if (pin3){digitalWrite(3,LOW);pin3=LOW;}else{digitalWrite(3,HIGH);pin3=HIGH;}break;
    case 4:if (pin4){digitalWrite(4,LOW);pin4=LOW;}else{digitalWrite(4,HIGH);pin4=HIGH;}break;
    case 5:if (pin5){digitalWrite(5,LOW);pin5=LOW;}else{digitalWrite(5,HIGH);pin5=HIGH;}break;
    case 6:if (pin6){digitalWrite(6,LOW);pin6=LOW;}else{digitalWrite(6,HIGH);pin6=HIGH;}break;
    case 7:if (pin7){digitalWrite(7,LOW);pin7=LOW;}else{digitalWrite(7,HIGH);pin7=HIGH;}break;
    case 8:if (pin8){digitalWrite(8,LOW);pin8=LOW;}else{digitalWrite(8,HIGH);pin8=HIGH;}break;
    case 9:if (pin9){digitalWrite(9,LOW);pin9=LOW;}else{digitalWrite(9,HIGH);pin9=HIGH;}break;
    case 10:if (pin10){digitalWrite(10,LOW);pin10=LOW;}else{digitalWrite(10,HIGH);pin10=HIGH;}break;
    case 11:if (pin11){digitalWrite(11,LOW);pin11=LOW;}else{digitalWrite(11,HIGH);pin11=HIGH;}break;
    case 12:if (pin12){digitalWrite(12,LOW);pin12=LOW;}else{digitalWrite(12,HIGH);pin12=HIGH;}break;
  }
}
