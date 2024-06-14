// Multiple Input and Multiple Output
#ifndef MIMO_DRV_H
#define MIMO_DRV_H

#include "Arduino.h"
#include "mmf2_module.h"

uint32_t mimoCreate(void);
void mimoDestroy(void *);
int mimoStart(void *);
void mimoStop(void *);
void mimoPause(void *);
void mimoResume(void *);
void mimoRegIn1(void *, mm_context_t *);
void mimoRegIn2(void *, mm_context_t *);
void mimoRegIn3(void *, mm_context_t *);
void mimoRegOut1(void *, mm_context_t *);
void mimoRegOut2(void *, mm_context_t *);
void getInput(uint8_t numInput);

#endif
