/*
  This example shows how to use SparkFun NAU7802 to get raw readings using a
  load cell.

  Modified by: Realtek SG (27 January 2026)

  Example Guide:
  *To be added*

  #####

  Use the Qwiic Scale to read load cells and scales
  By: Nathan Seidle @ SparkFun Electronics
  Date: March 3rd, 2019
  License: This code is public domain but you buy me a beer if you use this
  and we meet someday (Beerware license).

  The Qwiic Scale is an I2C device that converts analog signals to a 24-bit
  digital signal. This makes it possible to create your own digital scale
  either by hacking an off-the-shelf bathroom scale or by creating your
  own scale using a load cell.

  This example merely outputs the raw data from a load cell. For example, the
  output may be 25776 and change to 43122 when a cup of tea is set on the scale.
  These values are unitless - they are not grams or ounces. Instead, it is a
  linear relationship that must be calculated. Remember y = mx + b?
  If 25776 is the 'zero' or tare state, and 43122 when I put 15.2oz of tea on
  the scale, then what is a reading of 57683 in oz?

  (43122 - 25776) = 17346/15.2 = 1141.2 per oz
  (57683 - 25776) = 31907/1141.2 = 27.96oz is on the scale

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
    if (myScale.available() == true) {
        int32_t currentReading = myScale.getReading();
        Serial.print("NAU7802 reading: ");
        Serial.println(currentReading);
    }
    delay(1000);
}
