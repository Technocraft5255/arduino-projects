#define button 2
int i;
void setup() {
  Serial.begin(9600);
  pinMode(button,INPUT_PULLUP);
}

void loop() {
  if (digitalRead(button)==LOW){
    Serial.println(1);
    while (digitalRead(button)==LOW);
  }
  else{
    Serial.println(0);
    }

}
