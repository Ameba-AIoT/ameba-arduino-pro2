/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/WS2812B/WS2812B%20-%20Basics.html
 */

#include "WS2812B.h"

#define TOTAL_NUM_OF_LED 16
#define NUM_OF_LEDS      8

WS2812B led(SPI_MOSI, TOTAL_NUM_OF_LED);

void setup()
{
    Serial.begin(115200);
    Serial.println("WS2812B test");
    led.begin();
    // Set a specific LED with a certain color
    led.setPixelColor(0, 50, 0, 0);
    led.setPixelColor(1, 0, 50, 0);
    led.setPixelColor(2, 0, 0, 50);
    led.show();
    delay(1000);
    // Fill the entire LED strip with the same color
    led.fill(60, 0, 25, 0, NUM_OF_LEDS);
    led.show();
}

void loop()
{
    delay(500);
}
