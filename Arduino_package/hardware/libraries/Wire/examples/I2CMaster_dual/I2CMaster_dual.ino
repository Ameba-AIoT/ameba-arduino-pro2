/*
 I2C Master using Wire library for AmebaPro2

 This example demonstrates I2C master communication using the standard
 Arduino Wire library on AmebaPro2 boards.

 Hardware connections:
    Master (this board)     Slave (other AmebaPro2 board)
    SDA (pin 12) ---------> SDA (pin 12)
    SCL (pin 13) ---------> SCL (pin 13)
    GND  -----------------> GND

 This sketch:
 1. Sends 127 bytes of data to the slave
 2. Requests 127 bytes of data from the slave
 3. Prints results to Serial

 Slave address: 0x08
 I2C clock: 100000 Hz (100 kHz)

 Example guide: TBD
*/

#include <Wire.h>

#define SLAVE_ADDR  0x08
#define DATA_LENGTH 127

// Data buffers
uint8_t txData[DATA_LENGTH];
uint8_t rxData[DATA_LENGTH];

void setup()
{
    Serial.begin(115200);
    while (!Serial);    // Wait for Serial port to connect
    Serial.println("\r\n========================================");
    Serial.println("AmebaPro2 I2C Master (Wire Library)");
    Serial.println("========================================");

    // Initialize I2C as master
    Wire.begin();
    Wire.setClock(100000);
    Serial.println("I2C Master initialized at 100 kHz");

    // Prepare transmit data: 0x02, 0x03, 0x04, ... 0x80
    for (int i = 0; i < DATA_LENGTH; i++) {
        txData[i] = i + 0x02;
    }

    // Clear receive buffer
    memset(rxData, 0, DATA_LENGTH);

    // Give slave time to initialize
    delay(500);

    // ==========================================
    // Step 1: Master writes data to slave
    // ==========================================
    Serial.println("\r\n--- Step 1: Master Write to Slave ---");
    Wire.beginTransmission(SLAVE_ADDR);
    for (int i = 0; i < DATA_LENGTH; i++) {
        Wire.write(txData[i]);
    }
    uint8_t error = Wire.endTransmission(true);    // Send with STOP

    if (error == 0) {
        Serial.println("Master write completed successfully");
    } else {
        Serial.print("Master write failed with error code: ");
        Serial.println(error);
    }

    // Wait for slave to process the received data
    delay(500);

    // ==========================================
    // Step 2: Master reads data from slave
    // ==========================================
    Serial.println("\r\n--- Step 2: Master Read from Slave ---");
    uint8_t bytesRead = Wire.requestFrom(SLAVE_ADDR, DATA_LENGTH);

    if (bytesRead > 0) {
        Serial.print("Received ");
        Serial.print(bytesRead);
        Serial.println(" bytes from slave");

        // Read all received bytes
        int idx = 0;
        while (Wire.available() > 0 && idx < DATA_LENGTH) {
            char c = Wire.read();
            rxData[idx++] = c;
            Serial.print("0x");
            if (c < 0x10) {
                Serial.print("0");
            }
            Serial.println(c, HEX);
        }

        // Verify received data
        bool success = true;
        for (int i = 0; i < DATA_LENGTH; i++) {
            if (rxData[i] != (i + 1)) {    // Slave sends 0x01, 0x02, ... 0x7F
                success = false;
                Serial.print("Mismatch at index ");
                Serial.print(i);
                Serial.print(": expected 0x");
                Serial.print(i + 1, HEX);
                Serial.print(", got 0x");
                Serial.println(rxData[i], HEX);
                break;
            }
        }

        if (success) {
            Serial.println("Master receive: Result is success");
        } else {
            Serial.println("Master receive: Result is fail");
        }
    } else {
        Serial.println("No data received from slave");
    }

    Serial.println("\r\n========================================");
    Serial.println("Test complete");
    Serial.println("========================================");
}

void loop()
{
    // Nothing to do here
    delay(1000);
}
