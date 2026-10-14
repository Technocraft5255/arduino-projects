#define TRIG_PIN A5
#define ECHO_PIN A4

unsigned long lastMeasure = 0;
const unsigned long interval = 1000; // 1 seconde

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

long mesurerDistance() {
  // Trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lecture avec timeout (30 ms)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1; // Pas d'écho
  }

  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastMeasure >= interval) {
    lastMeasure = currentMillis;

    long distance = mesurerDistance();

    if (distance > 0 && distance < 1180) {
      Serial.print(distance);
      Serial.println(" cm");
    } else {
      Serial.println("Hors portée ou erreur");
    }
  }

  // Ici tu peux ajouter d'autres tâches sans blocage
}