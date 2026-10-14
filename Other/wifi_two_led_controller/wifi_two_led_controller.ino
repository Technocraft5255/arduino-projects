#include <ESP8266WiFi.h>

// Remplacez ces valeurs par votre SSID et mot de passe WiFi
const char* ssid = "SagitarriusA";
const char* password = ")PNDI@So76513wG&xSLac49oTs642jATy|=7bSyoQPx48gCXIHcDpYkf9761Cm@";

// Pins pour les LEDs
const int ledPin1 = 5; // GPIO 5
const int ledPin2 = 4; // GPIO 4

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  digitalWrite(ledPin1, LOW);
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
  if (request.indexOf("/LED1ON") != -1) {
    digitalWrite(ledPin1, HIGH);
  }

  // Vérifier si la requête contient /LED1OFF
  if (request.indexOf("/LED1OFF") != -1) {
    digitalWrite(ledPin1, LOW);
  }

  // Vérifier si la requête contient /LED2ON
  if (request.indexOf("/LED2ON") != -1) {
    digitalWrite(ledPin2, HIGH);
  }

  // Vérifier si la requête contient /LED2OFF
  if (request.indexOf("/LED2OFF") != -1) {
    digitalWrite(ledPin2, LOW);
  }

  // Préparer la page HTML
  String html = "<html><body>";
  html += "<h1>ESP8266 Web Server</h1>";
  html += "<h2>LED 1</h2>";
  html += "<a href=\"/LED1ON\"><button>Allumer</button></a>";
  html += "<a href=\"/LED1OFF\"><button>Éteindre</button></a>";
  html += "<h2>LED 2</h2>";
  html += "<a href=\"/LED2ON\"><button>Allumer</button></a>";
  html += "<a href=\"/LED2OFF\"><button>Éteindre</button></a>";
  html += "</body></html>";

  // Envoyer la réponse HTTP
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);

  delay(10);
}
