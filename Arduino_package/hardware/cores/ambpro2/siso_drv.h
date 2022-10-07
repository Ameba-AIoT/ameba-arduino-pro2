// Single Input and Single Output
#include "Arduino.h"


void *sisoCreate(void);
void sisoDestroy(void*);
int  sisoStart(void*);
void sisoStop(void*);
void sisoPause(void*);
void sisoResume(void*);
void sisoRegIn(void*, void*);
void sisoRegOut(void*, void*);

