/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/Retrieve%20Data%20from%20VL53L0X%20IR%20sensor.html

*/

#include <Wire.h>
#include <VL53L0X_IR_libraries/VL53L0X.h>

VL53L0X sensor;

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    sensor.setTimeout(500);
    if (!sensor.init()) {
        Serial.println("Failed to detect and initialize sensor!");
        while (1) {
        }
    }

    // Start continuous back-to-back mode (take readings as
    // fast as possible).  To use continuous timed mode
    // instead, provide a desired inter-measurement period in
    // ms (e.g. sensor.startContinuous(100)).
    sensor.startContinuous();
}

void loop()
{
    Serial.print(sensor.readRangeContinuousMillimeters());
    if (sensor.timeoutOccurred()) {
        Serial.print(" TIMEOUT");
    }

    Serial.println();
}
