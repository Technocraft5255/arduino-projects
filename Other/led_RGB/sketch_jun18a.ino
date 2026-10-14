#define BLUE 6
#define GREEN 5
#define RED 3
String color;
void setup(){
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  Serial.begin(9600);
}

void loop(){
  color = Serial.readString();
  if (color != 0){
    String test = color;
    String R = String(test[1]) + String(test[2]) + String(test[3]);
    while (true){
      Serial.print(R);
      Serial.print(" ; ");
      Serial.print(test[5]);
      Serial.print(test[6]);
      Serial.print(test[7]);
      Serial.print(" ; ");
      Serial.print(test[9]);
      Serial.print(test[10]);
      Serial.print(test[11]);
      Serial.print(" ; ");
      Serial.println(test);}
    analogWrite(RED,color[0]);
    analogWrite(GREEN,color[1]);
    analogWrite(BLUE,color[2]);
  }
}
