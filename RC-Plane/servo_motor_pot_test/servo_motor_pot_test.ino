#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
Servo myservo;  // create servo object to control a servo

const byte addresses[][6] = {"00001","00002"}; // Communication address, Connection address
char conn_state = 0; // Receiver connected when this variable is "C"
char uid = 0x30; // UID of the receiver

void connexion_handler(){
  while (conn_state != 'C'){
    radio.stopListening(); // Stop listening to send message to radio
    delay(20);
    radio.write(&uid,sizeof(uid)); // Tell the telecommand the uid to connect
    Serial.println("Sent UID");
    delay(5); // Wait during radio message sending
    radio.startListening(); // Start listening to get a response from the command
    delay(50);
    unsigned long start = millis();
    while (!radio.available() && millis() - start < 15); // 15 ms max attente
    if (radio.available()) {
      radio.read(&conn_state, sizeof(conn_state)); // Read response from the command
    }
  }
}

void setup() {
  myservo.attach(9,600,2300);  // (pin, min, max)
  Serial.begin(9600);
  radio.begin();  // Initisalise la radio
  radio.flush_tx();
  radio.flush_rx();
  radio.openReadingPipe(0, addresses[0]); // Open reading channel (communictaion)
  radio.openWritingPipe(addresses[1]); // Open writing channel (connection)
  radio.setPALevel(RF24_PA_MIN); // Set low emmiting level
  connexion_handler();

  radio.startListening();
  delay(5);
}

void loop() {
  if (radio.available()) {
    short int radio_data[5];
    radio.read(&radio_data, sizeof(radio_data));
    Serial.print(" , Potentiometer 2 Y:");
    Serial.print(radio_data[3]);
    myservo.write(map(radio_data[3], 200, 800, 0, 180));  // tell servo to go to a particular angle
    delay(50);  
  }             
}