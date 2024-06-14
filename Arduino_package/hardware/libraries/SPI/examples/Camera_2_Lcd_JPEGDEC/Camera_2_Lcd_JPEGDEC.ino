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

/*******************************************************
 * This example has been modified by Realtek. The original example is written by Kevin Chen.
 *
 * This example uses another JPEG Decoder library which can also work as well to display video stream from AMB82 Mini.
 *
 * Date Modified: 19 March 2024
 *
 *******************************************************/

#include "VideoStream.h"
#include "SPI.h"
#include "AmebaILI9341.h"
// Include the jpeg decoder library
#include <JPEGDEC_Libraries/JPEGDEC.h>

long lTime;

#define CHANNEL 0

#define TFT_RESET 5
#define TFT_DC    4
#define TFT_CS    SPI_SS


AmebaILI9341 tft = AmebaILI9341(TFT_CS, TFT_DC, TFT_RESET);

#define ILI9341_SPI_FREQUENCY 50000000

VideoSetting config(VIDEO_VGA, CAM_FPS, VIDEO_JPEG, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;

int JPEGDraw(JPEGDRAW *pDraw)
{
    tft.drawBitmap(pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight, pDraw->pPixels);
    return 1;    // continue decode
} /* JPEGDraw() */

JPEGDEC jpeg;

void setup()
{
    Serial.begin(115200);

    Serial.println("TFT ILI9341 ");

    SPI.setDefaultFrequency(ILI9341_SPI_FREQUENCY);

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    tft.begin();
    tft.setRotation(1);
}

void loop()
{
    Camera.getImage(CHANNEL, &img_addr, &img_len);

    jpeg.openFLASH((uint8_t *)img_addr, img_len, JPEGDraw);
    jpeg.decode(0, 0, JPEG_SCALE_HALF);
    jpeg.close();
}
