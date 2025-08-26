/*
  Read an 8x8 array of distances from the VL53L5CX
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 26, 2021
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  Modified 02 Jul 2025
  by Realtek SG

  This example shows how to read all 64 distance readings at once.

  Example Guide:
  https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/VL53L5CX%20Distance%20Array.html
*/

#include <Wire.h>
#include <SparkFun_VL53L5CX_libraries/SparkFun_VL53L5CX_Library.h>

SparkFun_VL53L5CX sensor;
VL53L5CX_ResultsData data;

int imageResolution = 0;
int imageWidth = 0;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin();
    Wire.setClock(400000);

    Serial.println("Initializing sensor board. This can take up to 10s. Please wait.");
    if (sensor.begin() == false) {
        Serial.println(F("Sensor not found - check your wiring. Freezing"));
        while (1)
            ;
    }

    sensor.setResolution(8 * 8);    // Enable all 64 pads

    imageResolution = sensor.getResolution();    // Query sensor for current resolution - either 4x4 or 8x8
    imageWidth = sqrt(imageResolution);          // Calculate printing width

    sensor.startRanging();
}

void loop()
{
    // Poll sensor for new data
    if (sensor.isDataReady() == true) {
        if (sensor.getRangingData(&data))    // Read distance data into array
        {
            // The ST library returns the data transposed from zone mapping shown in datasheet
            // Pretty-print data with increasing y, decreasing x to reflect reality
            for (int y = 0; y <= imageWidth * (imageWidth - 1); y += imageWidth) {
                for (int x = imageWidth - 1; x >= 0; x--) {
                    Serial.print("\t");
                    Serial.print(data.distance_mm[x + y]);
                }
                Serial.println();
            }
            Serial.println();
        }
    }

    delay(5);    // Small delay between polling
}
