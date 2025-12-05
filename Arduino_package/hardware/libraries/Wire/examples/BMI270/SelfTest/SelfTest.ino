/*
This example will run the sensor's self test feature. This will return an error code to indicate whether the test was successful.
Note that the sensor will be reset after the test finishes.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20Self%20Test.html
*/
#include <Wire.h>
#include "SparkFun_BMI270_libraries/SparkFun_BMI270_Arduino_Library.h"

// Create a new sensor object
BMI270 imu;

// I2C address selection
uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;    // 0x68
// uint8_t i2cAddress = BMI2_I2C_SEC_ADDR; // 0x69

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("BMI270 Example - Self Test");

    // Initialize the I2C library
    Wire.begin();

    // Check if sensor is connected and initialize
    // Address is optional (defaults to 0x68)
    while (imu.beginI2C(i2cAddress) != BMI2_OK) {
        // Not connected, inform user
        Serial.println("Error: BMI270 not connected, check wiring and I2C address!");

        // Wait a bit to see if connection is established
        delay(1000);
    }

    Serial.println("BMI270 connected!");

    Serial.println("Running self test...");

    // Run the sensor's self test feature. This will return an error code to
    // indicate whether the test was successful. Note that the sensor will be
    // reset after the test finishes
    int8_t err = imu.selfTest();

    if (err == BMI2_OK) {
        Serial.println("Self test passed!");
    } else {
        Serial.print("Self test failed! Error code: ");
        Serial.println(err);
    }
}

void loop()
{
    // Nothing to do here
}
