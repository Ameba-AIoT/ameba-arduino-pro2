/*
 Demonstrates use of the Wire library
 Receives data as an I2C/TWI slave device on AMB82-mini

 Reference to Wire Slave Receiver by Nicholas Zambetti <http://www.zambetti.com>.
 This example code is in the public domain.

 modified 15 May 2026
 by Realtek SG

 Example guide: TBD
*/

#include <Wire.h>

#define DATA_LENGTH 6

// Buffer for data received from master
uint8_t slaveRxData[DATA_LENGTH];
volatile int rxDataCount = 0;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;    // Wait for Serial port to connect
    Serial.println("\r\n========================================");
    Serial.println("AmebaPro2 I2C Slave Receiver");
    Serial.println("========================================");

    // Initialize as I2C slave with address 0x08
    Wire.begin(0x08);

    // // Register callbacks
    Wire.onReceive(receiveEvent);

    Serial.println("I2C Slave ready at address 0x08");
    Serial.println("Waiting for master communication...");
    Wire.slaveReadLen(DATA_LENGTH);
    Wire.available();    // Start listening for master (calls onReceive when data
                         // arrives)
    delay(10);
}

void loop()
{
    // Poll Wire.available() to check for incoming data from master.
    // This calls i2c_slave_receive() internally to check state.
    // When state=1 (data available), it reads the data and calls onReceive.
    // State=2 (read request) is handled by the hardware callback.
    // Wire.available();
    delay(10);
}

// Called when master sends data to this slave
void receiveEvent(int numBytes)
{
    while (1) {
        // Serial.print("\r\n[onReceive] Received ");
        // Serial.print(numBytes);
        // Serial.println(" bytes from master:");

        // Read all available bytes
        int idx = 0;
        while (Wire.available() > 1) {
            char c = Wire.read();
            slaveRxData[idx++] = c;
            Serial.print(c);
        }
        int x = Wire.read();
        Serial.println(x);
        delay(500);
        Wire.slaveClrRxFlag();
    }
}
