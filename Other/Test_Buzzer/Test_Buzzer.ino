int buzzer = 2; // Broche du buzzer

void setup() {
  pinMode(buzzer, OUTPUT);

  // Bip de connexion (2 bips longs)
  connexion();

  delay(5000); // Pause avant le bip de déconnexion
  deconnexion();
}
void loop(){
   
}

void connexion() {
  for (int i = 0; i < 2; i++) {     
    tone(buzzer, 588);  // fréquence du son (1000 Hz)
    delay(75);          // durée du bip (long)
    noTone(buzzer);
    delay(75);          // pause entre les bips
  }
}

void deconnexion() {
  for (int i = 0; i < 3; i++) {
    tone(buzzer, 700);   // fréquence du son (plus grave)
    delay(50);          // durée du bip (court)
    noTone(buzzer);
    delay(75);          // pause entre les bips
  }
}
