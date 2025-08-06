/*
  This example shows how to use the SparkFun VL53L5CX Time-of-Flight sensor in 8x8 mode
  to detect hand presence.

  Example Guide: TBD
*/

#include <Wire.h>
#include <SparkFun_VL53L5CX_libraries/SparkFun_VL53L5CX_Library.h>

#define HAND_DETECTION_THRESHOLD_MM 100
#define MIN_VALID_READINGS          5
#define NO_VALID_DATA               9999    // The value 9999 is used as a clearly invalid or out-of-range number that signals “no valid data.”

SparkFun_VL53L5CX sensor;
VL53L5CX_ResultsData data;

int imageResolution = 0;
int imageWidth = 0;
float leftAvg, rightAvg;
uint32_t leftColSum = 0, rightColSum = 0;
int leftColCount = 0, rightColCount = 0;

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
    if (sensor.isDataReady() == true) {
        if (sensor.getRangingData(&data))    // Read distance data into array
        {
            leftColSum = 0;
            rightColSum = 0;
            leftColCount = 0;
            rightColCount = 0;

            // Use center rows 2 to 5 to avoid top/bottom noise
            for (int row = 2; row <= 5; row++) {
                for (int col = 0; col < 8; col++) {
                    int idx = row * 8 + col;
                    uint16_t d = data.distance_mm[idx];

                    if (d == 0 || d > 800) {
                        continue;    // Filter out invalid/far readings
                    }

                    if (col < 4) {
                        leftColSum += d;
                        leftColCount++;
                    } else {
                        rightColSum += d;
                        rightColCount++;
                    }
                }
            }

            if (leftColCount < 3 && rightColCount < 3) {
                Serial.println("No hand present");
                delay(67);
                return;
            }

            if (leftColCount > 0) {
                leftAvg = (float)leftColSum / leftColCount;
            } else {
                leftAvg = NO_VALID_DATA;
            }

            if (rightColCount > 0) {
                rightAvg = (float)rightColSum / rightColCount;
            } else {
                rightAvg = NO_VALID_DATA;
            }

            if (abs(leftAvg - rightAvg) < HAND_DETECTION_THRESHOLD_MM) {
                Serial.println("Hand present");
                // printDistance();
            }

            delay(67);
        }
    }
}

// Print the full 8x8 distance grid (in millimeters) as seen by the sensor.
void printDistance()
{
    Serial.println();
    for (int y = 0; y <= imageWidth * (imageWidth - 1); y += imageWidth) {
        Serial.print("\t");
        for (int x = imageWidth - 1; x >= 0; x--)    // print right to left
        {
            Serial.print(data.distance_mm[x + y]);
            Serial.print("\t");
        }
        Serial.println();
    }
    Serial.println();
}
