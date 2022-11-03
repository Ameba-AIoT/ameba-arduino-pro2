// Single Input and Multiple Output
#include "Arduino.h"
#include "mmf2_module.h"

void simoCreate(void);
void simoDestroy(void);
int  simoStart(void);
void simoStop(void);
void simoPause(void);
void simoResume(void);
void simoRegIn(mm_context_t*);
void simoRegOut1(mm_context_t*);
void simoRegOut2(mm_context_t*);