/*
 * Arduino Wireless Radiocommand 2.4Ghz
 *
 * by Emilien Mariau
 *
 * Made btw 28/10/2025 and 
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define POT_1_X_PIN A3
#define POT_1_Y_PIN A2
#define POT_2_X_PIN A0
#define POT_2_Y_PIN A1

#define BUZZER_PIN 2
#define BTN_PIN 3
#define RED_LED_PIN 4
#define GREEN_LED_PIN 5

RF24 radio(9, 10);                                 // CE, CSN
const byte addresses[][6] = { "00001", "00002" };  // Communication address, Connection address
char receiver_uid = 0x00;
char command_mode = "r"; // Mode r: radiocommande, m: mannete, rc: radiocommande connectée, re: recuperation de données, c: calibrage
enum Mode { RADIO, PC, CRAD, RECOVER, CALIBRATION  };
Mode mode = RADIO;
unsigned long lastSend = 0;
const int sendRate = 10; // ms → 100 Hz

uint16_t joystick_1_x_value;
uint16_t joystick_1_y_value;
uint16_t joystick_2_x_value;
uint16_t joystick_2_y_value;
uint16_t button_state;
uint16_t radio_data[5];


void buzzer_sound_1() {
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, 588);  // fréquence du son (588 Hz)
    delay(75);              // durée du bip (long)
    noTone(BUZZER_PIN);
    delay(75);  // pause entre les bips
  }
}

void buzzer_sound_2() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 700);  // fréquence du son (700 Hz)
    delay(50);              // durée du bip (court)
    noTone(BUZZER_PIN);
    delay(75);  // pause entre les bips
  }
}

void connexion_handler() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  radio.startListening();  // Start listening to the receiver uid
  delay(5);
  while (receiver_uid != 0x30) {
    while (!radio.available())
      ;                                               // Wait for radio available
    radio.read(&receiver_uid, sizeof(receiver_uid));  // Read the receiver uid
    delay(5);                                         // Wait before stop listening
  }
  radio.stopListening();                         // Stop listening to send the connection response
  delay(10);                                     // Wait during stop listening
  char conn_state = 'C';                         // Statut connected
  radio.write(&conn_state, sizeof(conn_state));  // Send response
  delay(5);
  radio.write(&conn_state, sizeof(conn_state));  // Resend response to prevent the receiver from not receiving the response
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  buzzer_sound_1();
}

void setup() {
  pinMode(POT_1_X_PIN, INPUT);
  pinMode(POT_1_Y_PIN, INPUT);
  pinMode(POT_2_X_PIN, INPUT);
  pinMode(POT_2_Y_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  radio.begin();
  radio.flush_tx();
  radio.flush_rx();
  radio.openReadingPipe(0, addresses[1]);
  radio.openWritingPipe(addresses[0]);
  radio.setPALevel(RF24_PA_LOW);
  connexion_handler();

  radio.stopListening();
  delay(5);
}

void loop() {
  // 1. lecture rapide
  joystick_1_x_value = analogRead(POT_1_X_PIN);
  joystick_1_y_value = analogRead(POT_1_Y_PIN);
  joystick_2_x_value = analogRead(POT_2_X_PIN);
  joystick_2_y_value = analogRead(POT_2_Y_PIN);
  button_state = digitalRead(BTN_PIN);

  // 2. envoi contrôlé
  if (millis() - lastSend >= sendRate) {

    lastSend = millis();



    radio_data[0] = joystick_1_x_value;
    radio_data[1] = joystick_1_y_value;
    radio_data[2] = joystick_2_x_value;
    radio_data[3] = joystick_2_y_value;
    radio_data[4] = button_state;

    radio.write(&radio_data, sizeof(radio_data));
  }
}
