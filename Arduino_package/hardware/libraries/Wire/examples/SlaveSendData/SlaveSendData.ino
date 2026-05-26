/*
 Demonstrates use of the Wire library
 Sends data as an I2C/TWI slave device on AMB82-mini

 Reference to Wire Slave Sender by Nicholas Zambetti <http://www.zambetti.com>.
 This example code is in the public domain.

 modified 15 May 2026
 by Realtek SG

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/Slave%20Send%20Data%20to%20Arduino%20UNO.html
*/

#include <Wire.h>

void setup()
{
    Wire.begin(0x08);                // join I2C bus with address #8
    Wire.onRequest(requestEvent);    // register event
}

void loop()
{
    Wire.slaveWrite();
    delay(2000);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
    Serial.println("\r\n[onRequest] Master is requesting data");
    Wire.write("hello master from slave");    // respond with message of 23 bytes
    Serial.println("Sent to master");
}
