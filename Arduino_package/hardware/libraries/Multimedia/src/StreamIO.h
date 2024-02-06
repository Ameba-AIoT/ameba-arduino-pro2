#ifndef __STREAMIO_H__
#define __STREAMIO_H__

#include "Arduino.h"
#include "VideoStream.h"

class StreamIO {
public:
    StreamIO(uint8_t numInput, uint8_t numOutput);
    ~StreamIO(void);

    int begin(void);
    void end(void);
    void pause(void);
    void resume(void);
    void registerInput(const MMFModule &module);
    void registerInput1(const MMFModule &module);
    void registerInput2(const MMFModule &module);
    void registerInput3(const MMFModule &module);
    void registerOutput(const MMFModule &module);
    void registerOutput1(const MMFModule &module);
    void registerOutput2(const MMFModule &module);
    void setStackSize(void);
    void setTaskPriority(void);

private:
    void *_p_linker = NULL;

    // function pointers
    uint32_t (*_p_create)(void);
    void (*_p_destroy)(void *);
    int (*_p_start)(void *);
    void (*_p_stop)(void *);
    void (*_p_pause)(void *);
    void (*_p_resume)(void *);
    void (*_p_registerInput)(void *, mm_context_t *);
    void (*_p_registerInput1)(void *, mm_context_t *);
    void (*_p_registerInput2)(void *, mm_context_t *);
    void (*_p_registerInput3)(void *, mm_context_t *);
    void (*_p_registerOutput)(void *, mm_context_t *);
    void (*_p_registerOutput1)(void *, mm_context_t *);
    void (*_p_registerOutput2)(void *, mm_context_t *);
    void (*_p_setStackSize)(void *);
    void (*_p_setTaskPriority)(void *);
};

#endif
