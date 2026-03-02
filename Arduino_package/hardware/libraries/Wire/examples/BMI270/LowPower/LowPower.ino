/*
This example shows how to lower the power consumption by setting the power mode of each sensor to the power optimized mode.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20Low%20Power.html
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
    Serial.println("BMI270 Example - Low Power");

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

    // We can lower the power consumption by setting the power mode of each
    // sensor to the power optimized mode
    imu.setAccelPowerMode(BMI2_POWER_OPT_MODE);
    imu.setGyroPowerMode(BMI2_POWER_OPT_MODE, BMI2_POWER_OPT_MODE);

    // Lower ODR values result in less power consumption. To ensure the sensors
    // are synchronized, we'll choose the minimum ODR that both sensors support
    imu.setAccelODR(BMI2_ACC_ODR_25HZ);
    imu.setGyroODR(BMI2_GYR_ODR_25HZ);

    // The BMI270 has an advanced power save mode that can be used to minimize
    // current consumption. Note that this comes with some restrictions, see
    // datasheet for details
    imu.enableAdvancedPowerSave();

    // After the sensor has been configured, we can enter suspend mode by
    // disabling both the accelerometer and gyroscope. This can lower the
    // BMI270's current consumption down to 3.5uA
    imu.disableFeature(BMI2_ACCEL);
    imu.disableFeature(BMI2_GYRO);
}

void loop()
{
    // Wait until next measurement. For low power applications, this could be
    // replaced by setting the microcontroller into a sleep state
    delay(1000);

    // Re-enable the sensors to get new measurements. The current consumption
    // depends on which sensors are enabled:
    //
    // Accelerometer only          - Down to 4uA
    // Gyroscope only              - Down to 400uA
    // Accelerometer and gyroscope - Down to 420uA
    imu.enableFeature(BMI2_ACCEL);
    imu.enableFeature(BMI2_GYRO);

    // Wait until the measurements are complete. This is indicated by the DRDY
    // bits getting set in the sensor's status register
    bool accelDRDY = false;
    bool gyroDRDY = false;
    while ((accelDRDY == false) || (gyroDRDY == false)) {
        // Get sensor status
        uint8_t status = 0;
        imu.getStatus(&status);

        // Update data DRDY flags
        if (status & BMI2_DRDY_ACC) {
            accelDRDY = true;
        }
        if (status & BMI2_DRDY_GYR) {
            gyroDRDY = true;
        }
    }

    // Get measurements from the sensor. This must be called before accessing
    // the sensor data, otherwise it will never update
    imu.getSensorData();

    // Go back to suspend mode by disabling the sensors. This must be done
    // after calling getSensorData(), otherwise the data will be zeros
    imu.disableFeature(BMI2_ACCEL);
    imu.disableFeature(BMI2_GYRO);

    // Print acceleration data
    Serial.print("Acceleration in g's");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(imu.data.accelX, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(imu.data.accelY, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.print(imu.data.accelZ, 3);

    Serial.print("\t");

    // Print rotation data
    Serial.print("Rotation in deg/sec");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(imu.data.gyroX, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(imu.data.gyroY, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.println(imu.data.gyroZ, 3);
}
