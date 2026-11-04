#ifndef _RGBLED_H_
#define _RGBLED_H_

#include <stdint.h>

#include "VideoStream.h"    // MMFModule, MMFModule::_p_mmf_context
#include "WS2812B.h"

/* Thin C++ front end for module_rgbled.c.
 *
 * StreamIO::registerOutput() takes an MMFModule&, and _p_mmf_context is
 * protected, so the module needs this subclass to be linkable. Everything
 * interesting happens in module_rgbled.c.
 *
 * The frame is split into four quadrants and each quarter of the strip follows
 * the midpoint colour of one quadrant: TL, TR, BL, BR. The strip is refreshed
 * once per second by the module.
 *
 * Usage:
 *     RGBLed led(17);              // 17 LEDs
 *     led.begin(176, 144);         // open the module, bind the strip
 *     streamer.registerOutput(led);
 *     ... Camera.channelBegin(RGB_CHANNEL) ...
 *
 * The strip is driven from the siso task, so begin() must complete before the
 * link is started.
 */
class RGBLed : public MMFModule {
public:
    /* num_leds  : length of the strip
     * mosi_pin  : SPI data pin, defaults to SPI_MOSI (PE_3 on AMB82-Mini)
     * At most one RGBLed may exist: the C module holds a single strip binding.
     */
    RGBLed(uint16_t num_leds, uint8_t mosi_pin = SPI_MOSI);

    /* Unbinds and closes the module if begin() succeeded. */
    ~RGBLed(void);

    /* Open the module and start driving the strip.
     * width/height must match the RGB video channel's output, because the
     * module indexes into a width * height * 3 planar frame.
     * Returns false if the module or the SPI port could not be opened.
     */
    bool begin(uint16_t width, uint16_t height);

    /* Close the module and blank the strip. Safe to call more than once. */
    void end(void);

    /* Called by the module to paint num_leds pixels starting at first. */
    void fillRange(uint8_t r, uint8_t g, uint8_t b, uint16_t first, uint16_t num_leds);

    /* Push the pixel buffer to the strip. */
    void show(void);

    /* Latest sampled colours, 0xRRGGBB, indexed RGBLED_QUAD_TL/TR/BL/BR. */
    uint32_t quadrantColor(uint8_t quadrant);

    /* Convenience for the top-left quadrant, kept for older sketches. */
    uint32_t lastColor(void);

    /* Number of frames the module has handled. */
    uint32_t frameCount(void);

private:
    WS2812B _strip;    // declared first: must outlive the module's binding
    uint16_t _num_leds;
    uint8_t _mosi_pin;
    bool _begun = false;

    /* The C module has a single strip binding, so only one RGBLed may be
     * active at a time. Set/cleared by begin()/end().
     */
    static RGBLed *_active;
};

#endif
