// Single Input and Single Output
#ifndef SISO_DRV_H
#define SISO_DRV_H

#include "Arduino.h"
#include "mmf2_module.h"

uint32_t sisoCreate(void);
void sisoDestroy(void *);
int  sisoStart(void *);
void sisoStop(void *);
void sisoPause(void *);
void sisoResume(void *);
void sisoRegIn(void *, mm_context_t *);
void sisoRegOut(void *, mm_context_t *);
void sisoSetStackSize(void *);
void sisoSetTaskPriority(void *);

#endif
