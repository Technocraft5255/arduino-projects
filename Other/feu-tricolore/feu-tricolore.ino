
#define GREEN_PIN 11
#define RED_PIN 10

void setup() {
  pinMode(GREEN_PIN,OUTPUT);
  pinMode(RED_PIN,OUTPUT);
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
}

void loop() {
  analogWrite(GREEN_PIN,0);
  analogWrite(RED_PIN,255);
  delay(45000); 
  analogWrite(GREEN_PIN,255);
  analogWrite(RED_PIN,0);
  delay(30000);
  analogWrite(GREEN_PIN,75);
  analogWrite(RED_PIN,255);
  delay(3000);
}
