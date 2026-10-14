#include <ESP8266WiFi.h>

// Remplacez ces valeurs par votre SSID et mot de passe WiFi
const char* ssid = "SagitarriusA";
const char* password = ")PNDI@So76513wG&xSLac49oTs642jATy|=7bSyoQPx48gCXIHcDpYkf9761Cm@";

// Pin pour la LED
const int ledPin = 5; // GPIO 5

WiFiServer server(80);

int brightness = 0; // Intensité de la LED en pourcentage

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, map(brightness, 0, 100, 0, 255));

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Attendre si le client n'est pas encore connecté
  while (!client.available()) {
    delay(1);
  }

  // Lire la requête HTTP
  String request = client.readStringUntil('\r');
  client.flush();

  // Extraire la valeur du pourcentage de luminosité de la requête HTTP
  if (request.indexOf("GET /?brightness=") != -1) {
    String brightnessString = request.substring(request.indexOf("GET /?brightness=") + 17);
    brightness = brightnessString.toInt();
    Serial.println(brightness);
    brightness = constrain(brightness, 0, 100); // S'assurer que la valeur est entre 0 et 100
    analogWrite(ledPin, map(brightness, 0, 100, 0, 255)); // Convertir le pourcentage en valeur PWM
  }

  // Préparer la page HTML
  String html = "<html><body>";
  html += "<meta charset=\"utf-8\">";
  html += "<style>body{font-family: Segoe UI;display:flex;flex-direction:column;padding:15px 75px 0px 75px;} h1,p{display: flex;justify-content: center;} input{margin: 0px 400px 0px 400px;}</style>";
  html += "<h1>ESP8266 Web Server - Contrôle de luminosité LED</h1>";
  html += "<p id=\"display_value\">Intensité de la LED: " + String(brightness) + "%</p>";
  html += "<input type=\"range\" min=\"0\" max=\"100\" value=\"" + String(brightness) + "\" onchange=\"updateBrightness(this.value)\">";
  html += "<script>function updateBrightness(value) { var xhr = new XMLHttpRequest(); xhr.open('GET', '/?brightness=' + value, true); xhr.send();document.getElementById(\"display_value\").innerHTML = value; }</script>";
  html += "</body></html>";

  // Envoyer la réponse HTTP
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);

  delay(10);
}
