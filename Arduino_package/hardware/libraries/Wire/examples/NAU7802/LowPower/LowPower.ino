/*
  This example shows how to setup low power consumption on Sparkfun NAU7802.

  Modified by: Realtek SG (27 January 2026)

  Example Guide:
  *To be added*

  #####

  Use the Qwiic Scale to read load cells and scales
  By: Nathan Seidle @ SparkFun Electronics
  Date: March 3rd, 2019
  License: This code is public domain but you buy me a beer if you use this
  and we meet someday (Beerware license).

  The NAU7802 runs at ~2mA but can be powered down to 200nA if needed.
  This example turns the scale on once per second.

  SparkFun labored with love to create this code. Feel like supporting open
  source? Buy a board from SparkFun!
  https://www.sparkfun.com/products/15242

  Hardware Connections:
  Plug a Qwiic cable into the Qwiic Scale and a RedBoard Qwiic
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic
  Breadboard Jumper (https://www.sparkfun.com/products/14425) Open the serial
  monitor at 115200 baud to see the output
*/

#include <Wire.h>

#include "SparkFun_NAU7802_libraries/SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

NAU7802 myScale;    // Create instance of the NAU7802 class

void setup()
{
    Serial.begin(115200);
    Serial.println("Qwiic Scale Example");

    Wire.begin();

    if (myScale.begin() == false) {
        Serial.println("Scale not detected. Please check wiring. Freezing...");
        while (1)
            ;
    }
    Serial.println("Scale detected!");
}

void loop()
{

    // Time how long it takes for scale to take a reading
    // This should be significantly faster if you do NOT power down then power up,
    // i.e., comment out the following lines:

    // ####################
    // Power down to ~200nA
    myScale.powerDown();
    // Wait for 1s
    delay(1000);
    // Power up NAU7802.
    myScale.powerUp();
    // ####################

    // ^ Try it out!

    unsigned long startTime = millis();
    while (myScale.available() == false) {
        delay(1);
    }

    int32_t currentReading = myScale.getReading();
    Serial.print("Startup time: ");
    Serial.print(millis() - startTime);
    Serial.print(", ");
    Serial.println(currentReading);
}
