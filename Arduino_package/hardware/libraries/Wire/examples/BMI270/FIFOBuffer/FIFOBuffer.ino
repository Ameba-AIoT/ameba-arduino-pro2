/*
This example shows how to use SparkFun 6DoF BMI270 to get basic measurements using I2C based on FIFO buffer.

Prepared by: SparkFun Electronics
Modified by: Realtek SG (24 Nov 2025)

Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/BMI270%20FIFO%20Buffer.html
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

// Create a buffer for FIFO data
const uint16_t numSamples = 5;
BMI270_SensorData fifoData[numSamples];

// Track FIFO length to give progress updates
uint8_t previousFIFOLength = 0;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("BMI270 Example - FIFO Buffer");

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
    // 200Hz and gyroscope. Those are too fast for this example, and we want
    // them to be the same for the FIFO, so we'll reduce them both to the
    // minimum ODR that both sensors support (25Hz)
    imu.setAccelODR(BMI2_ACC_ODR_25HZ);
    imu.setGyroODR(BMI2_GYR_ODR_25HZ);

    // Here we configure the FIFO buffer of the BMI270. Each of the config
    // parameters are described below:
    //
    // .flags           - Which features of the FIFO to enable. Only the
    //                    accelerometer and gyroscope in headless mode is
    //                    currently supported
    // .watermark       - Number of data samples to store before triggering an
    //                    interrupt
    // .accelDownSample - Downsampling factor for the accelerometer, relative to
    //                    the sensor's ODR (output data rate)
    // .gyroDownSample  - Downsampling factor for the gyroscope, relative to the
    //                    sensor's ODR (output data rate)
    // .accelFilter     - Whether the accelerometer data is filtered
    // .gyroFilter      - Whether the gyroscope data is filtered
    // .selfWakeUp      - Whether FIFO can be read in low power mode
    BMI270_FIFOConfig config;
    config.flags = BMI2_FIFO_ACC_EN | BMI2_FIFO_GYR_EN;
    config.watermark = numSamples;
    config.accelDownSample = BMI2_FIFO_DOWN_SAMPLE_16;
    config.gyroDownSample = BMI2_FIFO_DOWN_SAMPLE_16;
    config.accelFilter = BMI2_ENABLE;
    config.gyroFilter = BMI2_ENABLE;
    config.selfWakeUp = BMI2_ENABLE;
    imu.setFIFOConfig(config);

    // The BMI270 has 2 interrupt pins. All interrupt conditions can be mapped
    // to either pin, so we'll just choose the first one for this example. We're
    // using the FIFO watermark condition, which triggers whenever the FIFO
    // buffer reches the watermark level
    imu.mapInterruptToPin(BMI2_FWM_INT, BMI2_INT1);

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
    // Get number of data samples currently stored in FIFO buffer
    uint16_t currentFIFOLength = 0;
    imu.getFIFOLength(&currentFIFOLength);

    // Check whether number of samples in FIFO buffer has changed
    if (previousFIFOLength != currentFIFOLength) {
        // Update FIFO length
        previousFIFOLength = currentFIFOLength;

        // Print current FIFO length
        Serial.print("FIFO Length: ");
        Serial.print(currentFIFOLength);
        Serial.print("/");
        Serial.println(numSamples);

        // If the buffer length goes beyond the watermark level, then an
        // interrupt was missed. This example will likely run into issues,
        // so we'll just clear the FIFO buffer
        if (currentFIFOLength > numSamples) {
            Serial.println("Too many samples in FIFO buffer, flushing...");
            imu.flushFIFO();
        }
    }

    // Wait for interrupt to occur
    if (interruptOccurred) {
        // Reset flag for next interrupt
        interruptOccurred = false;

        Serial.println("Interrupt occurred!");

        // Get the interrupt status to know which condition triggered
        uint16_t interruptStatus = 0;
        imu.getInterruptStatus(&interruptStatus);

        // Check if this is the FIFO watermerk interrupt condition
        if (interruptStatus & BMI2_FWM_INT_STATUS_MASK) {
            // Get FIFO data from the sensor
            uint16_t samplesRead = numSamples;
            imu.getFIFOData(fifoData, &samplesRead);

            // samplesRead will be changed to the number of data frames actually
            // read from the FIFO buffer. Check whether it's equal to numSamples
            if (samplesRead != numSamples) {
                // Most likely didn't have enough data frames in FIFO buffer.
                // This can happen if control frames are inserted into the FIFO
                // buffer, which occurs when certain configuration changes occur
                Serial.print("Unexpected number of samples read from FIFO: ");
                Serial.println(samplesRead);
            }

            // Print out all acquired data
            for (uint16_t i = 0; i < samplesRead; i++) {
                // Print acceleration data
                Serial.print("Acceleration in g's");
                Serial.print("\t");
                Serial.print("X: ");
                Serial.print(fifoData[i].accelX, 3);
                Serial.print("\t");
                Serial.print("Y: ");
                Serial.print(fifoData[i].accelY, 3);
                Serial.print("\t");
                Serial.print("Z: ");
                Serial.print(fifoData[i].accelZ, 3);

                Serial.print("\t");

                // Print rotation data
                Serial.print("Rotation in deg/sec");
                Serial.print("\t");
                Serial.print("X: ");
                Serial.print(fifoData[i].gyroX, 3);
                Serial.print("\t");
                Serial.print("Y: ");
                Serial.print(fifoData[i].gyroY, 3);
                Serial.print("\t");
                Serial.print("Z: ");
                Serial.println(fifoData[i].gyroZ, 3);
            }
        } else {
            Serial.println("Unknown interrupt condition!");
        }
    }
}

void myInterruptHandler(uint32_t id, uint32_t event)
{
    interruptOccurred = true;
}
