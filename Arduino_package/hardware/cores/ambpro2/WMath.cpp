/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <inttypes.h>
#include "WMath.h"
#include "device.h"
#include "trng_api.h"

static bool s_useRandomHW = false;    // by default use pseudo random, not TRNG
uint32_t _rtl_seed;

extern void useRealRandomGenerator(bool useRandomHW)
{
    s_useRandomHW = useRandomHW;
}

extern void randomSeed(uint32_t dwSeed)
{
    if (dwSeed != 0) {
        _rtl_seed = dwSeed;
        s_useRandomHW = false;    // if randomSeed is called, useRandom=false by default.
    }
}

uint32_t random_calculate(uint32_t rtl_seed)
{
    uint32_t hi32, lo32;

    hi32 = (rtl_seed >> 16) * 19;
    lo32 = (rtl_seed & 0xffff) * 19 + 37;
    hi32 = hi32 ^ (hi32 << 16);
    return (hi32 ^ lo32);
}

extern long random(long howbig)
{
    if (howbig == 0) {
        return 0;
    }
    if (s_useRandomHW == true) {    // TRNG
        trng_init();
        return (trng_get_rand() % howbig);
    } else {    // default non TRNG
        _rtl_seed = random_calculate(_rtl_seed);
        return (_rtl_seed % howbig);
    }
}

extern long random(long howsmall, long howbig)
{
    if (howsmall >= howbig) {
        return howsmall;
    }
    long diff = howbig - howsmall;
    return (random(diff) + howsmall);
}

extern long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

extern uint16_t makeWord(uint16_t w)
{
    return w;
}

extern uint16_t makeWord(uint8_t h, uint8_t l)
{
    return ((h << 8) | l);
}
