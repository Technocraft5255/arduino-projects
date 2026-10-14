#include "Wire.h"

#define EEPROM_I2C_ADDRESS 0x50

void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  int address = 0;
  byte val = 110;
  writeAddress(40,0x00);
  //writeAddress(address, val);
  for(int address = 0;address<16000;address++){
    byte readVal = readAddress(address);
  
    Serial.print(address);
    Serial.print(" : ");
    Serial.println(readVal);
    }
  

}

void loop() 
{

}

void writeAddress(int address, byte val)
{
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  
   
  Wire.write(val);
  Wire.endTransmission();

  delay(5);
}

byte readAddress(int address)
{
  byte rData = 0xFF;
  
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.endTransmission();  


  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);  

  rData =  Wire.read();

  return rData;
}
