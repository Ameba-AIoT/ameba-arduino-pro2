// Multiple Input and Single Output
#ifndef MISO_DRV_H
#define MISO_DRV_H

#include "Arduino.h"
#include "mmf2_module.h"

uint32_t misoCreate(void);
void misoDestroy(void *);
int misoStart(void *);
void misoStop(void *);
void misoPause(void *);
void misoResume(void *);
void misoRegIn1(void *, mm_context_t *);
void misoRegIn2(void *, mm_context_t *);
void misoRegOut(void *, mm_context_t *);

#endif
