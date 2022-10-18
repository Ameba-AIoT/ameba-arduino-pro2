#include "Arduino.h"

class CameraIOClass
{
public:
    CameraIOClass(uint8_t numInput, uint8_t numOutput);

    uint8_t numInput;
    uint8_t numOutput;

    // function pointers
    void *(*create)(void);
    void (*destroy)(void*);
    void (*registerInput)(void*, void*);
    void (*registerOutput)(void*, void*);
    int  (*start)(void*);
    void (*stop)(void*);
    void (*pause)(void*);
    void (*resume)(void*);
};

