#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "VoitureWifi";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Voiture WiFi</title>
  <style>
    body {
      background: #111;
      color: white;
      text-align: center;
      font-family: sans-serif;
    }
    .btn {
      width: 100px;
      height: 100px;
      margin: 10px;
      font-size: 20px;
      border-radius: 15px;
      border: none;
      color: white;
      background-color: #2196F3;
      box-shadow: 0 4px #0b78d1;
    }
    .btn:active {
      box-shadow: 0 2px #0b78d1;
      transform: translateY(2px);
    }
    .grid {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 10px;
      justify-items: center;
      margin-top: 50px;
    }
  </style>
</head>
<body>
  <h1>Contrôle Voiture</h1>
  <div class="grid">
    <div></div>
    <button class="btn" onclick="send('F')">↑</button>
    <div></div>
    <button class="btn" onclick="send('L')">←</button>
    <button class="btn" onclick="send('S')">■</button>
    <button class="btn" onclick="send('R')">→</button>
    <div></div>
    <button class="btn" onclick="send('B')">↓</button>
    <div></div>
  </div>

  <script>
    function send(cmd) {
      fetch("/cmd?val=" + cmd);
    }
  </script>
</body>
</html>
  )rawliteral");
}

void handleCmd() {
  if (server.hasArg("val")) {
    String cmd = server.arg("val");
    Serial.print(cmd); // Envoi sur TX vers Arduino UNO
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/cmd", handleCmd);
  server.begin();
}

void loop() {
  server.handleClient();
}
