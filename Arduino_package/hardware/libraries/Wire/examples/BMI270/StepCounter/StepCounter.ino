/*
This example shows how to enable the step detector, counter, and activity recognition features of the BMI270.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20Step%20Counter.html
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
    Serial.println("BMI270 Example - Step Counter");

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

    // Here we enable the step detector, counter, and activity recognition
    // features of the BMI270; any combination of these is supported.
    //
    // DETECTOR - Triggers an interrupt whenever a step is detected
    // COUNTER  - Increments a counter whenever a step is detected (detector
    //            does not need to be enabled). Triggers an interrupt based on
    //            the step counter watermark (see below)
    // ACTIVITY - The sensor monitors the motion to determine simple user
    //            activities, including standing still, walking, and running. An
    //            interrupt is triggered whenever the activity changes
    imu.enableFeature(BMI2_STEP_DETECTOR);
    imu.enableFeature(BMI2_STEP_COUNTER);
    imu.enableFeature(BMI2_STEP_ACTIVITY);

    // When the step counter feature is enabled, it can trigger an interrupt
    // every number of steps defined by the watermark. This has a factor of 20x,
    // so a value of 1 means 20 step intervals. The step counter interrupt is
    // disabled when the watermark is 0 (default)
    //
    // Note - The step counter and detector interrupts share the same bit in the
    // interrupt status flags registers, so the step detector should be disabled
    // to actually see the step counter interrupts
    imu.setStepCountWatermark(1);

    // The BMI270 has 2 interrupt pins. All interrupt conditions can be mapped
    // to either pin, so we'll just choose the first one for this example
    //
    // Note - The step counter and detector interrupts share the same bit in the
    // interrupt mapping registers, so enabling one enables both
    imu.mapInterruptToPin(BMI2_STEP_COUNTER_INT, BMI2_INT1);
    imu.mapInterruptToPin(BMI2_STEP_ACTIVITY_INT, BMI2_INT1);

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
        if (interruptStatus & BMI270_STEP_CNT_STATUS_MASK) {
            Serial.print("Step detected! Total step count: ");

            // Get the step count
            uint32_t count = 0;
            imu.getStepCount(&count);

            // Print step count
            Serial.print(count);
            Serial.print("\t");
        }
        if (interruptStatus & BMI270_STEP_ACT_STATUS_MASK) {
            Serial.print("Step activity changed! New activity: ");

            // Get the step activity
            uint8_t activity = 0;
            imu.getStepActivity(&activity);

            // Print step activity
            switch (activity) {
                case BMI2_STEP_ACTIVITY_STILL: {
                    Serial.print("Still, resetting step counter");
                    imu.resetStepCount();
                    break;
                }
                case BMI2_STEP_ACTIVITY_WALKING: {
                    Serial.print("Walking");
                    break;
                }
                case BMI2_STEP_ACTIVITY_RUNNING: {
                    Serial.print("Running");
                    break;
                }
                default: {
                    Serial.print("Unknown!");
                    break;
                }
            }
        }
        if (!(interruptStatus & (BMI270_STEP_CNT_STATUS_MASK | BMI270_STEP_ACT_STATUS_MASK))) {
            Serial.print("Unknown interrupt condition!");
        }

        Serial.println();
    }
}

void myInterruptHandler(uint32_t id, uint32_t event)
{
    interruptOccurred = true;
}
