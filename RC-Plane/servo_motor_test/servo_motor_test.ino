/*
     Servo Motor Control using the Arduino Servo Library
           by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9,600,2300);  // (pin, min, max)
}

void loop() {
  myservo.write(0);  // tell servo to go to a particular angle
  delay(1000);
  
  myservo.write(90);              
  delay(1000); 
  
  
  myservo.write(300);              
  delay(1500);                     
}