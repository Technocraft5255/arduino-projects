#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  esp.begin(115200);

  delay(2000);

  sendCommand("AT", 2000);
  sendCommand("AT+CWMODE=1", 2000);
  sendCommand("AT+CWJAP=\"TON_SSID\",\"TON_MDP\"", 5000);

  // Connexion au serveur
  sendCommand("AT+CIPSTART=\"TCP\",\"192.168.1.26\",8080", 3000);

  // Requête HTTP
  String request = "GET /?wind=34.0&rain=250.0 HTTP/1.1\r\n";
  request += "Host: 192.168.1.26\r\n";
  request += "Connection: close\r\n\r\n";

  // Longueur de la requête
  esp.print("AT+CIPSEND=");
  esp.println(request.length());

  delay(1000);

  esp.print(request);

  delay(2000);

  sendCommand("AT+CIPCLOSE", 2000);
}

void loop() {}

void sendCommand(String cmd, int timeout) {
  esp.println(cmd);
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (esp.available()) {
      Serial.write(esp.read());
    }
  }
}