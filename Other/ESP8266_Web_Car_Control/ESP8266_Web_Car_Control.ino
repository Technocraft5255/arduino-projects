#include <ESP8266WiFi.h>

// Remplacez ces valeurs par votre SSID et mot de passe WiFi
const char* ssid = "SagitarriusA";
const char* password = ")PNDI@So76513wG&xSLac49oTs642jATy|=7bSyoQPx48gCXIHcDpYkf9761Cm@";

// Pins pour les LEDs
const int ledPin1 = 5; // GPIO 5
const int ledPin2 = 4; // GPIO 4
const int ledPin3 = 0; 
const int ledPin4 = 2; 

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin2, LOW);

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

  // Vérifier si la requête contient /LED1ON
  if (request.indexOf("/FORWARDON") != -1) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin3,HIGH);
  }
  // Vérifier si la requête contient /LED1OFF
  if (request.indexOf("/FORWARDOFF") != -1) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin3, LOW);
  }
  // Vérifier si la requête contient /LED2ON
  if (request.indexOf("/BACKON") != -1) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin4, HIGH);
  }
  // Vérifier si la requête contient /LED2OFF
  if (request.indexOf("/BACKOFF") != -1) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin4, LOW);
  }
  if (request.indexOf("/RIGHTON") != -1) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin4, HIGH);
  }
  // Vérifier si la requête contient /LED2OFF
  if (request.indexOf("/RIGHTOFF") != -1) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin4, LOW);
  }
  if (request.indexOf("/LEFTON") != -1) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  }
  // Vérifier si la requête contient /LED2OFF
  if (request.indexOf("/LEFTOFF") != -1) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Préparer la page HTML
  String html = "<!DOCTYPE html>";
  html += "<html><head><meta charset='utf-8'><title>Car controller</title><link rel='stylesheet' href='http://technocraft-dev.000webhostapp.com/extern_style/car_web_style.css'></head><body>";
  html += "<h1>ESP8266 Web Server</h1>";
  html += "<button id='forwardBouton'>↑</button>";
  html += "<button id='backBouton'>↓</button>";
  html += "<button id='rightBouton'>→</button>";
  html += "<button id='leftBouton'>←</button>";

  html += "<script>function forwardOn() {var xhr = new XMLHttpRequest();xhr.open('GET', '/FORWARDON', true);xhr.send(); }function forwardOff() {var xhr = new XMLHttpRequest();xhr.open('GET', '/FORWARDOFF', true);xhr.send();}var forwardbouton = document.getElementById('forwardBouton');forwardbouton.addEventListener('mousedown', function() {forwardOn();});forwardbouton.addEventListener('mouseup', function() {forwardOff();});</script>";
  html += "<script>function backOn() {console.log('Btn reculer press');var xhr = new XMLHttpRequest();xhr.open('GET', '/BACKON', true);xhr.send(); }function backOff() {var xhr = new XMLHttpRequest();xhr.open('GET', '/BACKOFF', true);xhr.send();}var backbouton = document.getElementById('backBouton');backbouton.addEventListener('mousedown', function() {backOn();});backbouton.addEventListener('mouseup', function() {backOff();});</script>";
  html += "<script>function rightOn() {var xhr = new XMLHttpRequest();xhr.open('GET', '/RIGHTON', true);xhr.send(); }function rightOff() {var xhr = new XMLHttpRequest();xhr.open('GET', '/RIGHTOFF', true);xhr.send();}var rightbouton = document.getElementById('rightBouton');rightbouton.addEventListener('mousedown', function() {rightOn();});rightbouton.addEventListener('mouseup', function() {rightOff();});</script>";
  html += "<script>function leftOn() {var xhr = new XMLHttpRequest();xhr.open('GET', '/LEFTON', true);xhr.send(); }function leftOff() {var xhr = new XMLHttpRequest();xhr.open('GET', '/LEFTOFF', true);xhr.send();}var leftbouton = document.getElementById('leftBouton');leftbouton.addEventListener('mousedown', function() {leftOn();});leftbouton.addEventListener('mouseup', function() {leftOff();});</script>";
  
  
  // html += "<h2>Avancer</h2>"
  // html += "<a href=\"/FORWARDON\"><button>Allumer</button></a>";
  // html += "<a href=\"/FORWARDOFF\"><button>Éteindre</button></a>";
  // html += "<h2>Reculer</h2>";
  // html += "<a href=\"/BACKON\"><button>Allumer</button></a>";
  // html += "<a href=\"/BACKOFF\"><button>Éteindre</button></a>";
  // html += "<h2>Tourn. Droite</h2>";
  // html += "<a href=\"/RIGHTON\"><button>Allumer</button></a>";
  // html += "<a href=\"/RIGHTOFF\"><button>Éteindre</button></a>";
  // html += "<h2>Tourn. Gauche</h2>";
  // html += "<a href=\"/LEFTON\"><button>Allumer</button></a>";
  // html += "<a href=\"/LEFTOFF\"><button>Éteindre</button></a>";
  html += "</body></html>";

  // Envoyer la réponse HTTP
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);

  delay(10);
}