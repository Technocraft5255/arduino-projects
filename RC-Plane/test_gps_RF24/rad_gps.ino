#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
RF24 radio(4, 5);
const uint64_t addresse = 0x1111111111;
const int taille = 32;
char message[taille + 1];
char gps_vals;
char char_msg;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresse);

  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);

}


void loop() {
  clearGPS();
  while (!GPS.newNMEAreceived()) {
    gps_vals = GPS.read();
  }

  GPS.parse(GPS.lastNMEA());
  if (GPS.fix){
    snprintf(message, sizeof(message), "%.6f,%.6f,%.5f", GPS.latitudeDegrees, GPS.longitudeDegrees, GPS.altitude);
    /*
    GPS.latitude,
    GPS.lat,
    GPS.longitude,
    GPS.lon,
    GPS.latitudeDegrees,
    GPS.longitudeDegrees,
    GPS.speed,
    GPS.angle,
    GPS.altitude,
    GPS.satellites,
    GPS.fixquality,
    GPS.fix,
    GPS.day,
    GPS.month,
    GPS.year,
    GPS.hour,
    GPS.minute,
    GPS.seconds,
    GPS.milliseconds
    */
  }
  else{
    strcpy(message, "GPS not readable");
  }
  Serial.print("Message sent : "); // pour débogage
  Serial.println(message);

  radio.write( message, taille);
}


void clearGPS() {
  while (!GPS.newNMEAreceived()) {
    gps_vals = GPS.read();
  }
  GPS.parse(GPS.lastNMEA());

  while (!GPS.newNMEAreceived()) {
    gps_vals = GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  while (!GPS.newNMEAreceived()) {
    gps_vals = GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  while (!GPS.newNMEAreceived()) {
    gps_vals = GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
}