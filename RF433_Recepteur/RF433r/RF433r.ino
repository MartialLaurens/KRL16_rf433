//send data routine

// link between the computer and the SoftSerial Shield
//at 9600 bps 8-N-1
//Computer is connected to Hardware UART
//SoftSerial Shield is connected to the Software UART:D2&D3

#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(11, 10); // TX, RX
int buffer[64];
int count=0;
void setup()
{
    SoftSerial.begin(9600);               // the SoftSerial baud rate
    Serial.begin(9600);             // the Serial port of Arduino baud rate.

}

void loop()
{
    delay(1000);
    SoftSerial.write(0xAA);
    SoftSerial.write(0xFA);
    SoftSerial.write(0xE1);

    if (SoftSerial.available())              // if date is coming from software serial port ==> data is coming from SoftSerial shield
    {
        while(SoftSerial.available())          // reading data into char array
        {
            buffer[count++]=SoftSerial.read();     // writing data into array
            if(count == 64)break;
        }
        for (int i=0; i<count; i++) {
            Serial.print(buffer[i],HEX);            // if no data transmission ends, write buffer to hardware serial port
        }
        clearBufferArray();              // call clearBufferArray function to clear the stored data from the array
        count = 0;                       // set counter of while loop to zero
    }
    if (Serial.available())            // if data is available on hardware serial port ==> data is coming from PC or notebook
    SoftSerial.write(Serial.read());       // write it to the SoftSerial shield
    Serial.println("...");
}
void clearBufferArray()              // function to clear buffer array
{
    for (int i=0; i<count;i++)
    { buffer[i]=NULL;}                  // clear all index of array with command NULL
}
