/*
  I2C Slave using Wire library for AmebaPro2

  This example demonstrates I2C slave communication using the standard
  Arduino Wire library on AmebaPro2 boards.

  Hardware connections:
    Slave (this board)      Master (other AmebaPro2 board)
    SDA (pin 12) ---------> SDA (pin 12)
    SCL (pin 13) ---------> SCL (pin 13)
    GND  -----------------> GND

  This sketch:
  1. Listens for incoming data from the master (onReceive callback)
  2. Prepares data when master requests it (onRequest callback)
  3. Prints results to Serial

  Slave address: 0x08

  Example guide: TBD
*/

#include <Wire.h>

#define DATA_LENGTH 127

// Buffer for data to send when master requests
uint8_t slaveTxData[DATA_LENGTH];

// Buffer for data received from master
uint8_t slaveRxData[DATA_LENGTH];
volatile int rxDataCount = 0;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;    // Wait for Serial port to connect
    Serial.println("\r\n========================================");
    Serial.println("AmebaPro2 I2C Slave (Wire Library)");
    Serial.println("========================================");

    // Prepare data to send when master requests: 0x01, 0x02, ... 0x7F
    for (int i = 0; i < DATA_LENGTH; i++) {
        slaveTxData[i] = i + 1;
    }

    // Initialize as I2C slave with address 0x08
    Wire.begin(0x08);

    // // Register callbacks
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    Serial.println("I2C Slave ready at address 0x08");
    Serial.println("Waiting for master communication...");
    Wire.slaveReadLen(DATA_LENGTH);
    Wire.available();    // Start listening for master (calls onReceive when data arrives)
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
    Serial.print("\r\n[onReceive] Received ");
    Serial.print(numBytes);
    Serial.println(" bytes from master:");

    // Read all available bytes
    int idx = 0;
    while (Wire.available() > 0 && idx < numBytes) {
        char c = Wire.read();
        slaveRxData[idx++] = c;
        Serial.print("0x");
        if (c < 0x10) {
            Serial.print("0");
        }
        Serial.print(c, HEX);
        Serial.print(" ");
    }
    Serial.println();
    rxDataCount = idx;

    // Verify received data (master sends 0x02, 0x03, ... 0x80)
    bool success = true;
    for (int i = 0; i < idx; i++) {
        if (slaveRxData[i] != (i + 0x02)) {
            success = false;
            Serial.print("Mismatch at index ");
            Serial.print(i);
            Serial.print(": expected 0x");
            Serial.print(i + 0x02, HEX);
            Serial.print(", got 0x");
            Serial.println(slaveRxData[i], HEX);
            break;
        }
    }

    if (success) {
        Serial.println("Slave receive: Result is success");
    } else {
        Serial.println("Slave receive: Result is fail");
    }
    Serial.println("Slave reply");
    Wire.slaveWrite();
}

// Called when master requests data from this slave
void requestEvent()
{
    Serial.println("\r\n[onRequest] Master is requesting data");

    // Write the prepared data to the master
    Wire.write(slaveTxData, DATA_LENGTH);
    Serial.print("Sent ");
    Serial.print(DATA_LENGTH);
    Serial.println(" bytes to master");
}
