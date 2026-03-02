/*
This example shows how to enable motion detection using interrupts.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20Motion%20Detection.html
*/

#include <Wire.h>
#include "SparkFun_BMI270_libraries/SparkFun_BMI270_Arduino_Library.h"

// Create a new sensor object
BMI270 imu;

// I2C address selection
uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;    // 0x68
// uint8_t i2cAddress = BMI2_I2C_SEC_ADDR; // 0x69

// Pin used for interrupt detection
int interruptPin = 5;

// Flag to know when interrupts occur
volatile bool interruptOccurred = false;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("BMI270 Example - Motion Detection");

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

    // Here we enable both the "any motion" and "no motion" features of the
    // BMI270. These will trigger interrupts whenever motion is/isn't detected
    // by the accelerometer for a long enough duration
    imu.enableFeature(BMI2_ANY_MOTION);
    imu.enableFeature(BMI2_NO_MOTION);

    // We can configure the parameters for the any/no motion features. The
    // sensor has settings for each of these, described below:
    //
    // .duration  - Time required to trigger an interrupt. 20ms resolution, up
    //              to 163 seconds
    // .threshold - Threshold acceleration required to trigger an interrupt.
    //              Range is 0-1g with 11 bits, or 1/2048 = 0.49mg resolution
    // .select_x  - Whether to use this axis
    // .select_y  - Whether to use this axis
    // .select_z  - Whether to use this axis
    //
    // This example uses the default parameter values defined by the sensor, but
    // you can change these values by uncommenting the code below

    // Set the "any motion" config. Default values:
    //
    // .duration  - 5 = 100ms
    // .threshold - 170 = 83mg
    // .select_x  - Enabled
    // .select_y  - Enabled
    // .select_z  - Enabled
    //
    // bmi2_sens_config anyMotionConfig;
    // anyMotionConfig.type = BMI2_ANY_MOTION;
    // anyMotionConfig.cfg.any_motion.duration = 5;
    // anyMotionConfig.cfg.any_motion.threshold = 170;
    // anyMotionConfig.cfg.any_motion.select_x = BMI2_ENABLE;
    // anyMotionConfig.cfg.any_motion.select_y = BMI2_ENABLE;
    // anyMotionConfig.cfg.any_motion.select_z = BMI2_ENABLE;
    // imu.setConfig(anyMotionConfig);

    // Set the "no motion" config. Default values:
    //
    // .duration  - 5 = 100ms
    // .threshold - 144 = 70mg
    // .select_x  - Enabled
    // .select_y  - Enabled
    // .select_z  - Enabled
    //
    // bmi2_sens_config noMotionConfig;
    // noMotionConfig.type = BMI2_NO_MOTION;
    // noMotionConfig.cfg.no_motion.duration = 5;
    // noMotionConfig.cfg.no_motion.threshold = 144;
    // noMotionConfig.cfg.no_motion.select_x = BMI2_ENABLE;
    // noMotionConfig.cfg.no_motion.select_y = BMI2_ENABLE;
    // noMotionConfig.cfg.no_motion.select_z = BMI2_ENABLE;
    // imu.setConfig(noMotionConfig);

    // The BMI270 has 2 interrupt pins. All interrupt conditions can be mapped
    // to either pin, so we'll just choose the first one for this example
    imu.mapInterruptToPin(BMI2_ANY_MOTION_INT, BMI2_INT1);
    imu.mapInterruptToPin(BMI2_NO_MOTION_INT, BMI2_INT1);

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

        // Check if this is the correct interrupt condition
        if (interruptStatus & BMI270_ANY_MOT_STATUS_MASK) {
            Serial.print("Any motion!");
            Serial.print("\t");
        }
        if (interruptStatus & BMI270_NO_MOT_STATUS_MASK) {
            Serial.print("No motion!");
        }
        if (!(interruptStatus & (BMI270_ANY_MOT_STATUS_MASK | BMI270_NO_MOT_STATUS_MASK))) {
            Serial.print("Unknown interrupt condition!");
        }

        Serial.println();
    }
}

void myInterruptHandler(uint32_t id, uint32_t event)
{
    interruptOccurred = true;
}
