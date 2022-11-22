// Single Input and Multiple Output
#ifndef simo_drv_h
#define simo_drv_h

#include "Arduino.h"
#include "mmf2_module.h"

uint32_t simoCreate(void);
void simoDestroy(void *);
int  simoStart(void *);
void simoStop(void *);
void simoPause(void *);
void simoResume(void *);
void simoRegIn(void *, mm_context_t *);
void simoRegOut1(void *, mm_context_t *);
void simoRegOut2(void *, mm_context_t *);

#endif