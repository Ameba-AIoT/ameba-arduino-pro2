#include "RGBLed.h"

#include "Arduino.h"
#include "module_rgbled.h"

/* The C module reaches the bound object through these two functions, which is
 * what keeps module_rgbled.c free of C++ and WS2812B headers.
 *
 * rgbled_bind() is handed the RGBLed the sketch owns, so the opaque void* is
 * really an RGBLed*. Going through RGBLed (rather than casting straight to
 * WS2812B*) lets the range fill be bounds checked against the bound strip.
 */
void rgbled_strip_fill_range(void *strip, uint8_t r, uint8_t g, uint8_t b,
                             uint16_t first, uint16_t count)
{
    static_cast<RGBLed *>(strip)->fillRange(r, g, b, first, count);
}

void rgbled_strip_show(void *strip)
{
    static_cast<RGBLed *>(strip)->show();
}

RGBLed *RGBLed::_active = NULL;

RGBLed::RGBLed(uint16_t num_leds, uint8_t mosi_pin)
    : _strip(mosi_pin, num_leds), _num_leds(num_leds), _mosi_pin(mosi_pin)
{
}

RGBLed::~RGBLed(void)
{
    end();
}

bool RGBLed::begin(uint16_t width, uint16_t height)
{
    if (_begun) {
        return true;
    }
    if (width == 0 || height == 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] RGBLed: invalid frame size %ux%u\n", width, height);
        return false;
    }
    if (_active != NULL && _active != this) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] RGBLed: another instance is already driving the strip\n");
        return false;
    }

    _p_mmf_context = mm_module_open(&rgbled_module);
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] RGBLed: module open failed\n");
        return false;
    }

    rgbled_params_t params = {
        .width = width,
        .height = height,
        .num_leds = _num_leds,
    };
    mm_module_ctrl(_p_mmf_context, CMD_RGBLED_SET_PARAMS, (int)&params);

    _strip.begin();
    _strip.clear();
    _strip.show();

    rgbled_bind(this);
    _active = this;
    _begun = true;
    return true;
}

void RGBLed::end(void)
{
    if (!_begun) {
        return;
    }

    /* Unbind before closing the module: the siso task must stop calling into
     * this object before it (or the module) goes away. Stop the stream link
     * as well if it outlives this call.
     */
    rgbled_bind(NULL);
    _active = NULL;

    _strip.clear();
    _strip.show();

    if (_p_mmf_context != NULL) {
        mm_module_close(_p_mmf_context);
        _p_mmf_context = NULL;
    }
    _begun = false;
}

void RGBLed::fillRange(uint8_t r, uint8_t g, uint8_t b, uint16_t first, uint16_t num_leds)
{
    if (num_leds == 0 || first >= _num_leds) {
        return;
    }
    if (num_leds > (uint16_t)(_num_leds - first)) {
        num_leds = (uint16_t)(_num_leds - first);
    }
    _strip.fill(r, g, b, first, num_leds);
}

void RGBLed::show(void)
{
    _strip.show();
}

uint32_t RGBLed::quadrantColor(uint8_t quadrant)
{
    uint32_t colours[RGBLED_QUADRANTS] = {0};

    if (_p_mmf_context == NULL || quadrant >= RGBLED_QUADRANTS) {
        return 0;
    }
    mm_module_ctrl(_p_mmf_context, CMD_RGBLED_GET_QUADRANT_COLORS, (int)colours);
    return colours[quadrant];
}

uint32_t RGBLed::lastColor(void)
{
    return quadrantColor(RGBLED_QUAD_TL);
}

uint32_t RGBLed::frameCount(void)
{
    if (_p_mmf_context == NULL || _p_mmf_context->priv == NULL) {
        return 0;
    }
    return static_cast<rgbled_ctx_t *>(_p_mmf_context->priv)->frames;
}
