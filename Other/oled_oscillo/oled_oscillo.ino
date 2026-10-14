#include <Adafruit_SSD1306.h>

#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
String values = "";


int get_val(int val){
  return values.substring(val-1*3,(val*3)+2).toInt();
}

void set_val(int val){
  if (true/*val >= 10*/){
    String str_val = String(val);
    int length = values.length();
    values[length] = str_val[0];
    values[length+1] = str_val[1];
    values[length+2] = " ";
  }
}


void draw_rect(int x,int y, int width, int height){
  for(byte numeroLigne=0 ; numeroLigne < width; numeroLigne++) {
    for(byte numeroColonne=0 ; numeroColonne < height ; numeroColonne++) {
      oled.drawPixel(numeroColonne+x, numeroLigne+y, WHITE);          // On demande l'allumage de chaque pixel, un à un, avec la commande : drawPixel(posX,posY,couleur);
    }
  }
}
// ========================
// Initialisation programme
// ========================
void setup() {
  pinMode(A0,INPUT);
  // Initialisation de la liaison série, côté PC (pour y faire afficher des infos, via le moniteur série de l'IDE Arduino)
  Serial.begin(9600);

  // Initialisation de l'écran OLED
  oled.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED);

  oled.clearDisplay();                                            // Effaçage de l'intégralité du buffer

  draw_rect(10,10,40,40);
  
  Serial.println(F("Chargement terminé. Affichage !")); 
  oled.display();
  delay(1000);
  oled.clearDisplay(); 
  oled.display();
}

void loop() {
  int value = analogRead(A0);
  set_val(value);
  Serial.println(values);
  // int val_lenght = get_lenght(values);
  // values[val_lenght+1] = analogRead(A0)
  // oled.clearDisplay();
  // for(int i=0;i<get_lenght(values);i++){
  //   int y_place = map(values[i],0,1023,0,64);
  //   oled.drawPixel(10,y_place,WHITE);
  // }
  // oled.display();
  // delay(10);
}