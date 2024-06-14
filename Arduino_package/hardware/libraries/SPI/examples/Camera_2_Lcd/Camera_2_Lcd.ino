/*******************************************************
 * Camera_2_Lcd.ino - Camera to TFT LCD
 *
 * Author: Kevin Chen
 * Date: 2023/11/16
 *
 * Version: 1.0.0
 *
 * This code was written by Kevin Chen.
 *
 * This is an open-source program, and it can be freely used, modified, and distributed under the following conditions:
 *
 * 1. The original copyright notice must not be removed or modified.
 * 2. Projects or products using this code must acknowledge the original author's name and the source in applicable documentation, websites, or other related materials.
 * 3. Any derivative work based on this code must state its origin and retain the original copyright notice in its documentation.
 * 4. This code must not be used for any activities that may infringe upon the rights of others, be unlawful, or harmful, whether in a commercial or non-commercial environment.
 *
 * This code is provided "as is" with no warranty, expressed or implied. The author is not liable for any losses or damages caused by using the code.
 *
 * Users of Camera_2_Lcd.ino assume all risks associated with its use, and the author shall not be held responsible for any consequences.
 *
 * For more information about our company, please visit: www.makdev.net
 *
 *  1.Based on AmebaILI9341.h, implement the functionality to display Camera output on TFT LCD and utilize the SD Card feature to achieve basic photo capture.
 *
 *  2.Before starting the project, please install the TJpg_Decoder library. In the library's configuration file, User_Config.h, comment out line 5 which reads: #define TJPGD_LOAD_SD_LIBRARY
 *******************************************************/

#include "VideoStream.h"
#include "SPI.h"
#include "AmebaILI9341.h"
// Include the jpeg decoder library
#include "TJpg_Decoder.h"
#include "AmebaFatFS.h"

#define CHANNEL 0

#define TFT_RESET 5
#define TFT_DC    4
#define TFT_CS    SPI_SS

#define FILENAME "ximg_"

AmebaILI9341 tft = AmebaILI9341(TFT_CS, TFT_DC, TFT_RESET);

#define ILI9341_SPI_FREQUENCY 20000000

VideoSetting config(VIDEO_VGA, CAM_FPS, VIDEO_JPEG, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;

AmebaFatFS fs;
int button = 16;
int button_State = 0;
bool Camer_cap;
uint32_t count;

void button_Handler(uint32_t id, uint32_t event)
{
    if (button_State == 0) {
        button_State = 1;
    }
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    tft.drawBitmap(x, y, w, h, bitmap);

    // Return 1 to decode next block
    return 1;
}

void setup()
{
    Serial.begin(115200);

    Serial.println("TFT ILI9341 ");

    SPI.setDefaultFrequency(ILI9341_SPI_FREQUENCY);
    pinMode(button, INPUT_IRQ_FALL);
    digitalSetIrqHandler(button, button_Handler);

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    tft.begin();
    tft.setRotation(1);

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(2);


    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);
}

void loop()
{
    Camera.getImage(CHANNEL, &img_addr, &img_len);
    if (button_State == 1) {
        fs.begin();
        File file = fs.open(String(fs.getRootPath()) + String(FILENAME) + String(count) + String(".jpg"));
        file.write((uint8_t *)img_addr, img_len);
        delay(1);
        file.close();
        fs.end();
        count++;
        button_State = 0;
    }

    TJpgDec.getJpgSize(0, 0, (uint8_t *)img_addr, img_len);
    TJpgDec.drawJpg(0, 0, (uint8_t *)img_addr, img_len);
}
