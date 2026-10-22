#include <USBHostCDC.h>
#include <MI48Protocol.h>

USBHostCDC cdc;
MI48Protocol mi48;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("Starting USB Host CDC...");

    if (!cdc.begin()) {
        Serial.println("USBHostCDC.begin() failed");
        while (1) {
            delay(1000);
        }
    }

    Serial.println("Waiting for MI48...");

    if (!mi48.begin(cdc, 10000)) {
        Serial.println("MI48Protocol.begin() failed");
        while (1) {
            delay(1000);
        }
    }

    Serial.println("MI48 streaming");
}

void loop()
{
    // Keep this running frequently. One GFRA payload is about 39.7 KB.
    mi48.poll();

    if (!mi48.frameAvailable()) {
        delay(1);
        return;
    }

    uint32_t payloadLen = 0;
    const uint8_t *frame = mi48.getFrame(&payloadLen);

    if (frame != nullptr) {
        Serial.print("GFRA frame: ");
        Serial.print(payloadLen);
        Serial.print(" bytes, USB dropped=");
        Serial.println(cdc.droppedBytes());
    }
}
