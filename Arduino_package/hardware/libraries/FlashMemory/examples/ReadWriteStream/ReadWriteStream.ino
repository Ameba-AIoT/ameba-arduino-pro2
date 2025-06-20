/*
 This sketch shows how to request flash memory read/write stream word.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Flash%20Memory/Read%20Write%20Stream.html
*/

#include <FlashMemory.h>

#define TEST_SIZE       0x1000
#define RESET_THRESHOLD 5

void setup()
{
    Serial.begin(115200);

    FlashMemory.begin(FLASH_MEMORY_APP_BASE, TEST_SIZE);
    FlashMemory.read();

    int i;
    if (FlashMemory.buf[0] >= RESET_THRESHOLD) {
        for (i = 0; i < TEST_SIZE; i++) {
            FlashMemory.buf[i] = 0x00;
        }
        Serial.print("Reset count to 0");
    } else {
        for (i = 0; i < TEST_SIZE; i++) {
            FlashMemory.buf[i]++;
        }
        Serial.print("Boot count: ");

        for (i = 0; i < (TEST_SIZE - 1); i++) {
            if (FlashMemory.buf[i] != FlashMemory.buf[i + 1]) {
                Serial.print("error at ");
                Serial.print(i);
                Serial.print(" value ");
                break;
            }
        }
        Serial.println(FlashMemory.buf[i]);
    }
    FlashMemory.write();
}

void loop()
{
    delay(1000);
}
