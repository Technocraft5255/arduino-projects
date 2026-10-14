//www.elegoo.com
//2016.09.12

#include <IRremote.h>
int receiverpin = 12;
int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6;
unsigned long RED;
long  function = 0;
bool func_hashtag = false;
#define lamp 5
#define A 16736925

#define B 16754775

#define X 16712445

#define C 16720605

#define D 16761405

#define hashtag 16732845

IRrecv irrecv(receiverpin);
decode_results results;

void moveForward() {
  if (!func_hashtag) {
    digitalWrite(lamp, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(750);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(lamp, LOW);
  }
  else {
    function = function * 10;
    function = function + 1;
  }

}
void moveBack() {
  if (!func_hashtag) {
    digitalWrite(lamp, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(750);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(lamp, LOW);
  }
  else {
    function = function * 10;
    function = function + 2;
  }
}
void moveLeft() {
  if (!func_hashtag) {
    digitalWrite(lamp, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(285);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(lamp, LOW);
  }
  else {
    function = function * 10;
    function = function + 3;
  }
}
void moveRight() {
  if (!func_hashtag) {
    digitalWrite(lamp, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(285);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(lamp, LOW);
  }
  else {
    function = function * 10;
    function = function + 4;
  }
}

void hashTagClick() {
  if (!func_hashtag) {
    func_hashtag = true;
  }
  else if (func_hashtag) {
    func_hashtag = false;
  }
}

void move_func() {
  long num = function;
  int lenght = 1;
  while (num > 10) {
    num = num / 10;
    lenght ++;
  }
  Serial.print("           ");
  Serial.println(function);
  Serial.print("           ");
  Serial.println(lenght);

  for (int i = lenght ; i >= 0 ; i-- ){
    int _direction = (function / round(pow(10,i))) % 10;
    switch (_direction) {
      case 1: moveForward();Serial.println("avant"); break;
      case 2: moveBack();Serial.println("arrière");break;
      case 3: moveLeft();Serial.println("gauche");break;
      case 4: moveRight();Serial.println("droite");break;
    }
  }
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(receiverpin, INPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results))
  {

    RED = results.value;
    //Serial.println(RED);
    Serial.println(func_hashtag);
    irrecv.resume();
    delay(150);
    if (RED == A)
    {
      moveForward();
    }

    else if (RED == B)
    {
      moveBack();
    }

    else if (RED == C)
    {
      moveLeft();
    }

    else if (RED == D)
    {
      moveRight();
    }

    else if (RED == hashtag)
    {
      hashTagClick();
    }
    else if (RED == X)
    {
      move_func();
    }

  }
}
