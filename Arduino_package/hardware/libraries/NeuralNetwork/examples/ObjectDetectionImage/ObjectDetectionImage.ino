/*

This sketch performs object detection for single image saved on SD card.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Neural%20Network/Object%20Detection%20Image.html
*/
#include "NNObjectDetectionImage.h"

NNObjectDetectionImage ObjDetImg;

char filelist_name[] = "image_list.txt";    // modify according to image name list

void setup()
{
    Serial.begin(115200);
    ObjDetImg.modelSelect(OBJECT_DETECTION, DEFAULT_YOLOV4TINY, NA_MODEL, NA_MODEL);
    ObjDetImg.begin(filelist_name);
}

void loop()
{
    // do nothing
}
