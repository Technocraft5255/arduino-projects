#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "VoitureRadar";
const char* password = "12345678";

ESP8266WebServer server(80);
String radarData = "";

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>Radar Voiture</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      background: #121212;
      color: #fff;
      text-align: center;
      font-family: sans-serif;
    }
    canvas {
      background: #000;
      margin-top: 20px;
      border-radius: 15%;
    }
    .controls {
      margin-top: 30px;
    }
    button {
      width: 80px;
      height: 80px;
      margin: 5px;
      font-size: 20px;
      border: none;
      border-radius: 10px;
      background-color: #2196F3;
      color: white;
      box-shadow: 0 4px #0b78d1;
    }
    button:active {
      transform: translateY(2px);
    }
  </style>
</head>
<body>
  <h1>Voiture Radar</h1>
  <canvas id="radar" width="300" height="300"></canvas>

  <div class="controls">
    <div>
      <button onclick="send('F')">↑</button>
    </div>
    <div>
      <button onclick="send('L')">←</button>
      <button onclick="send('S')">■</button>
      <button onclick="send('R')">→</button>
    </div>
    <div>
      <button onclick="send('B')">↓</button>
    </div>
  </div>

  <script>
  let canvas = document.getElementById("radar");
  let ctx = canvas.getContext("2d");
  let distances = Array(37).fill(200); // 200 = max (pas détecté)
  let width = canvas.width;
  let height = canvas.height;

  function map(x, in_min, in_max, out_min, out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  function drawRadar() {
    ctx.clearRect(0, 0, width, height);
    let rectWidth = width / 37;

    for (let angle = 0; angle <= 36; angle++) {
      let dist = distances[angle];
      let gray = 255 - Math.min(255, map(dist, 0, 200, 255, 30)); // Inversé : proche = clair
      ctx.fillStyle = `rgb(${gray},${gray},${gray})`;
      ctx.fillRect(angle * rectWidth, 0, rectWidth, height);
    }
  }

  function updateRadar() {
    fetch("/radar").then(res => res.text()).then(txt => {
      let lines = txt.trim().split("\\n");
      lines.forEach(line => {
        if (line.startsWith("A")) {
          let parts = line.substring(1).split(":");
          let angle = parseInt(parts[0]);
          let dist = parseInt(parts[1]);
          if (angle >= 0 && angle <= 180) {
            distances[angle*36/180] = dist;
          }
        }
      });
      drawRadar();
    });
  }

  function send(cmd) {
    fetch("/cmd?val=" + cmd);
  }

  setInterval(updateRadar, 300);
  drawRadar();
</script>

</body>
</html>
  )rawliteral");
}

void handleCmd() {
  if (server.hasArg("val")) {
    String cmd = server.arg("val");
    Serial.print(cmd);
  }
  server.send(200, "text/plain", "OK");
}

void handleRadar() {
  server.send(200, "text/plain", radarData);
  radarData = "";  // Reset after sending
}

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/cmd", handleCmd);
  server.on("/radar", handleRadar);
  server.begin();
}

void loop() {
  server.handleClient();

  while (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    radarData += line + "\n";
  }
}
