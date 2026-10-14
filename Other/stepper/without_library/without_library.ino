
// écrit par THONAIN 01/2021
// MOTEUR PAS à PAS 28BYJ-48 avec module ULN2003 + ARDUINO UNO
int in1 = 8; // broche 8 reliée à IN1
int in2 = 9; // broche 9 reliée à IN2
int in3 = 10; // broche 10 reliée à IN3
int in4 = 11; // broche 11 reliée à IN4
int numero_de_pas = 0;

void setup() {
  // broches 8 à 11 de l'arduino définies en output
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // SENS HORAIRE (2048 pas = 1 tour complet de l'axe extérieur du moteur)

  for (int cycle1 = 0; cycle1 < 2048; cycle1++)
  {
    switch (numero_de_pas) {
      case 0:
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
      case 1:
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
      case 2:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        break;
      case 3:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }
    numero_de_pas++;
    if (numero_de_pas > 3) {
      numero_de_pas = 0;
    }

    Serial.println(numero_de_pas);
    delay(2);
  }

  // SENS ANTI-HORAIRE (2048 pas = 1 tour complet de l'axe extérieur du moteur)
  for (int cycle2 = 0; cycle2 < 2048; cycle2++)
  {
    switch (numero_de_pas) {
      case 0:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        break;
      case 1:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        break;
      case 2:
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
      case 3:
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
    }
    numero_de_pas++;
    if (numero_de_pas > 3) {
      numero_de_pas = 0;
    }
    delay(2);
  }
}
