void setup() {
  Serial.begin(9600);
}

char rx_byte = 0;

void loop() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
    Serial.println(rx_byte);
  } // end: if (Serial.available() > 0)
}
