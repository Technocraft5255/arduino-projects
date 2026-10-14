#include <Wire.h>
void writeEEPROM(int address, byte val, int i2c_address){
  Wire.beginTransmission(i2c_address);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.write(val);
  Wire.endTransmission();
  delay(5);
}

byte readEEPROM(int address, int i2c_address){
  byte rcvData = 0xFF; 
  Wire.beginTransmission(i2c_address);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(i2c_address, 1);
  rcvData =  Wire.read();
  return rcvData;
}


void setup() {   
  Wire.begin();
  Serial.begin(9600);
  Serial.print("Reading");
  delay(500);
  Serial.print('.');
  delay(500);
  Serial.print('.');
  delay(500);
  Serial.println('.');

}

void loop() {
  // put your main code here, to run repeatedly:
}
