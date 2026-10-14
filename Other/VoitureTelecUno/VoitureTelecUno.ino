// === Arduino UNO Code ===
// Communication via Serial (USB TX/RX)
// Contrôle moteurs + radar + réception commandes depuis ESP8266

#include <Servo.h>

// Pins moteurs
const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;

// Capteur ultrason
const int trigPin = 6;
const int echoPin = 7;

// Servo
Servo radarServo;
const int servoPin = 5;

// Radar
const int radarStep = 5;
const int radarMin = 60;
const int radarMax = 120;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  radarServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  // Lire commande du WiFi (ESP)
  if (Serial.available()) {
    char c = Serial.read();
    handleCommand(c);
  }

  // Balayage radar
  for (int angle = radarMin; angle <= radarMax; angle += radarStep) {
    radarServo.write(angle);
    delay(60);
    int dist = measureDistance();
    Serial.print("A");
    Serial.print(angle);
    Serial.print(":");
    Serial.println(dist);
    if (dist < 8) stopMotors();
  }
  for (int angle = radarMax; angle >= radarMin; angle -= radarStep) {
    radarServo.write(angle);
    delay(60);
    int dist = measureDistance();
    Serial.print("A");
    Serial.print(angle);
    Serial.print(":");
    Serial.println(dist);
    if (dist < 8) stopMotors();
  }
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // distance en cm
}

// Commandes moteur
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'F': forward(); break;
    case 'B': backward(); break;
    case 'L': left(); break;
    case 'R': right(); break;
    case 'S': stopMotors(); break;
  }
}
