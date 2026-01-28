/*
This example shows how to use SparkFun HX711 to get raw reading using a load cell.

Prepared by: Realtek SG (22 January 2026)

Example Guide:
*To be added*
*/

#include "HX711.h"

// Define HX711 pins
const int HX711_DAT_PIN = 2;
const int HX711_CLK_PIN = 3;

// Define HX711 instance
HX711 loadCell;

void setup()
{
    Serial.begin(115200);

    // Set up pins
    loadCell.begin(HX711_DAT_PIN, HX711_CLK_PIN);
    delay(1000);
}

void loop()
{

    if (!loadCell.is_ready()) {
        Serial.println("HX711 not found. Check wiring");
    } else {
        long reading = loadCell.read();
        Serial.print("HX711 reading: ");
        Serial.println(reading);
    }
    delay(1000);
}
