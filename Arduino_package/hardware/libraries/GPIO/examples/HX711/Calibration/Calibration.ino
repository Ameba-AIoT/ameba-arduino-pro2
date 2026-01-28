/*
This example shows how to calibrate SparkFun HX711 to get actual reading (in grams) using a load cell.

Prepared by: Realtek SG (22 January 2026)

Example Guide:
*To be added*
*/

#include "HX711.h"

// Define HX711 pins
const int HX711_DAT_PIN = 2;
const int HX711_CLK_PIN = 3;

// Define HX711 instance
HX711 loadCell;

// Default calibration value (will be updated)
float savedCalibration = 1.0;

void setup()
{
    Serial.begin(115200);

    // Set up pins
    loadCell.begin(HX711_DAT_PIN, HX711_CLK_PIN);
    delay(1000);

    // Set initial calibration
    loadCell.set_scale(savedCalibration);
    delay(1000);

    // Tare, i.e., zero the scale
    loadCell.tare();
    delay(1000);

    if (!loadCell.is_ready()) {
        Serial.println("HX711 not found. Check wiring!");
    } else {
        Serial.println("Setup completed");
    }

    // Wait for HX711 to be ready
    while (!loadCell.is_ready()) {
        delay(1000);
    }

    // Trigger calibration procedure
    calibrate();
}

void loop()
{
    // Print every 1000ms
    static unsigned long lastPrint = 0;
    const int printInterval = 1000;
    if (loadCell.is_ready()) {
        if (millis() - lastPrint > printInterval) {
            float weight = loadCell.get_units(5);
            Serial.print("Weight: ");
            Serial.print(weight, 1);
            Serial.println(" g");
            lastPrint = millis();
        }
    }

    // Receive command from serial terminal
    if (Serial.available() > 0) {
        char inByte = Serial.read();
        if (inByte == 't') {
            Serial.println("Taring...");
            loadCell.tare();
            delay(1000);
            Serial.println("Tare complete");
        } else if (inByte == 'r') {
            // Recalibrate
            calibrate();
        } else if (inByte == 'c') {
            // Manually change calibration factor
            changeCalibration();
        }
    }
}

void calibrate()
{
    Serial.print("\n\n==========================\n");
    Serial.print("START CALIBRATION");
    Serial.print("\n==========================\n\n");


    Serial.print("Step 1: Place the load cell on a level stable surface.\n\n");
    Serial.println("- Remove any load from the load cell.");
    Serial.println("- Send 't' from serial monitor to tare.");
    boolean resume = false;
    while (!resume) {
        if (Serial.available() > 0) {
            char inByte = Serial.read();
            if (inByte == 't') {
                loadCell.tare();
                delay(1000);
                Serial.println("Tare completed");
                resume = true;
            }
        }
    }

    Serial.print("\nStep 2: Measure the weight of a known mass on the load cell.\n\n");
    Serial.println("- Place the known mass on the load cell.");
    Serial.println("- Send the weight in grams (e.g., 1000.0) from serial monitor to calculate the calibration factor.");
    float known_mass = 0;
    resume = false;
    while (!resume) {
        if (Serial.available() > 0) {
            known_mass = Serial.parseFloat();
            if (known_mass != 0) {
                Serial.print("- Received known mass: ");
                Serial.print(known_mass);
                Serial.println(" g");
                resume = true;
            }
        }
    }

    Serial.println("- Reading scale...");
    loadCell.set_scale(1.0);
    delay(1000);

    // Get average reading with known weight, based on n=30 readings
    long raw_reading = loadCell.get_value(30);

    // Calculate new calibration factor
    float newCalibration = raw_reading / known_mass;
    Serial.println();
    Serial.print("NEW CALIBRATION VALUE: ");
    Serial.println(newCalibration, 2);
    Serial.println();

    Serial.println("- Add this to your code at ~ line 20 for future reference:");
    Serial.print("  - savedCalibration = ");
    Serial.print(newCalibration, 2);
    Serial.println(";");

    // Apply the new calibration
    loadCell.set_scale(newCalibration);
    savedCalibration = newCalibration;

    Serial.print("\nStep 3: Re-Tare to ensure 0 reading.\n\n");
    Serial.println("- Remove the known mass from the load cell.");
    Serial.println("- Send 't' from serial monitor to re-tare.");

    resume = false;
    while (!resume) {
        if (Serial.available() > 0) {
            char inByte = Serial.read();
            if (inByte == 't') {
                loadCell.tare();
                Serial.println("✓ Scale zeroed! Empty scale now reads 0g");
                resume = true;
            }
        }
    }

    Serial.println();
    Serial.print("\n\n==========================\n");
    Serial.print("CALIBRATION COMPLETED");
    Serial.print("\n==========================\n\n");
    Serial.println("Commands:");
    Serial.println("  't' - Tare (zero) the scale");
    Serial.println("  'r' - Re-calibrate");
    Serial.println("  'c' - Manually change calibration value");
}

void changeCalibration()
{
    float currentCal = savedCalibration;

    Serial.print("\n\n==========================\n\n");
    Serial.print("CHANGE CALIBRATION FACTOR");
    Serial.print("\n\n==========================\n\n");
    Serial.print("Current calibration: ");
    Serial.println(currentCal, 2);
    Serial.println("Enter new calibration value:");

    boolean resume = false;

    float newCal = 0;
    while (!resume) {
        if (Serial.available() > 0) {
            newCal = Serial.parseFloat();
            if (newCal != 0) {
                Serial.print("New calibration: ");
                Serial.println(newCal, 2);
                loadCell.set_scale(newCal);
                savedCalibration = newCal;
                resume = true;
            }
        }
    }

    Serial.print("\n\n==========================");
    Serial.print("CALIBRATION FACTOR CHANGED");
    Serial.print("==========================\n\n");
    Serial.println("Add this to your code at ~ line 20 for future reference:");
    Serial.print("  savedCalibration = ");
    Serial.print(savedCalibration, 2);
    Serial.println(";");
}
// ```

// ---

// ## **How to use this:**

// ### **Step 1: Upload and run**
// Upload this code to your AmebaPro2

// ### **Step 2: Follow the calibration process**
// ```
// 1. Remove all weight
// 2. Type 't' and press Enter → Tares the scale
// 3. Place known weight (e.g., 1000g)
// 4. Type the weight: 1000
// 5. Press Enter
// ```

// ### **Step 3: Get your calibration value**
// The output will show something like:
// ```
// ==========================
// New calibration value: 262.45
// ==========================

// Add this to your code:
//   savedCalibration = 262.45;
