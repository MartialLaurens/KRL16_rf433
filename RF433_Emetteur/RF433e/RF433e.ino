// link between the computer and the SoftSerial Shield
//at 9600 bps 8-N-1
//Computer is connected to Hardware UART
//SoftSerial Shield is connected to the Software UART:D2&D3 
 
#include <SoftwareSerial.h>
#include "DHT12.h"
#include <Wire.h>
DHT12 dht12;
 
SoftwareSerial SoftSerial(2, 3);
unsigned char buffer[64]; // buffer array for data recieve over serial port
int count=0;     // counter for buffer array 

void setup()
{
  Wire.begin();
  SoftSerial.begin(9600);               // the SoftSerial baud rate   
  Serial.begin(9600);             // the Serial port of Arduino baud rate.
}

 
void loop()
{
  /*if(SoftSerial.available())              // if date is comming from softwareserial port ==> data is comming from SoftSerial shield
  {
    while(SoftSerial.available())          // reading data into char array 
    {
      buffer[count++]=SoftSerial.read();     // writing data into array
      if(count == 64)break;
    }
    Serial.write(buffer,count);            // if no data transmission ends, write buffer to hardware serial port
    clearBufferArray();              // call clearBufferArray function to clear the storaged data from the array
    count = 0;                       // set counter of while loop to zero
  }
  
  if (Serial.available())            // if data is available on hardwareserial port ==> data is comming from PC or notebook
    SoftSerial.write(Serial.read());       // write it to the SoftSerial shield*/


    int deciTemperature = 0;
    int deciHumidite = 0;

    int erreur = dht12.read( &deciTemperature, &deciHumidite );
    
    SoftSerial.print("Temperature °C : "); SoftSerial.println( (float)deciTemperature /10.0 );
    SoftSerial.print("Humidite     % : "); SoftSerial.println( (float)deciHumidite /10.0 ); 
    delay(5000);
}


void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer[i]=NULL;}                  // clear all index of array with command NULL
}
