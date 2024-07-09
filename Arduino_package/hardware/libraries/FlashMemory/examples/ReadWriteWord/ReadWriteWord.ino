/*
 This sketch shows how to request flash memory read/write one specific word.

 Example guide: TBD
 */

#include <FlashMemory.h>

void setup()
{
    Serial.begin(115200);

    unsigned int value;
    unsigned int check_value;

    /* request flash size 0x1000 from FLASH_MEMORY_APP_BASE */
    FlashMemory.begin(FLASH_MEMORY_APP_BASE, 0x1000);

    /* read one word (32-bit) from FLASH_MEMORY_APP_BASE plus offset 0x1E00 */
    value = FlashMemory.readWord(0x1E00);
    Serial.println();
    Serial.print("Read value is ");
    Serial.println(value, HEX);

    if (value == 0xFFFFFFFF) {
        value = 0;
    } else {
        value++;
    }

    /* write one word (32-bit) to FLASH_MEMORY_APP_BASE plus offset 0x1F00 */
    Serial.print("Write value is ");
    Serial.println(value, HEX);
    FlashMemory.writeWord(0x1E00, value);

    check_value = FlashMemory.readWord(0x1E00);
    if (check_value == value) {
        Serial.println("Success! Read and Write flash memory by word.");
    } else {
        Serial.println("Error! Read and Write flash memory by word.");
    }
}

void loop()
{
    delay(1000);
}
