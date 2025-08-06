/*
 This sketch shows how to request flash memory read/write one specific word.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Flash%20Memory/Read%20Write%20Word.html
*/

#include <FlashMemory.h>

/* Suggest 1 - 9 */
#define RESET_THRESHOLD 9

void setup()
{
    Serial.begin(115200);

    unsigned int value;
    unsigned int check_value;

    /* request flash size 0x1000 from FLASH_MEMORY_APP_BASE */
    FlashMemory.begin(FLASH_MEMORY_APP_BASE, 0x1000);

    /* read one word (32-bit) from FLASH_MEMORY_APP_BASE plus offset 0x1E00*/
    value = FlashMemory.readWord(0x1E00) & 0xF;
    if (value > 9) {
        FlashMemory.writeWord(0x1E00, 0);
    }

    Serial.println();
    Serial.print("Read value is ");
    Serial.println(value, DEC);

    if ((value % 10) == RESET_THRESHOLD) {
        value = 0;
    } else {
        value++;
    }

    /* write one word (32-bit) to FLASH_MEMORY_APP_BASE plus offset 0x1F00 */
    Serial.print("Write value is ");
    Serial.println(value, DEC);
    FlashMemory.writeWord(0x1E00, value);

    check_value = FlashMemory.readWord(0x1E00);
    if (check_value == value) {
        Serial.println("Success!");
    } else {
        Serial.println("Error!");
    }
}

void loop()
{
    delay(1000);
}
