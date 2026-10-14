int PinDeMesure=A0;
int adjustPin = A1;
//conteneur pour stocker la mesure
int tension=0;
// délai entre deux mesures
int periodeDeMesure=20;

void setup(){ // Initialisation du programme
    // établir la connection série à 19200 baud
    Serial.begin(19200);
    // définir le PinDeMesure comme une entrée
    pinMode(PinDeMesure, INPUT);
    //pinMode(adjustPin, INPUT);
    //pinMode(2,OUTPUT);
    //tone(2,1,100);
}

void loop() { //boucle principale
    tension = analogRead(PinDeMesure); // Lit la tension du pin DeMesure et stocke le résultat dans la variable tension
    Serial.println(tension); // communique la valeur de la tension au port série
    delay(periodeDeMesure); //attendre jusqu'à la prochaine mesure
}