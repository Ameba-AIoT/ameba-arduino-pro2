/*
  This example shows how to use the SparkFun VL53L5CX Time-of-Flight sensor in 8x8 mode
  to detect thumbs-up or thumbs-down gestures.

  Example Guide:
  https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/VL53L5CX%20sensor%20Hand%20Presence%20Detection.html
*/

#include <Wire.h>
#include <SparkFun_VL53L5CX_libraries/SparkFun_VL53L5CX_Library.h>

#define THUMB_DETECTION_THRESHOLD_MM 50
#define MIN_VALID_READINGS           5
#define NO_VALID_DATA                9999    // The value 9999 is used as a clearly invalid or out-of-range number that signals “no valid data.”

SparkFun_VL53L5CX sensor;
VL53L5CX_ResultsData data;

int imageResolution = 0;
int imageWidth = 0;

uint32_t topRowSum = 0, bottomRowSum = 0;
int topRowCount = 0, bottomRowCount = 0;
float topRowAvg, bottomRowAvg;

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
            topRowSum = 0;
            bottomRowSum = 0;
            topRowCount = 0;
            bottomRowCount = 0;

            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    int idx = row * 8 + col;
                    uint16_t d = data.distance_mm[idx];
                    if (d == 0 || d > 800) {
                        continue;
                    }

                    // Collect data for top 3 rows (rows 0–2)
                    if (row <= 2) {
                        topRowSum += d;
                        topRowCount++;
                    }
                    // Collect data for bottom 3 rows (rows 5–7)
                    else if (row >= 5) {
                        bottomRowSum += d;
                        bottomRowCount++;
                    }
                }
            }

            // Compute average distances for top and bottom zones
            // Uses NO_VALID_DATA to represent “no data” if count is zero.
            if (topRowCount > 0) {
                topRowAvg = (float)topRowSum / topRowCount;
            } else {
                topRowAvg = NO_VALID_DATA;
            }

            if (bottomRowCount > 0) {
                bottomRowAvg = (float)bottomRowSum / bottomRowCount;
            } else {
                bottomRowAvg = NO_VALID_DATA;
            }

            // This part can be calibrated based on the orientation of your sensor
            // THUMB_DETECTION_THRESHOLD_MM can be calibrated depending on the distance between your hand and sensor
            if (topRowAvg < bottomRowAvg - THUMB_DETECTION_THRESHOLD_MM && topRowCount >= MIN_VALID_READINGS) {
                Serial.println("Thumbs DOWN 👎");
                // printDistance();
            } else if (bottomRowAvg < topRowAvg - THUMB_DETECTION_THRESHOLD_MM && bottomRowCount >= MIN_VALID_READINGS) {
                Serial.println("Thumbs UP 👍");
                // printDistance();
            } else {
                Serial.println("Unclear thumb direction");
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
