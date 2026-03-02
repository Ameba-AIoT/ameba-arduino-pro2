/*
This example perform component retrim for the gyroscope, and offset calibration for both the accelerometer and IMU.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20Calibration%20NVM.html
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
    Serial.println("BMI270 Example - Calibration NVM");

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

    Serial.println("Place the sensor on a flat surface and leave it stationary.");
    Serial.println("Enter any key to begin calibration.");

    // Throw away any previous inputs
    while (Serial.available() != 0) {
        Serial.read();
    }
    // Wait for user input
    while (Serial.available() == 0) {
    }

    Serial.println();
    Serial.println("Average sensor values before calibration:");
    printAverageSensorValues();
    Serial.println();

    // Perform component retrim for the gyroscope. According to the datasheet,
    // the gyroscope has a typical error of 2%, but running the CRT can reduce
    // that error to 0.4%
    Serial.println("Performing component retrimming...");
    imu.performComponentRetrim();

    // Perform offset calibration for both the accelerometer and IMU. This will
    // automatically determine the offset of each axis of each sensor, and
    // that offset will be subtracted from future measurements. Note that the
    // offset resolution is limited for each sensor:
    //
    // Accelerometer offset resolution: 0.0039 g
    // Gyroscope offset resolution: 0.061 deg/sec
    Serial.println("Performing accelerometer offset calibration...");
    imu.performAccelOffsetCalibration(BMI2_GRAVITY_POS_Z);
    Serial.println("Performing gyroscope offset calibration...");
    imu.performGyroOffsetCalibration();

    Serial.println();
    Serial.println("Calibration complete!");
    Serial.println();
    Serial.println("Average sensor values after calibration:");
    printAverageSensorValues();
    Serial.println();

    Serial.println("These calibration values can be stored in the sensor's non-volatile memory (NVM).");
    Serial.println("Would you like to save these values to the NVM? If so, enter 'Y'");

    // Throw away any previous inputs
    while (Serial.available() != 0) {
        Serial.read();
    }
    // Wait for user input
    while (Serial.available() == 0) {
    }

    // Check to see if user wants to save values to NVM
    if (Serial.read() == 'Y') {
        Serial.println();
        Serial.println("!!! WARNING !!! WARNING !!! WARNING !!! WARNING !!! WARNING !!!");
        Serial.println();
        Serial.println("The BMI270's NVM only supports 14 write cycles TOTAL!");
        Serial.println("Are you sure you want to save to the NVM? If so, enter 'Y' again");

        // Throw away any previous inputs
        while (Serial.available() != 0) {
            Serial.read();
        }
        // Wait for user input
        while (Serial.available() == 0) {
        }

        // Check to see if user *really* wants to save values to NVM
        if (Serial.read() == 'Y') {
            // Save NVM contents
            int8_t err = imu.saveNVM();

            // Check to see if the NVM saved successfully
            if (err == BMI2_OK) {
                Serial.println();
                Serial.println("Calibration values have been saved to the NVM!");
            } else {
                Serial.print("Error saving to NVM, error code: ");
                Serial.println(err);
            }
        }
    }

    Serial.println();
    Serial.println("Example done!");
}

// This helper function samples the sensor several times and prints the average
void printAverageSensorValues()
{
    // Variables to store the sum of each sensor axis
    float accXSum = 0;
    float accYSum = 0;
    float accZSum = 0;

    float gyrXSum = 0;
    float gyrYSum = 0;
    float gyrZSum = 0;

    // Collect 50 measurements at 50Hz
    int numSamples = 50;
    for (int i = 0; i < numSamples; i++) {
        // Get measurements from the sensor
        imu.getSensorData();

        // Add this measurement to the running total
        accXSum += imu.data.accelX;
        accYSum += imu.data.accelY;
        accZSum += imu.data.accelZ;

        gyrXSum += imu.data.gyroX;
        gyrYSum += imu.data.gyroY;
        gyrZSum += imu.data.gyroZ;

        // Wait for next measurement
        delay(20);
    }

    // Print acceleration data
    Serial.print("Acceleration in g's");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(accXSum / numSamples, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(accYSum / numSamples, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.print(accZSum / numSamples, 3);

    Serial.print("\t");

    // Print rotation data
    Serial.print("Rotation in deg/sec");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(gyrXSum / numSamples, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(gyrYSum / numSamples, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.println(gyrZSum / numSamples, 3);
}

void loop()
{
    // Nothing to do here
}
