

#include <Adafruit_SSD1306.h>

#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

Adafruit_SSD1306 oled(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);


// ========================
// Initialisation programme
// ========================
void setup() {

  // Initialisation de la liaison série, côté PC (pour y faire afficher des infos, via le moniteur série de l'IDE Arduino)
  Serial.begin(9600);
  Serial.println(F("Allumage de l'intégralité des pixels (OLED 128x64, chipset SSD1306)"));
  Serial.println(F("==================================================================="));
  Serial.println();


  // Initialisation de l'écran OLED
  if(!oled.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)) {
    Serial.println(F("Erreur de communication avec le chipset SSD1306… arrêt du programme."));
    while(1);                                             // Arrêt du programme (boucle infinie)
  }
  else {
    Serial.println(F("Initialisation du contrôleur SSD1306 réussi."));
  }


  // Allumage de tous les pixels de l'écran OLED
  Serial.println(F("Chargement de la mémoire tampon de l'écran OLED, avec tous les pixels à allumer…"));
  oled.clearDisplay();                                            // Effaçage de l'intégralité du buffer

  for(byte numeroLigne=0 ; numeroLigne < nombreDePixelsEnHauteur ; numeroLigne++) {
    for(byte numeroColonne=0 ; numeroColonne < nombreDePixelsEnLargeur ; numeroColonne++) {
      oled.drawPixel(numeroColonne, numeroLigne, WHITE);          // On demande l'allumage de chaque pixel, un à un, avec la commande : drawPixel(posX,posY,couleur);
    }
  }
  
  // Nota 1 : le "WHITE" ne veut pas dire "blanc" ici, mais la couleur de votre écran OLED monochrome (qui peut être blanc, bleu, jaune, bleu/jaune, …)
  // Nota 2 : on aurait pu utiliser la fonction "fillScreen(couleur)" pour remplir/effacer l'écran, avec la couleur souhaitée ; mais ici, j'ai voulu vous montrer
  //          comment se servir de la fonction "drawPixel(posX,posY,couleur)"

  
  Serial.println(F("Chargement terminé. Affichage !")); 
  oled.display();                                                 // Transfert du buffer à l'écran
  
  Serial.println(F("Fin."));
  
}


// =================
// Boucle principale
// =================
void loop() {
  // Aucun code dans cette partie, car tout se passe dans la fonction setup !
  
}
