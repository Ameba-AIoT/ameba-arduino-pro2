/*
  This example shows how to configure different I2C bus and clock speed for SparkFun NAU7802.

  Modified by: Realtek SG (27 January 2026)

  Example Guide:
  *To be added*

  #####

  Use the Qwiic Scale to read load cells and scales
  By: Nathan Seidle @ SparkFun Electronics
  Date: March 3rd, 2019
  License: This code is public domain but you buy me a beer if you use this
  and we meet someday (Beerware license).

  The NAU7802 supports up to 400kHz. You can also pass different wire ports
  into the library.

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

    // Configure a separate I2C bus
    // On AMB82-mini, this means you have to adjust your pins from
    // Pin 12 (I2C_SDA), 13 (I2C_SCL) to
    // Pin 09 (I2C_SDA1), 10 (I2C_SCL1)
    // if you follow all other examples
    Wire1.begin();

    // We can increase I2C clock speed to 400kHz, the NAU7802 supports it.
    // - You are likely to adjust this only when you requires very high sample
    // rate.
    Wire1.setClock(400000);

    // Pass the Wire port to the library, if not default to use Wire
    if (myScale.begin(Wire1) == false) {
        Serial.println("Scale not detected. Please check wiring. Freezing...");
        while (1)
            ;
    }
    Serial.println("Scale detected!");
}

void loop()
{
    if (myScale.available()) {
        int32_t currentReading = myScale.getReading();
        Serial.print("Reading: ");
        Serial.println(currentReading);
    }
}
