#define LED1 9
#define LED2 8
#define LED3 7
#define LED4 6
#define LED5 5

#define BUTTON_PLUS 2
#define BUTTON_MINUS 4
#define MOTOR_PIN 3

short unsigned int button_plus_state;
short unsigned int button_minus_state;
short unsigned int power;



long get_speed_with_power(long x) {
  return (332.8 * (1 - 1.5 / (x + 1.5)));
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(BUTTON_PLUS, INPUT);
  pinMode(BUTTON_MINUS, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);

  button_plus_state = 0;
  button_minus_state = 0;
  power = 0;
}

void loop() {
  // plus btn test
  if (digitalRead(BUTTON_PLUS) == HIGH) {
    if ((button_plus_state == 0) && (power < 5)) {
      power++;
      //set Motor speed
      analogWrite(3,min(get_speed_with_power(power),255));
      Serial.println(power);
    }
    button_plus_state = 1;
  } else {
    button_plus_state = 0;
  }
  // minus btn test
  if (digitalRead(BUTTON_MINUS) == HIGH) {
    if ((button_minus_state == 0) && (power > 0)) {
      power--;
      //set Motor speed
      analogWrite(3,min(get_speed_with_power(power),255));
      Serial.println(power);
    }
    button_minus_state = 1;
  } else {
    button_minus_state = 0;
  }
  //LED lighting
  switch (power) {
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      break;
    case 1:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      break;
    case 2:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      break;
    case 3:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      break;
    case 4:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, LOW);
      break;
    case 5:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, HIGH);
      break;
  }

  delay(90);
}
