// Multiple Input and Multiple Output
#ifndef mimo_drv_h
#define mimo_drv_h

#include "Arduino.h"
#include "mmf2_module.h"

void mimoCreate(void);
void mimoDestroy(void);
int  mimoStart(void);
void mimoStop(void);
void mimoPause(void);
void mimoResume(void);
void mimoRegIn1(mm_context_t*);
void mimoRegIn2(mm_context_t*);
void mimoRegIn3(mm_context_t*);
void mimoRegOut1(mm_context_t*);
void mimoRegOut2(mm_context_t*);
void getInput(uint8_t numInput);

#endif
