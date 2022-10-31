#include "Arduino.h"
#include "rtsp.h"
#include "camera.h"



class CameraIOClass
{
public:
    CameraIOClass(uint8_t numInput, uint8_t numOutput);

    uint8_t numInput;
    uint8_t numOutput;

    // function pointers
    void (*create)(void);
    void (*destroy)(void);
    void (*registerInput)(mm_context_t*);
    void (*registerOutput)(mm_context_t*);
    int  (*start)(void);
    void (*stop)(void);
    void (*pause)(void);
    void (*resume)(void);
};

