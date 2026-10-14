/*
 Osiloscope
 */

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  Serial.print("0,");
  Serial.print("0,");
  Serial.print("0,");
}

void loop() {
  Serial.print("0,");
  Serial.print("1023,");
  Serial.println(analogRead(A0));
  delay(2);
}
