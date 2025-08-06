/*
 Wire Master Writer
 by Nicholas Zambetti <http://www.zambetti.com>

 Demonstrates use of the Wire library
 Writes data to an I2C/TWI slave device
 Refer to the "Wire Slave Receiver" example for use with this

 Created 29 March 2006

 This example code is in the public domain.

 modified 17 Jan 2023
 by Realtek SG

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/Master%20Send%20Data%20to%20Arduino%20UNO.html
 */

#include <Wire.h>

void setup()
{
    Serial.begin(115200);
    Wire.begin();    // join i2c bus (address optional for master)
    Serial.println("Master writer sending data to slave 8");
}

byte x = 0;

void loop()
{
    Wire.beginTransmission(8);    // transmit to device #8
    Wire.write("x is ");          // sends five bytes
    Wire.write(x);                // sends one byte
    Wire.endTransmission();       // stop transmitting

    x++;
    delay(500);
}
