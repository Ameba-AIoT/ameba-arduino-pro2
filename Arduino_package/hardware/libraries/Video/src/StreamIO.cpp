#include "StreamIO.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mimo_drv.h"
#include "miso_drv.h"
#include "simo_drv.h"
#include "siso_drv.h"

#ifdef __cplusplus
}
#endif

StreamIO::StreamIO(uint8_t numInput, uint8_t numOutput) {
    if (numInput > 4) {
        printf("StreamIO too many inputs. Max 4 inputs.\r\n");
        return;
    }
    if (numOutput > 4) {
        printf("StreamIO too many outputs. Max 4 outputs.\r\n");
        return;
    }
    if (numInput > 1) {
        if (numOutput > 1) {
            // MIMO (Multi Input Multi Output)
            _p_create = &mimoCreate;
            _p_destroy = &mimoDestroy;
            _p_start = &mimoStart;
            _p_stop = &mimoStop;
            _p_pause = &mimoPause;
            _p_resume = &mimoResume;
            _p_registerInput = NULL;
            _p_registerInput1 = &mimoRegIn1;
            _p_registerInput2 = &mimoRegIn2;
            _p_registerInput3 = &mimoRegIn3;
            _p_registerOutput = NULL;
            _p_registerOutput1 = &mimoRegOut1;
            _p_registerOutput2 = &mimoRegOut2;
            _p_setStackSize = NULL;
            _p_setTaskPriority = NULL;
            getInput(numInput);
        } else {
            // MISO (Multi Input Single Output)
            _p_create = &misoCreate;
            _p_destroy = &misoDestroy;
            _p_start = &misoStart;
            _p_stop = &misoStop;
            _p_pause = &misoPause;
            _p_resume = &misoResume;
            _p_registerInput = NULL;
            _p_registerInput1 = &misoRegIn1;
            _p_registerInput2 = &misoRegIn2;
            _p_registerInput3 = NULL;
            _p_registerOutput = &misoRegOut;
            _p_registerOutput1 = NULL;
            _p_registerOutput2 = NULL;
            _p_setStackSize = NULL;
            _p_setTaskPriority = NULL;
        }
    } else {
        if (numOutput > 1) {
            // SIMO (Single Input Multi Output)
            _p_create = &simoCreate;
            _p_destroy = &simoDestroy;
            _p_start = &simoStart;
            _p_stop = &simoStop;
            _p_pause = &simoPause;
            _p_resume = &simoResume;
            _p_registerInput = &simoRegIn;
            _p_registerInput1 = NULL;
            _p_registerInput2 = NULL;
            _p_registerInput3 = NULL;
            _p_registerOutput = NULL;
            _p_registerOutput1 = &simoRegOut1;
            _p_registerOutput2 = &simoRegOut2;
            _p_setStackSize = NULL;
            _p_setTaskPriority = NULL;
        } else {
            // SISO (Single Input Single Output)
            _p_create = &sisoCreate;
            _p_destroy = &sisoDestroy;
            _p_start = &sisoStart;
            _p_stop = &sisoStop;
            _p_pause = &sisoPause;
            _p_resume = &sisoResume;
            _p_registerInput = &sisoRegIn;
            _p_registerInput1 = NULL;
            _p_registerInput2 = NULL;
            _p_registerInput3 = NULL;
            _p_registerOutput = &sisoRegOut;
            _p_registerOutput1 = NULL;
            _p_registerOutput2 = NULL;
            _p_setStackSize = &sisoSetStackSize;
            _p_setTaskPriority = &sisoSetTaskPriority;
        }
    }
    _p_linker = (void *)_p_create();
}

StreamIO::~StreamIO(void) {
    end();
    _p_destroy(_p_linker);
}

int  StreamIO::begin(void) {
    return _p_start(_p_linker);
}

void StreamIO::end(void) {
    _p_stop(_p_linker);
}

void StreamIO::pause(void) {
    _p_pause(_p_linker);
}

void StreamIO::resume(void) {
    _p_resume(_p_linker);
}

void StreamIO::registerInput(const MMFModule& module) {
    if (module._p_mmf_context == NULL) {
        printf("Input not initialized correctly!\r\n");
        return;
    }
    if (_p_registerInput != NULL) {
        _p_registerInput(_p_linker, module._p_mmf_context);
    } else {
        _p_registerInput1(_p_linker, module._p_mmf_context);
    }
}

void StreamIO::registerInput1(const MMFModule& module) {
    if (module._p_mmf_context == NULL) {
        printf("Input not initialized correctly!\r\n");
        return;
    }
    if (_p_registerInput1 != NULL) {
        _p_registerInput1(_p_linker, module._p_mmf_context);
    } else {
        _p_registerInput(_p_linker, module._p_mmf_context);
    }
}

void StreamIO::registerInput2(const MMFModule& module) {
    if (module._p_mmf_context == NULL) {
        printf("Input not initialized correctly!\r\n");
        return;
    }
    if (_p_registerInput2 != NULL) {
        _p_registerInput2(_p_linker, module._p_mmf_context);
    } else {
        _p_registerInput(_p_linker, module._p_mmf_context);
    }
}

void StreamIO::registerInput3(const MMFModule& module) {
    if (module._p_mmf_context == NULL) {
        printf("Input not initialized correctly!\r\n");
        return;
    }
    if (_p_registerInput3 != NULL) {
        _p_registerInput3(_p_linker, module._p_mmf_context);
    } else {
        _p_registerInput(_p_linker, module._p_mmf_context);
    }
}

void StreamIO::registerOutput(const MMFModule& module) {
    if (module._p_mmf_context == NULL) {
        printf("Output not initialized correctly!\r\n");
        return;
    }
    if (_p_registerOutput != NULL) {
        _p_registerOutput(_p_linker, module._p_mmf_context);
    } else {
        _p_registerOutput1(_p_linker, module._p_mmf_context);
    }
}

void StreamIO::registerOutput1(const MMFModule& module) {
    if (module._p_mmf_context == NULL) {
        printf("Output not initialized correctly!\r\n");
        return;
    }
    if (_p_registerOutput1 != NULL) {
        _p_registerOutput1(_p_linker, module._p_mmf_context);
    } else {
        _p_registerOutput(_p_linker, module._p_mmf_context);
    }
}

void StreamIO::registerOutput2(const MMFModule& module) {
    if (module._p_mmf_context == NULL) {
        printf("Output not initialized correctly!\r\n");
        return;
    }
    if (_p_registerOutput2 != NULL) {
        _p_registerOutput2(_p_linker, module._p_mmf_context);
    } else {
        _p_registerOutput(_p_linker, module._p_mmf_context);
    }
}

void StreamIO::setStackSize(void) {
    if (_p_setStackSize != NULL) {
        _p_setStackSize(_p_linker);
    }
}

void StreamIO::setTaskPriority(void) {
    if (_p_setTaskPriority != NULL) {
        _p_setTaskPriority(_p_linker);
    }
}