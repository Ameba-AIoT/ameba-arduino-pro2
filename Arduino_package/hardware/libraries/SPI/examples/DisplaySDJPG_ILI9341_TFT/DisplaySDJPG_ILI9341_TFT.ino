/*

 This sketch shows the example of displaying jpg image from micro SD card on ILI9341 TFT display module.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/SPI/Display%20SD%20JPG%20ILI9341%20TFT.html

*/

#include "SPI.h"
#include "AmebaILI9341.h"
// Include the jpeg decoder library
#include "TJpg_Decoder.h"
#include "AmebaFatFS.h"

#define TFT_RESET 5
#define TFT_DC    4
#define TFT_CS    SPI_SS

#define ILI9341_SPI_FREQUENCY 20000000

AmebaILI9341 tft = AmebaILI9341(TFT_CS, TFT_DC, TFT_RESET);

AmebaFatFS fs;

String filename = "image-0001.jpg";    // modify according to saved jpg image name

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    tft.drawBitmap(x, y, w, h, bitmap);

    // Return 1 to decode next block
    return 1;
}

void setup()
{
    Serial.begin(115200);

    Serial.println("TFT ILI9341");

    SPI.setDefaultFrequency(ILI9341_SPI_FREQUENCY);

    tft.begin();
    tft.setRotation(0);

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(2);

    tft.clr();
    tft.setCursor(0, 0);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);

    fs.begin();
    String file_path = String(fs.getRootPath());
    if (fs.exists(file_path + "/" + filename)) {
        File file = fs.open(file_path + "/" + filename);

        unsigned char *file_data;
        uint32_t file_size;
        if (file.readFile(file_data, file_size)) {
            TJpgDec.getJpgSize(0, 0, (const uint8_t *)file_data, file_size);
            TJpgDec.drawJpg(0, 0, (const uint8_t *)file_data, file_size);
            free(file_data);
        } else {
            Serial.println("Failed to get JPG data.");
        }
        file.close();
    } else {
        Serial.println("File does not exist.");
    }
    fs.end();
}

void loop()
{
    // put your main code here, to run repeatedly:
}
