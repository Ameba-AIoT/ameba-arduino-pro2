/*
  This example shows how to calibrate SparkFun NAU7802 (external calibration).

  Modified by: Realtek SG (27 January 2026)

  Example Guide:
  *To be added*

  #####

  Use the Qwiic Scale to read load cells and scales
  By: Paul Clark @ SparkFun Electronics
  Date: February 25th, 2024
  License: MIT - see License.md for more details.

  This example shows how to setup a scale complete with zero offset (tare),
  and linear calibration using the NAU7802's external calibration mode.

  This is similar to Example2, except here we use the NAU7802's external
  calibration function and internal offset register to store the zero point. By
  default .begin performs an _internal_ calibration. In this example we
  overwrite the offset register with the result of the _external_ calibration.

  If you know the calibration and offset values you can send them directly to
  the library and NAU7802. This is useful if you want to maintain values between
  power cycles in EEPROM or Non-volatile memory (NVM). If you don't know these
  values then you can go through a series of steps to calculate the offset and
  calibration value.

  SparkFun labored with love to create this code. Feel like supporting open
  source? Buy a board from SparkFun!
  https://www.sparkfun.com/products/15242

  Hardware Connections:
  Plug a Qwiic cable into the Qwiic Scale and a RedBoard Qwiic
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic
  Breadboard Jumper (https://www.sparkfun.com/products/14425) Open the serial
  monitor at 115200 baud to see the output
*/

#include <Wire.h>

#include "SparkFun_NAU7802_libraries/SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

NAU7802 myScale;    // Create instance of the NAU7802 class

bool settingsDetected = false;    // Used to prompt user to calibrate their scale

// Average the weight over this many samples. This helps smooth out jitter.
const uint8_t avgWeights = 20;    // At 40 SPS, this will produce readings at 2Hz

// Allow negative weights. Why not?
const bool allowNegative = true;

void setup()
{
    delay(1000);    // Some platforms need this. Comment this line if needed

    Serial.begin(115200);
    Serial.println(F("Qwiic Scale Example"));

    Wire.begin();
    Wire.setClock(
        400000);    // Qwiic Scale is capable of running at 400kHz if desired

    if (myScale.begin() == false)    // begin performs an internal calibration.
    {
        Serial.println(F("Scale not detected. Please check wiring. Freezing..."));
        while (1)
            ;
    }
    Serial.println(F("Scale detected!"));

    myScale.setSampleRate(
        NAU7802_SPS_40);    // Set sample rate: 10, 20, 40, 80 or 320
    myScale.setGain(
        NAU7802_GAIN_16);               // Gain can be set to 1, 2, 4, 8, 16, 32, 64, or 128.
    myScale.setLDO(NAU7802_LDO_3V0);    // Set LDO (AVDD) voltage. 3.0V is the best
                                        // choice for Qwiic

    Serial.print(F("NAU7802 offset register: "));
    Serial.println(myScale.getChannel1Offset());
    Serial.print(F("Library calibration factor: "));
    Serial.println(myScale.getCalibrationFactor());

    Serial.println(F("\r\nPress 'c' to calibrate the scale\r\n"));
}

void loop()
{
    if (myScale.available() == true) {
        float currentWeight = myScale.getWeight(allowNegative, avgWeights);

        Serial.print(F("NAU7802 reading: "));
        Serial.print(currentWeight, 2);    // Print 2 decimal places

        if (settingsDetected == false) {
            Serial.print(F("\tScale not calibrated. Press 'c'."));
        }

        Serial.println();
    }

    if (Serial.available()) {
        byte incoming = Serial.read();

        if (incoming == 'c') {    // Calibrate
            calibrateScale();
        }
    }
}

// Gives user the ability to set a known weight on the scale and calculate a
// calibration factor
void calibrateScale(void)
{
    Serial.println();
    Serial.println();
    Serial.println(F("Scale calibration"));

    Serial.println(
        F("Setup scale with no weight on it. Press a key when ready."));
    while (Serial.available()) {
        Serial.read();    // Clear anything in RX buffer
    }
    while (Serial.available() == 0) {
        delay(10);    // Wait for user to press key
    }

    // Perform an external offset - this sets the NAU7802's internal offset
    // register
    myScale.calibrateAFE(NAU7802_CALMOD_OFFSET);    // Calibrate using external
                                                    // offset

    Serial.print(F("New NAU7802 offset register: "));
    Serial.println(myScale.getChannel1Offset());

    Serial.println(F("Place known weight on scale. Press a key when weight is in "
                     "place and stable."));
    while (Serial.available()) {
        Serial.read();    // Clear anything in RX buffer
    }
    while (Serial.available() == 0) {
        delay(10);    // Wait for user to press key
    }

    Serial.print(F("Please enter the weight, without units, currently sitting on "
                   "the scale (for example '4.25'): "));
    while (Serial.available()) {
        Serial.read();    // Clear anything in RX buffer
    }
    while (Serial.available() == 0) {
        delay(10);    // Wait for user to press key
    }

    // Read user input
    float weightOnScale = Serial.parseFloat();
    Serial.println();

    // Tell the library how much weight is currently on it
    // We are sampling slowly, so we need to increase the timeout too
    myScale.calculateCalibrationFactor(
        weightOnScale, 64,
        3000);    // 64 samples at 40SPS. Use a timeout of 3 seconds
    Serial.print(F("Weight on scale: "));
    Serial.println(weightOnScale, 2);
    Serial.print(F("New library calibration factor: "));
    Serial.println(myScale.getCalibrationFactor(), 2);

    settingsDetected = true;    // Mark the settings as detected
}
