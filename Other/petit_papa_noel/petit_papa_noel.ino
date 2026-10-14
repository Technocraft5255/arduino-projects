/**********************************************************
 
    5 mélodies de Noël jouées par l'Arduino
    
    https://electroniqueamateur.blogspot.com/2018/12/arduino-chante-noel.html
************************************************************/

#define sortie 8   // sortie du son à la broche 8 de l'Arduino
void setup() {
  Serial.begin(9600);
}

// fréquence associée à chaque note
// do, do#, ré, ré#, mi, fa, fa#, sol, sol#, la, la#, si
const float note[12] = {65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98.00, 103.83, 110.00, 116.54, 123.47
                       };

// chaque note de la mélodie comporte 3 paramètres:
// note (de 0 à 11:  0 pour do, 1 pour do#, etc)
// octave (1 à 3)
// durée (1 pour croche, 2 pour noire, 4 pour ronde)

void jingleBells(void) {

  // Vive le vent

  const int nombreDeNotes = 49;
  const int tempo = 150; // plus c'est petit, plus c'est rapide
  const int melodie[][3] = { {4, 2, 2}, {4, 2, 2}, {4, 2, 4}, {4, 2, 2}, {4, 2, 2}, {4, 2, 4},
    {4, 2, 2}, {7, 2, 2},  {0, 2, 3},  {2, 2, 1},  {4, 2, 8},
    {5, 2, 2}, {5, 2, 2}, {5, 2, 3}, {5, 2, 1}, {5, 2, 2}, {4, 2, 2}, {4, 2, 3},
    {4, 2, 1}, {4, 2, 2}, {2, 2, 2}, {2, 2, 2}, {4, 2, 2}, {2, 2, 4}, {7, 2, 4},
    {4, 2, 2}, {4, 2, 2}, {4, 2, 4}, {4, 2, 2}, {4, 2, 2}, {4, 2, 4},
    {4, 2, 2}, {7, 2, 2},  {0, 2, 3},  {2, 2, 1},  {4, 2, 8},
    {5, 2, 2}, {5, 2, 2}, {5, 2, 3}, {5, 2, 1}, {5, 2, 2}, {4, 2, 2}, {4, 2, 3},
    {4, 2, 1}, {7, 2, 2}, {7, 2, 2}, {5, 2, 2}, {2, 2, 2}, {0, 2, 8}
  };

  int frequence;

  for ( int i = 0; i < nombreDeNotes ; i++ ) {
    frequence = round(note[melodie[i][0]] * 2 * (melodie[i][1] - 1));

    tone(sortie, frequence);
    delay(tempo * melodie[i][2] - 50);
    noTone(sortie);
    delay(50);

  }


}


void weWishYou (void) {

  // We wish you a merry Christmas

  const int nombreDeNotes = 29;
  const int tempo = 150    ; // plus c'est petit, plus c'est rapide
  const int melodie[][3] = { {7, 2, 2}, {0, 3, 2}, {0, 3, 1}, {2, 3, 1}, {0, 3, 1}, {11, 2, 1},
    {9, 2, 2}, {9, 2, 2}, {9, 2, 2}, {2, 3, 2}, {2, 3, 1}, {4, 3, 1}, {2, 3, 1}, {0, 3, 1},
    {11, 2, 2}, {7, 2, 2}, {7, 2, 2}, {4, 3, 2}, {4, 3, 1}, {5, 3, 1}, {4, 3, 1}, {2, 3, 1},
    {0, 3, 2}, {9, 2, 2}, {7, 2, 2}, {9, 2, 2}, {2, 3, 2}, {11, 2, 2}, {0, 3, 4}
  };

  int frequence;

  for ( int i = 0; i < nombreDeNotes ; i++ ) {
    frequence = round(note[melodie[i][0]] * 2 * (melodie[i][1] - 1));

    tone(sortie, frequence);
    delay(tempo * melodie[i][2] - 50);
    noTone(sortie);
    delay(50);

  }

}

