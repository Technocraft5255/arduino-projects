#include <Servo.h>

#define trigPin 6
#define echoPin 7
#define servoPin 5

#define in1 8
#define in2 9
#define in3 10
#define in4 11

Servo scanner;

int angle = 0;
int step = 5;
unsigned long lastRadarSend = 0;

void setup() {
  Serial.begin(9600);
  scanner.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  stopMotors();
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    switch (cmd) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopMotors(); break;
    }
  }
  if (millis() - lastRadarSend >= 30) {
    scanner.write(angle);
    delay(5);  // Temps pour le servo

    int dist = readDistanceCM();
    Serial.print("A");
    Serial.print(angle);
    Serial.print(":");
    Serial.println(dist);

    angle += step;
    if (angle >= 180 || angle <= 0) step = -step;
    lastRadarSend = millis();
  }
}

int readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 20000);
  int distance = duration * 0.034 / 2;
  if (distance == 0) distance = 200;  // max si pas d'obstacle
  return distance;
}

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
