/*

This sketch performs object detection for single image saved on SD card.

Example guide: TBD

*/
#include "NNObjectDetectionImage.h"

NNObjectDetectionImage ObjDetImg;

char filelist_name[] = "image_list.txt"; // modify according to image name list

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