void petitRenne (void) {

  // le petit renne au  nez rouge

  const int nombreDeNotes = 56;
  const int tempo = 200    ; // plus c'est petit, plus c'est rapide
  const int melodie[][3] = { {7, 2, 2}, {9, 2, 1}, {7, 2, 1}, {4, 2, 2}, {0, 3, 2}, {9, 2, 2}, {7, 2, 6},
    {7, 2, 1}, {9, 2, 1}, {7, 2, 1}, {9, 2, 1}, {7, 2, 2}, {0, 3, 2}, {11, 2, 6},
    {5, 2, 2}, {7, 2, 1}, {5, 2, 1}, {2, 2, 2}, {11, 2, 2}, {9, 2, 2}, {7, 2, 6},
    {7, 2, 1}, {9, 2, 1}, {7, 2, 1}, {9, 2, 1}, {7, 2, 2}, {9, 2, 2}, {4, 2, 6},
    {7, 2, 2}, {9, 2, 1}, {7, 2, 1}, {4, 2, 2}, {0, 3, 2}, {9, 2, 2}, {7, 2, 6},
    {7, 2, 1}, {9, 2, 1}, {7, 2, 1}, {9, 2, 1}, {7, 2, 2}, {0, 3, 2}, {11, 2, 6},
    {5, 2, 2}, {7, 2, 1}, {5, 2, 1}, {2, 2, 2}, {11, 2, 2}, {9, 2, 2}, {7, 2, 6},
    {7, 2, 1}, {9, 2, 1}, {7, 2, 1}, {9, 2, 1}, {7, 2, 2}, {2, 3, 2}, {0, 3, 6},
  };

  int frequence;

  for ( int i = 0; i < nombreDeNotes ; i++ ) {
    frequence = round(note[melodie[i][0]] * 2 * (melodie[i][1] - 1));

    tone(sortie, frequence);
    delay(tempo * melodie[i][2] - 50);
    noTone(sortie);
    delay(50);

  }

}

void petitPapa(void) {
  // petit papa noël
  const int nombreDeNotes = 58;
  const int tempo = 250    ; // plus c'est petit, plus c'est rapide
  const int melodie[][3] = { {7, 2, 2}, {0, 3, 2}, {0, 3, 2}, {0, 3, 2}, {2, 3, 2}, {0, 3, 6},
    {0, 3, 1}, {2, 3, 1}, {4, 3, 2}, {4, 3, 2}, {4, 3, 2}, {5, 3, 2}, {4, 3, 6},
    {2, 3, 2}, {0, 3, 3}, {0, 3, 1}, {0, 3, 1}, {0, 3, 1}, {11, 2, 1}, {9, 2, 1}, {7, 2, 6},
    {7, 2, 1}, {7, 2, 1}, {0, 3, 4}, {0, 3, 1}, {0, 3, 1}, {11, 2, 1}, {0, 3, 1}, {2, 3, 6},
    {7, 2, 2}, {0, 3, 2}, {0, 3, 2}, {0, 3, 2}, {2, 3, 2}, {0, 3, 6},
    {0, 3, 1}, {2, 3, 1}, {4, 3, 2}, {4, 3, 2}, {4, 3, 2}, {5, 3, 2}, {4, 3, 6},
    {2, 3, 2}, {0, 3, 3}, {0, 3, 1}, {0, 3, 1}, {0, 3, 1}, {11, 2, 1}, {9, 2, 1}, {7, 2, 6},
    {7, 2, 1}, {7, 2, 1}, {0, 3, 4}, {0, 3, 1}, {0, 3, 1}, {2, 3, 1}, {2, 3, 1}, {0, 3, 6},
  };


  int frequence;

  for ( int i = 0; i < nombreDeNotes ; i++ ) {
    frequence = round(note[melodie[i][0]] * 2 * (melodie[i][1] - 1));

    Serial.println(frequence);
    tone(sortie, frequence);
    delay(tempo * melodie[i][2] - 50);
    noTone(sortie);
    delay(50);

  }
}


void auRoyaume (void) {

  //Au royaume du bonhomme hiver (Winter Wonderland)

  const int nombreDeNotes = 33;
  const int tempo = 150    ; // plus c'est petit, plus c'est rapide
  const int melodie[][3] = { {7, 2, 2}, {7, 2, 1}, {7, 2, 9}, {7, 2, 2}, {7, 2, 1}, {4, 2, 2}, {7, 2, 6},
    {7, 2, 2}, {7, 2, 1}, {7, 2, 9}, {7, 2, 2}, {7, 2, 1}, {5, 2, 2}, {7, 2, 6},
    {7, 2, 1}, {11, 2, 2}, {11, 2, 1}, {11, 2, 2}, {9, 2, 6},
    {9, 2, 1}, {7, 2, 2}, {7, 2, 1}, {7, 2, 2}, {5, 2, 6},
    {4, 2, 2}, {4, 2, 1}, {4, 2, 2}, {4, 2, 1}, {2, 2, 2}, {2, 2, 1}, {2, 2, 1}, {2, 2, 1}, {0, 2, 9},
  };

  int frequence;

  for ( int i = 0; i < nombreDeNotes ; i++ ) {
    frequence = round(note[melodie[i][0]] * 2 * (melodie[i][1] - 1));

    tone(sortie, frequence);
    delay(tempo * melodie[i][2] - 50);
    noTone(sortie);
    delay(50);

  }
}

  void loop() {
/*
    jingleBells();
    delay (2000);
    weWishYou ();
    delay (2000);
    petitRenne();
    delay (2000);*/
    petitPapa();
    delay (2000);
/*    auRoyaume();
    delay (2000);*/

  }
