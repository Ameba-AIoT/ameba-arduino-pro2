/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.

 Modified by Realtek SG SD3 13/02/2024
 **************************************************************************/

#include <Wire.h>
#include <Adafruit_OLED_libraries/Adafruit_GFX.h>
#include <Adafruit_OLED_libraries/Adafruit_SSD1306.h>

#define SCREEN_WIDTH  128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
#define OLED_RESET     -1      // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D    ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10    // Number of snowflakes in the animation example

// Realtek logo
#define LOGO_HEIGHT 64
#define LOGO_WIDTH  64
static const unsigned char PROGMEM logo_bmp[] =
    {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B01110000, B01110000, B00000000, B00000000, B00000111, B00000111, B00000000,
     B00000000, B01110000, B01110000, B00000000, B00000000, B00000111, B00000111, B00000000,
     B00000000, B01110000, B01110000, B00000000, B00000000, B00000111, B00000111, B00000000,
     B00000000, B01111001, B11110000, B00000000, B00000000, B00000111, B11001111, B00000000,
     B00000000, B01111001, B11110000, B00000000, B00000000, B00000111, B11001111, B00000000,
     B00000000, B01111101, B11110000, B00000000, B00000000, B00000111, B11011111, B00000000,
     B00000000, B01111111, B11110000, B00000000, B00000000, B00000111, B11111111, B00000000,
     B00000000, B01111111, B11110000, B00000000, B00000000, B00000111, B11111111, B00000000,
     B00000000, B01111111, B11110000, B00000000, B00000000, B00000111, B11111111, B00000000,
     B00000000, B00001111, B10000000, B00000000, B00000000, B00000000, B11111000, B00000000,
     B00000000, B00001111, B10000000, B00000000, B00000000, B00000000, B11111000, B00000000,
     B00000000, B00001111, B10000000, B00000000, B00000000, B00000000, B11111000, B00000000,
     B00000000, B00001111, B10000000, B00000000, B00000000, B00000000, B11111000, B00000000,
     B00000000, B00001111, B10000000, B00111100, B00011110, B00000000, B11111000, B00000000,
     B00000000, B00001111, B11000000, B00111100, B00011110, B00000001, B11111000, B00000000,
     B00000000, B00001111, B11100000, B00111100, B00011110, B00000011, B11111000, B00000000,
     B00000000, B00001111, B11110000, B00111100, B00011110, B00000111, B11111000, B00000000,
     B00000000, B00000111, B11111000, B00011000, B00001100, B00001111, B11110000, B00000000,
     B00000000, B00000011, B11111100, B00001000, B00001100, B00011111, B11100000, B00000000,
     B00000000, B00000001, B11111110, B00001000, B00001100, B00111111, B11000000, B00000000,
     B00000000, B00000000, B11111110, B00001000, B00001100, B00111111, B10000000, B00000000,
     B00000000, B00000000, B01111110, B00001000, B00001100, B00111111, B00000000, B00000000,
     B00000000, B00000000, B01111110, B00001111, B11111100, B00111111, B00000000, B00000000,
     B00000000, B00000000, B01111110, B00000000, B00000000, B00111111, B00000000, B00000000,
     B00000000, B00000000, B01111110, B00000000, B00000000, B00111111, B00000000, B00000000,
     B00000000, B00000000, B01111110, B00000000, B00000000, B00111111, B00000000, B00000000,
     B00000000, B00000000, B01111111, B11110000, B00000111, B11111100, B00000000, B00000000,
     B00000000, B00000000, B00111111, B11111000, B00001111, B11111100, B00000000, B00000000,
     B00000000, B11111111, B10111111, B11111100, B00011111, B11111101, B11111111, B00000000,
     B00000001, B11000000, B00111111, B11111110, B00111111, B11111100, B00000011, B00000000,
     B00000001, B10000000, B00111111, B11111111, B00111111, B11111000, B00000001, B10000000,
     B00000011, B00011111, B10110000, B11111111, B11111110, B00000001, B11111000, B11000000,
     B00000110, B00111111, B00111111, B11111111, B11111110, B00000001, B11111100, B01100000,
     B00000110, B01110000, B00111111, B11111111, B11111110, B00000000, B00001110, B01100000,
     B00000100, B11100000, B00111111, B11111011, B11101110, B00000000, B00000110, B00100000,
     B00000100, B11000111, B10111011, B11111001, B11001110, B00000001, B11110011, B00100000,
     B00000100, B10001111, B00110001, B11111000, B10001110, B00000000, B11110011, B00100000,
     B00000100, B10011000, B00110001, B11111000, B00001110, B00000000, B00011001, B00100000,
     B00000100, B10010001, B10110001, B11111000, B00001110, B00000001, B10001101, B00100000,
     B00000100, B10010011, B10110000, B11111000, B00001111, B00000001, B11001101, B00100000,
     B00000000, B10010010, B00110000, B11111000, B00001111, B11111000, B01001101, B00000000,
     B00000000, B10010010, B00110000, B11111000, B00001111, B11111000, B01001101, B00000000,
     B00000000, B00010010, B00000000, B00000000, B00000000, B00000000, B01001100, B00000000,
     B00000000, B00010010, B00000000, B00000000, B00000000, B00000000, B01001100, B00000000,
     B00000000, B00000010, B00000000, B00000000, B00000000, B00000000, B01000000, B00000000,
     B00000000, B00000010, B00000000, B00000000, B00000000, B00000000, B01000000, B00000000,
     B00000000, B00000010, B00000000, B00000000, B00000000, B00000000, B01000000, B00000000,
     B00111111, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00111001, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00111000, B11000111, B11100000, B10000001, B10000111, B11110011, B11100011, B00001000,
     B00011000, B11100110, B00000000, B11000001, B10000001, B11000011, B00000011, B00010000,
     B00011000, B11000110, B00000001, B11000001, B10000000, B11000011, B00000011, B00100000,
     B00011001, B11000110, B00000001, B11000001, B10000000, B11000011, B00000011, B01000000,
     B00011111, B00000110, B00000000, B01100001, B10000000, B11000011, B00000011, B01000000,
     B00011011, B00000111, B11000010, B01100001, B10000000, B11000011, B11100011, B11000000,
     B00011011, B10000110, B00000011, B11110001, B10000000, B11000011, B00000011, B11100000,
     B00011001, B11000110, B00000110, B00110001, B10000000, B11000011, B00000011, B01100000,
     B00111001, B11000110, B00000100, B00110001, B10000000, B11000011, B00000011, B00110000,
     B00111000, B11100110, B00001000, B00011001, B10000000, B11000011, B00000011, B00111000,
     B00011000, B01100111, B11101000, B00011001, B11111000, B10000011, B11100011, B00011000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};

