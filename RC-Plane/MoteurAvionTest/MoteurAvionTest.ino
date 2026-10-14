#include <Servo.h>

Servo esc;   // Création de l'objet permettant le contrôle de l'ESC

int val = 0; // 

void setup() {
   esc.attach(9); // On attache l'ESC au port numérique 9 (port PWM obligatoire)
   delay(15);
   Serial.begin(9600);
  pinMode(A0,INPUT);

   // Initialisation de l'ESC
   //  (certains ESC ont besoin d'une "procédure d'initialisation"
   //   pour devenir opérationnels - voir notice)
   esc.write(0);
   delay(1000);
   esc.write(180);
   delay(1000);
   esc.write(0);

   // Quelques informations pour l'utilisateur
   Serial.println("Saisir un nombre entre 0 et 179");
   Serial.println("(0 = arret - 179 = vitesse maxi");
   Serial.println(" demarrage a partir de 20)");
  esc.write(30);
  Serial.println("30");
  delay(2000);
   }

void loop() {
  int val = map(analogRead(A0),0,1023,0,180);
  Serial.println(val);
  esc.write(val);
  delay(200);
  }