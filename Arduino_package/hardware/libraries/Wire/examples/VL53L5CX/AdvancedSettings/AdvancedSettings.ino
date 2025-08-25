/*
  Read an 8x8 array of distances from the VL53L5CX
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 26, 2021
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  Modified 02 Jul 2025
  by Realtek SG

  This example shows how to configure:
    Ranging Mode
    Power Mode
    Integration Time
    Sharpener Percent
    Target Order
    Start/Stop Ranging

  Example Guide:
  https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/I2C/VL53L5CX%20Advanced%20Settings.html
*/

#include <Wire.h>
#include <SparkFun_VL53L5CX_libraries/SparkFun_VL53L5CX_Library.h>

SparkFun_VL53L5CX sensor;
VL53L5CX_ResultsData data;    // Result data class structure, 1356 byes of RAM

int imageResolution = 0;    // Used to pretty print output
int imageWidth = 0;         // Used to pretty print output

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("SparkFun VL53L5CX Imager Example");

    Wire.begin();              // This resets to 100kHz I2C
    Wire.setClock(1000000);    // Sensor has max I2C freq of 1MHz

    Serial.println("Initializing sensor board. This can take up to 10s. Please wait.");
    if (sensor.begin() == false) {
        Serial.println(F("Sensor not found - check your wiring. Freezing"));
        while (1)
            ;
    }

    sensor.setResolution(8 * 8);    // Enable all 64 pads

    imageResolution = sensor.getResolution();    // Query sensor for current resolution - either 4x4 or 8x8
    imageWidth = sqrt(imageResolution);          // Calculate printing width

    // Check if device is alive
    bool response = sensor.isConnected();
    if (response == true) {
        Serial.println(F("Sensor is connected."));
    } else {
        Serial.println(F("Sensor not detected. Freezing."));
        while (1)
            ;
    }

    // Set the ranging mode
    response = sensor.setRangingMode(SF_VL53L5CX_RANGING_MODE::AUTONOMOUS);
    if (response == true) {
        SF_VL53L5CX_RANGING_MODE mode = sensor.getRangingMode();
        switch (mode) {
            case SF_VL53L5CX_RANGING_MODE::AUTONOMOUS:
                Serial.println(F("Ranging mode set to autonomous."));
                break;

            case SF_VL53L5CX_RANGING_MODE::CONTINUOUS:
                Serial.println(F("Ranging mode set to continuous."));
                break;

            default:
                Serial.println(F("Error recovering ranging mode."));
                break;
        }
    } else {
        Serial.println(F("Cannot set ranging mode requested. Freezing..."));
        while (1)
            ;
    }

    // Set device to sleep mode
    response = sensor.setPowerMode(SF_VL53L5CX_POWER_MODE::SLEEP);
    if (response == true) {
        Serial.println(F("Set device to sleep mode."));
    } else {
        Serial.println(F("Cannot set device to sleep mode. Freezing..."));
        while (1)
            ;
    }

    // Check if device is actually in sleep mode
    SF_VL53L5CX_POWER_MODE currentPowerMode = sensor.getPowerMode();
    switch (currentPowerMode) {
        case SF_VL53L5CX_POWER_MODE::SLEEP:
            Serial.println(F("Shhhh... device is sleeping!"));
            break;

        case SF_VL53L5CX_POWER_MODE::WAKEUP:
            Serial.println(F("Device is awake."));
            break;

        default:
            Serial.println(F("Cannot retrieve device power mode."));
            break;
    }

    Serial.print(F("Waking up device in 5..."));
    delay(1000);
    Serial.print(F(" 4..."));
    delay(1000);
    Serial.print(F(" 3..."));
    delay(1000);
    Serial.print(F(" 2..."));
    delay(1000);
    Serial.println(F(" 1..."));
    delay(1000);

    // Wake up device
    response = sensor.setPowerMode(SF_VL53L5CX_POWER_MODE::WAKEUP);
    if (response == true) {
        Serial.println(F("Set device to wakeup mode."));
    } else {
        Serial.println(F("Cannot wakeup device. Freezing..."));
        while (1)
            ;
    }

    // Check if device is awake
    currentPowerMode = sensor.getPowerMode();
    switch (currentPowerMode) {
        case SF_VL53L5CX_POWER_MODE::SLEEP:
            Serial.println(F("Shhhh... device is sleeping!"));
            break;

        case SF_VL53L5CX_POWER_MODE::WAKEUP:
            Serial.println(F("Device is awake."));
            break;

        default:
            Serial.println(F("Cannot retrieve device power mode."));
            break;
    }

    Serial.print(F("Current integration time: "));
    Serial.print(sensor.getIntegrationTime());
    Serial.println(F("ms"));

    response = sensor.setIntegrationTime(8);
    if (response == true) {
        Serial.print(F("Current integration time: "));
        Serial.print(sensor.getIntegrationTime());
        Serial.println(F("ms"));
    } else {
        Serial.println(F("Cannot set integration time. Freezing..."));
        while (1)
            ;
    }

    Serial.print(F("Current sharpener value: "));
    Serial.print(sensor.getSharpenerPercent());
    Serial.println(F("%"));

    response = sensor.setSharpenerPercent(19);
    if (response == true) {
        Serial.print(F("Current sharpener value: "));
        Serial.print(sensor.getSharpenerPercent());
        Serial.println(F("%"));
    } else {
        Serial.println(F("Cannot set sharpener value."));
        Serial.println(F("System halted."));
        while (1) {
        }
    }

    SF_VL53L5CX_TARGET_ORDER order = sensor.getTargetOrder();
    switch (order) {
        case SF_VL53L5CX_TARGET_ORDER::STRONGEST:
            Serial.println(F("Current target order is strongest."));
            break;

        case SF_VL53L5CX_TARGET_ORDER::CLOSEST:
            Serial.println(F("Current target order is closest."));
            break;

        default:
            Serial.println(F("Cannot get target order."));
            break;
    }

    response = sensor.setTargetOrder(SF_VL53L5CX_TARGET_ORDER::CLOSEST);
    if (response == true) {
        order = sensor.getTargetOrder();
        switch (order) {
            case SF_VL53L5CX_TARGET_ORDER::STRONGEST:
                Serial.println(F("Target order set to strongest."));
                break;

            case SF_VL53L5CX_TARGET_ORDER::CLOSEST:
                Serial.println(F("Target order set to closest."));
                break;

            default:
                break;
        }
    } else {
        Serial.println(F("Cannot set target order. Freezing..."));
        while (1)
            ;
    }

    // Start/stop ranging
    response = sensor.startRanging();
    if (response == true) {
        Serial.println(F("Ranging has started."));
    } else {
        Serial.println(F("Cannot start ranging. Freezing..."));
        while (1)
            ;
    }

    // Uncomment below for testing the STOP ranging command
    /*
        delay(2000);

        // Stop ranging
        response = sensor.stopRanging();
        if (response == true)
        {
        Serial.println(F("Ranging has stopped."));
        }
        else
        {
        Serial.println(F("Cannot stop ranging. Freezing..."));
        while (1) ;
        }
    */

    sensor.startRanging();
}

void loop()
{
    // Poll sensor for new data
    if (sensor.isDataReady() == true) {
        if (sensor.getRangingData(&data))    // Read distance data into array
        {
            // The ST library returns the data transposed from zone mapping shown in datasheet
            // Pretty-print data with increasing y, decreasing x to reflect reality
            for (int y = 0; y <= imageWidth * (imageWidth - 1); y += imageWidth) {
                for (int x = imageWidth - 1; x >= 0; x--) {
                    Serial.print("\t");
                    Serial.print(data.distance_mm[x + y]);
                }
                Serial.println();
            }
            Serial.println();
        }
    }

    delay(5);    // Small delay between polling
}