#define LOGO_HEIGHT_FLAKES 16
#define LOGO_WIDTH_FLAKES  16
static const unsigned char PROGMEM logo_bmp_flake[] =
    {0b00000000, 0b11000000,
     0b00000001, 0b11000000,
     0b00000001, 0b11000000,
     0b00000011, 0b11100000,
     0b11110011, 0b11100000,
     0b11111110, 0b11111000,
     0b01111110, 0b11111111,
     0b00110011, 0b10011111,
     0b00011111, 0b11111100,
     0b00001101, 0b01110000,
     0b00011011, 0b10100000,
     0b00111111, 0b11100000,
     0b00111111, 0b11110000,
     0b01111100, 0b11110000,
     0b01110000, 0b01110000,
     0b00000000, 0b00110000};

void setup()
{
    Serial.begin(115200);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;    // Don't proceed, loop forever
    }

    // Draw a small bitmap image
    drawbitmap();
    delay(3000);

    // Clear the buffer
    display.clearDisplay();

    // Draw a single pixel in white
    display.drawPixel(10, 10, SSD1306_WHITE);

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000);

    // display.display() is NOT necessary after every single drawing command,
    // unless that's what you want...rather, you can batch up a bunch of
    // drawing operations and then update the screen all at once by calling
    // display.display(). These examples demonstrate both approaches...

    testdrawline();    // Draw many lines

    testdrawrect();    // Draw rectangles (outlines)

    testfillrect();    // Draw rectangles (filled)

    testdrawcircle();    // Draw circles (outlines)

    testfillcircle();    // Draw circles (filled)

    testdrawroundrect();    // Draw rounded rectangles (outlines)

    testfillroundrect();    // Draw rounded rectangles (filled)

    testdrawtriangle();    // Draw triangles (outlines)

    testfilltriangle();    // Draw triangles (filled)

    testdrawchar();    // Draw characters of the default font

    testdrawstyles();    // Draw 'stylized' characters

    testscrolltext();    // Draw scrolling text

    // Invert and restore display, pausing in-between
    display.invertDisplay(true);
    delay(1000);
    display.invertDisplay(false);
    delay(1000);

    testanimate(logo_bmp_flake, LOGO_WIDTH_FLAKES, LOGO_HEIGHT_FLAKES);    // Animate bitmaps
}

void loop()
{
}

