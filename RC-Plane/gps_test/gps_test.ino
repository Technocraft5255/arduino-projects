#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// RX, TX
SoftwareSerial mySerial(2, 3);

// Création GPS
Adafruit_GPS GPS(&mySerial);

unsigned long timer = millis();

void setup()
{
  Serial.begin(115200);

  // Démarrage GPS
  GPS.begin(9600);

  // Choix des phrases NMEA à recevoir
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  // Fréquence de mise à jour (1 Hz)
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  delay(1000);

  Serial.println(F("GPS NEO-6M + Adafruit GPS"));
}

void loop()
{
  // Lecture continue
  char c = GPS.read();

  // Affichage brut NMEA (optionnel)
  if (c)
  {
    // Serial.print(c);
  }

  // Nouvelle donnée reçue ?
  if (GPS.newNMEAreceived())
  {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  // Affichage toutes les secondes
  if (millis() - timer > 1000)
  {
    timer = millis();

    Serial.println(F("========== GPS =========="));

    // Heure
    Serial.print(F("Heure UTC : "));
    Serial.print(GPS.hour);
    Serial.print(F(":"));
    Serial.print(GPS.minute);
    Serial.print(F(":"));
    Serial.println(GPS.seconds);

    // Date
    Serial.print(F("Date : "));
    Serial.print(GPS.day);
    Serial.print(F("/"));
    Serial.print(GPS.month);
    Serial.print(F("/20"));
    Serial.println(GPS.year);

    // Fix GPS
    Serial.print(F("Fix : "));
    Serial.println((int)GPS.fix);

    // Qualité du signal
    Serial.print(F("Qualite fix : "));
    Serial.println((int)GPS.fixquality);

    if (GPS.fix)
    {
      // Latitude
      Serial.print(F("Latitude : "));
      Serial.println(GPS.latitudeDegrees, 6);

      // Longitude
      Serial.print(F("Longitude : "));
      Serial.println(GPS.longitudeDegrees, 6);

      // Vitesse
      Serial.print(F("Vitesse (knots) : "));
      Serial.println(GPS.speed);

      Serial.print(F("Vitesse (km/h) : "));
      Serial.println(GPS.speed * 1.852);

      // Angle direction
      Serial.print(F("Angle : "));
      Serial.println(GPS.angle);

      // Altitude
      Serial.print(F("Altitude (m) : "));
      Serial.println(GPS.altitude);

      // Satellites
      Serial.print(F("Satellites : "));
      Serial.println((int)GPS.satellites);

      // HDOP
      Serial.print(F("HDOP : "));
      Serial.println(GPS.HDOP);

      // Géolocalisation Google Maps
      Serial.print(F("Google Maps : "));
      Serial.print(F("https://maps.google.com/?q="));
      Serial.print(GPS.latitudeDegrees, 6);
      Serial.print(F(","));
      Serial.println(GPS.longitudeDegrees, 6);
    }

    Serial.println();
  }
}