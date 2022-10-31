// Multiple Input and Single Output
#include "Arduino.h"
#include "mmf2_module.h"

void misoCreate(void);
void misoDestroy(void);
int  misoStart(void);
void misoStop(void);
void misoPause(void);
void misoResume(void);
void misoRegIn1(mm_context_t*);
void misoRegIn2(mm_context_t*);
void misoRegOut(mm_context_t*);