void drawbitmap(void)
{
    display.clearDisplay();

    display.drawBitmap(
        (display.width() - LOGO_WIDTH) / 2,
        (display.height() - LOGO_HEIGHT) / 2,
        logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();
}

void testdrawline()
{
    int16_t i;

    display.clearDisplay();    // Clear display buffer

    for (i = 0; i < display.width(); i += 4) {
        display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
        display.display();    // Update screen with each newly-drawn line
        delay(1);
    }
    for (i = 0; i < display.height(); i += 4) {
        display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for (i = 0; i < display.width(); i += 4) {
        display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for (i = display.height() - 1; i >= 0; i -= 4) {
        display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for (i = display.width() - 1; i >= 0; i -= 4) {
        display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for (i = display.height() - 1; i >= 0; i -= 4) {
        display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for (i = 0; i < display.height(); i += 4) {
        display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for (i = 0; i < display.width(); i += 4) {
        display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);    // Pause for 2 seconds
}

void testdrawrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2; i += 2) {
        display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
        display.display();    // Update screen with each newly-drawn rectangle
        delay(1);
    }

    delay(2000);
}

void testfillrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2; i += 3) {
        // The INVERSE color is used so rectangles alternate white/black
        display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, SSD1306_INVERSE);
        display.display();    // Update screen with each newly-drawn rectangle
        delay(1);
    }

    delay(2000);
}

void testdrawcircle(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2) {
        display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfillcircle(void)
{
    display.clearDisplay();

    for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3) {
        // The INVERSE color is used so circles alternate white/black
        display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
        display.display();    // Update screen with each newly-drawn circle
        delay(1);
    }

    delay(2000);
}

void testdrawroundrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
        display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
                              display.height() / 4, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfillroundrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
        // The INVERSE color is used so round-rects alternate white/black
        display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
                              display.height() / 4, SSD1306_INVERSE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testdrawtriangle(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 5) {
        display.drawTriangle(
            display.width() / 2, display.height() / 2 - i,
            display.width() / 2 - i, display.height() / 2 + i,
            display.width() / 2 + i, display.height() / 2 + i, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfilltriangle(void)
{
    display.clearDisplay();

    for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 5) {
        // The INVERSE color is used so triangles alternate white/black
        display.fillTriangle(
            display.width() / 2, display.height() / 2 - i,
            display.width() / 2 - i, display.height() / 2 + i,
            display.width() / 2 + i, display.height() / 2 + i, SSD1306_INVERSE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testdrawchar(void)
{
    display.clearDisplay();

    display.setTextSize(1);                 // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);    // Draw white text
    display.setCursor(0, 0);                // Start at top-left corner
    display.cp437(true);                    // Use full 256 char 'Code Page 437' font

    // Not all the characters will fit on the display. This is normal.
    // Library will draw what it can and the rest will be clipped.
    for (int16_t i = 0; i < 256; i++) {
        if (i == '\n') {
            display.write(' ');
        } else {
            display.write(i);
        }
    }

    display.display();
    delay(2000);
}

void testdrawstyles(void)
{
    display.clearDisplay();

    display.setTextSize(1);                 // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);    // Draw white text
    display.setCursor(0, 0);                // Start at top-left corner
    display.println(F("Hello, world!"));

    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);    // Draw 'inverse' text
    display.println(3.141592);

    display.setTextSize(2);    // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.print(F("0x"));
    display.println(0xDEADBEEF, HEX);

    display.display();
    delay(2000);
}

void testscrolltext(void)
{
    display.clearDisplay();

    display.setTextSize(2);    // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.println(F("scroll"));
    display.display();    // Show initial text
    delay(100);

    // Scroll in various directions, pausing in-between:
    display.startscrollright(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrollleft(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrolldiagright(0x00, 0x07);
    delay(2000);
    display.startscrolldiagleft(0x00, 0x07);
    delay(2000);
    display.stopscroll();
    delay(1000);
}

void testdrawbitmap(void)
{
    display.clearDisplay();

    display.drawBitmap(
        (display.width() - LOGO_WIDTH) / 2,
        (display.height() - LOGO_HEIGHT) / 2,
        logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();
    delay(1000);
}

#define XPOS   0    // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h)
{
    int8_t f, icons[NUMFLAKES][3];

    // Initialize 'snowflake' positions
    for (f = 0; f < NUMFLAKES; f++) {
        icons[f][XPOS] = random(1 - LOGO_WIDTH_FLAKES, display.width());
        icons[f][YPOS] = -LOGO_HEIGHT_FLAKES;
        icons[f][DELTAY] = random(1, 6);
        Serial.print(F("x: "));
        Serial.print(icons[f][XPOS], DEC);
        Serial.print(F(" y: "));
        Serial.print(icons[f][YPOS], DEC);
        Serial.print(F(" dy: "));
        Serial.println(icons[f][DELTAY], DEC);
    }

    for (;;) {                     // Loop forever...
        display.clearDisplay();    // Clear the display buffer

        // Draw each snowflake:
        for (f = 0; f < NUMFLAKES; f++) {
            display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
        }

        display.display();    // Show the display buffer on the screen
        delay(200);           // Pause for 1/10 second

        // Then update coordinates of each flake...
        for (f = 0; f < NUMFLAKES; f++) {
            icons[f][YPOS] += icons[f][DELTAY];
            // If snowflake is off the bottom of the screen...
            if (icons[f][YPOS] >= display.height()) {
                // Reinitialize to a random position, just off the top
                icons[f][XPOS] = random(1 - LOGO_WIDTH_FLAKES, display.width());
                icons[f][YPOS] = -LOGO_HEIGHT_FLAKES;
                icons[f][DELTAY] = random(1, 6);
            }
        }
    }
}
