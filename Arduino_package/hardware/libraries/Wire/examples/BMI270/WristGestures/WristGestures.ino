/*
This example shows the application of BMI270 on detecting wrist gestures.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20Wrist%20Gestures.html
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
    Serial.println("BMI270 Example - Wrist Gestures");

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

    // Here we enable both the "wrist wake up" and "wrist gesture" features of
    // the BMI270. These assume the sensor is mounted to a user's wrist like a
    // smart watch
    //
    // WEAR_WAKE_UP - Triggers an interrupt whenever the arm is rotated so the
    //                user can see the watch face (called the "focus position")
    // GESTURE      - Triggers an interrupt whenever the user moves their arm in
    //                a specific way while looking at the watch face. Gestures:
    //     Flick-in     - The wrist is slowly rotated away, then quickly rotated
    //                    back to face the user
    //     Flick-out    - The wrist is quickly rotated away, then slowly rotated
    //                    back to face the user
    //     Arm-down     - The arm is quickly pushed down, then brought back to
    //                    face the user
    //     Arm-up       - The arm is quickly pushed up, then brought back to
    //                    face the user
    //     Shake/jiggle - The user shakes their hand quickly
    imu.enableFeature(BMI2_WRIST_WEAR_WAKE_UP);
    imu.enableFeature(BMI2_WRIST_GESTURE);

    // The sensor assumes the axes have a particular orientation with respect to
    // the watch face, where +Y is at 12 o'clock, and +X is at 3 o'clock. You
    // can remap the axes if needed by uncommenting the code below
    // bmi2_remap axes;
    // axes.x = BMI2_AXIS_POS_X;
    // axes.y = BMI2_AXIS_POS_Y;
    // axes.z = BMI2_AXIS_POS_Z;
    // imu.remapAxes(axes);

    // We can configure the parameters for the "wrist wake up" feature.
    // The sensor has default settings for each of these, described below:
    //
    // .min_angle_focus    - Minimum expected change in attitude angle in a 1
    //                       second period when moving within focus position.
    //                       Value is 2048 * cos(angle) (default: 1448 = 45 deg)
    //                       Range is 1024 to 1774 (60 to 30 deg)
    // .min_angle_nonfocus - Minimum expected change in attitude angle in a 1
    //                       second period when moving from non-focus position
    //                       to the focus position.
    //                       Value is 2048 * cos(angle) (default: 1774 = 30 deg)
    //                       Range is 1448 to 1856 (45 to 25 deg)
    // .max_tilt_lr        - Maximum tilt angle to the right that defines the
    //                       focus position.
    //                       Value is 2048 * sin(angle) (default: 1024 = 30 deg)
    //                       Range is 700 to 1024 (20 to 30 deg)
    // .max_tilt_ll        - Maximum tilt angle to the left that defines the
    //                       focus position.
    //                       Value is 2048 * sin(angle) (default: 700 = 20 deg)
    //                       Range is 700 to 1024 (20 to 30 deg)
    // .max_tilt_pd        - Maximum tilt angle to the front that defines the
    //                       focus position.
    //                       Value is 2048 * sin(angle) (default: 179 = 5 deg)
    //                       Range is 0 to 179 (0 to 5 deg)
    // .max_tilt_pu        - Maximum tilt angle to the back that defines the
    //                       focus position.
    //                       Value is 2048 * sin(angle) (default: 1925 = 70 deg)
    //                       Range is 1774 to 1978 (60 to 75 deg)
    //
    // This example uses the default parameter values defined by the sensor, but
    // you can change these values by uncommenting the lines below
    //
    // bmi2_sens_config wristWakeUpConfig;
    // wristWakeUpConfig.type = BMI2_WRIST_WEAR_WAKE_UP;
    // wristWakeUpConfig.cfg.wrist_wear_wake_up.min_angle_focus = 1448;
    // wristWakeUpConfig.cfg.wrist_wear_wake_up.min_angle_nonfocus = 1774;
    // wristWakeUpConfig.cfg.wrist_wear_wake_up.max_tilt_lr = 1024;
    // wristWakeUpConfig.cfg.wrist_wear_wake_up.max_tilt_ll = 700;
    // wristWakeUpConfig.cfg.wrist_wear_wake_up.max_tilt_pd = 179;
    // wristWakeUpConfig.cfg.wrist_wear_wake_up.max_tilt_pu = 1925;
    // imu.setConfig(wristWakeUpConfig);

    // We can configure the parameters for the "wrist gesture" feature.
    // The sensor has default settings for each of these, described below:
    //
    // .wearable_arm      - Left (default) or right arm
    // .min_flick_peak    - Minimum angle required for the wrist flick gesture
    //                      Value is 2048 * sin(angle) (default: 1774 = 60 deg)
    //                      Range is 1448 to 1774 (45 to 60 deg)
    // .min_flick_samples - Minimum time between wrist roll-in/out during flick
    //                      gestures. Range is 3-5 samples with 20ms resolution
    //                      (default: 4 = 80ms)
    // .max_duration      - Max time in which gestures must finish. Range is
    //                      150-200 with 20ms resolution (default: 200 = 4s)
    //
    // This example uses the default parameter values defined by the sensor, but
    // you can change these values by uncommenting the code below
    //
    // bmi2_sens_config wristGestureConfig;
    // wristGestureConfig.type = BMI2_WRIST_GESTURE;
    // wristGestureConfig.cfg.wrist_gest.wearable_arm = BMI2_ARM_LEFT;
    // wristGestureConfig.cfg.wrist_gest.min_flick_peak = 1774;
    // wristGestureConfig.cfg.wrist_gest.min_flick_samples = 4;
    // wristGestureConfig.cfg.wrist_gest.max_duration = 200;
    // imu.setConfig(wristGestureConfig);

    // The BMI270 has 2 interrupt pins. All interrupt conditions can be mapped
    // to either pin, so we'll just choose the first one for this example
    imu.mapInterruptToPin(BMI2_WRIST_WEAR_WAKE_UP_INT, BMI2_INT1);
    imu.mapInterruptToPin(BMI2_WRIST_GESTURE_INT, BMI2_INT1);

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
        if (interruptStatus & BMI270_WRIST_WAKE_UP_STATUS_MASK) {
            Serial.print("Wake up!");

            Serial.print("\t");
        }
        if (interruptStatus & BMI270_WRIST_GEST_STATUS_MASK) {
            Serial.print("Gesture: ");

            // Get the gesture
            uint8_t gesture = 0;
            imu.getWristGesture(&gesture);

            // Print gesture
            switch (gesture) {
                case BMI2_WRIST_GESTURE_ARM_DOWN: {
                    Serial.print("Arm down");
                    break;
                }
                case BMI2_WRIST_GESTURE_ARM_UP: {
                    Serial.print("Arm up");
                    break;
                }
                case BMI2_WRIST_GESTURE_SHAKE_JIGGLE: {
                    Serial.print("Shake jiggle");
                    break;
                }
                case BMI2_WRIST_GESTURE_FLICK_IN: {
                    Serial.print("Flick in");
                    break;
                }
                case BMI2_WRIST_GESTURE_FLICK_OUT: {
                    Serial.print("Flick out");
                    break;
                }
                default: {
                    Serial.print("Unknown!");
                    break;
                }
            }
        }
        if (!(interruptStatus & (BMI270_WRIST_WAKE_UP_STATUS_MASK | BMI270_WRIST_GEST_STATUS_MASK))) {
            Serial.print("Unknown interrupt condition!");
        }

        Serial.println();
    }
}

void myInterruptHandler(uint32_t id, uint32_t event)
{
    interruptOccurred = true;
}
