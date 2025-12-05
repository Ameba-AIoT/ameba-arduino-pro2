/*
This example shows how to configure interrupt pins to take measurement.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20Interrupts.html
*/

#include <Wire.h>
#include "SparkFun_BMI270_libraries/SparkFun_BMI270_Arduino_Library.h"

// Create a new sensor object
BMI270 imu;

// I2C address selection
uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;    // 0x68
// uint8_t i2cAddress = BMI2_I2C_SEC_ADDR; // 0x69

// Pin used for interrupt detection, kindly check AMB82-mini pin definition for supported interrupt pins
int interruptPin = 5;

// Flag to know when interrupts occur
volatile bool interruptOccurred = false;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("BMI270 Example - Interrupts");

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

    // The default ODR (output data rate) is 100Hz for the accelerometer, and
    // 200Hz and gyroscope. Those are too fast for this example, so we'll reduce
    // them both to their minimum values of 0.78Hz and 25Hz respectively. Note
    // that performance mode of each sensor limits which ODR settings are valid,
    // see datasheet for more info
    //
    // Accelerometer
    // Performance optimized mode - 12.5Hz to 1600Hz
    // Power optimized mode       - 0.78Hz to 400Hz
    //
    // Gyroscope
    // Performance optimized mode - 25Hz to 3200Hz
    // Power optimized mode       - 25Hz to 100Hz
    imu.setAccelPowerMode(BMI2_POWER_OPT_MODE);
    imu.setAccelODR(BMI2_ACC_ODR_0_78HZ);
    imu.setGyroODR(BMI2_GYR_ODR_25HZ);

    // If you only want measurements from one sensor, you can disable the other
    // sensor by calling disableFeature() like this:
    // imu.disableFeature(BMI2_ACCEL);
    // imu.disableFeature(BMI2_GYRO);

    // The BMI270 has 2 interrupt pins. All interrupt conditions can be mapped
    // to either pin, so we'll just choose the first one for this example. We're
    // using the data ready (DRDY) condition, which triggers whenever the sensor
    // makes a new measurement
    imu.mapInterruptToPin(BMI2_DRDY_INT, BMI2_INT1);

    // Here we configure the interrupt pins using a bmi2_int_pin_config, which
    // allows for both pins to be configured simultaneously if needed. Here's a
    // brief description of each value:
    //
    // .pin_type  - Which pin(s) is being configured (INT1, INT2, or BOTH)
    // .int_latch - Latched or pulsed signal (applies to both pins)
    // .pin_cfg   - Array of settings for each pin (index 0/1 for INT1/2):
    //     .lvl       - Active high or low
    //     .od        - Push/pull or open drain output
    //     .output_en - Whether to enable outputs from this pin
    //     .input_en  - Whether to enable inputs to this pin (see datasheet)
    //
    // In this case, we set INT1 to pulsed, active high, push/pull
    bmi2_int_pin_config intPinConfig;
    intPinConfig.pin_type = BMI2_INT1;
    intPinConfig.int_latch = BMI2_INT_NON_LATCH;
    intPinConfig.pin_cfg[0].lvl = BMI2_INT_ACTIVE_HIGH;
    intPinConfig.pin_cfg[0].od = BMI2_INT_PUSH_PULL;
    intPinConfig.pin_cfg[0].output_en = BMI2_INT_OUTPUT_ENABLE;
    intPinConfig.pin_cfg[0].input_en = BMI2_INT_INPUT_DISABLE;
    imu.setInterruptPinConfig(intPinConfig);

    // Setup interrupt handler
    pinMode(interruptPin, INPUT_IRQ_RISE);
    digitalSetIrqHandler(interruptPin, myInterruptHandler);
}

void loop()
{
    // Wait for interrupt to occur
    if (interruptOccurred) {
        // Reset flag for next interrupt
        interruptOccurred = false;

        Serial.print("Interrupt occurred!");
        Serial.print("\t");

        // Get the interrupt status to know which condition triggered
        uint16_t interruptStatus = 0;
        imu.getInterruptStatus(&interruptStatus);

        // Check if this is the "data ready" interrupt condition
        if (interruptStatus & BMI2_GYR_DRDY_INT_MASK) {
            Serial.print("Gyro data ready!");
            Serial.print("\t");

            // Get measurements from the sensor. This must be called before
            // accessing the sensor data, otherwise it will never update
            imu.getSensorData();

            // Print rotation data
            Serial.print("X: ");
            Serial.print(imu.data.gyroX, 3);
            Serial.print("\t");
            Serial.print("Y: ");
            Serial.print(imu.data.gyroY, 3);
            Serial.print("\t");
            Serial.print("Z: ");
            Serial.print(imu.data.gyroZ, 3);
            Serial.print("\t");
        }
        if (interruptStatus & BMI2_ACC_DRDY_INT_MASK) {
            Serial.print("Accelerometer data ready!");
            Serial.print("\t");

            // Get measurements from the sensor. This must be called before
            // accessing the sensor data, otherwise it will never update
            imu.getSensorData();

            // Print rotation data
            Serial.print("X: ");
            Serial.print(imu.data.accelX, 3);
            Serial.print("\t");
            Serial.print("Y: ");
            Serial.print(imu.data.accelY, 3);
            Serial.print("\t");
            Serial.print("Z: ");
            Serial.print(imu.data.accelZ, 3);
        }
        if (!(interruptStatus & (BMI2_GYR_DRDY_INT_MASK | BMI2_ACC_DRDY_INT_MASK))) {
            Serial.print("Unknown interrupt condition!");
        }

        Serial.println();
    }
}

void myInterruptHandler(uint32_t id, uint32_t event)
{
    interruptOccurred = true;
}
