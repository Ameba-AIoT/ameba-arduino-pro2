#include "CameraIO.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "siso_drv.h"
//#include "simo_drv.h"
//#include "miso_drv.h"
//#include "mimo_drv.h"

#ifdef __cplusplus
}
#endif


#define SIMO 0
#define MISO 0
#define MIMO 0


CameraIOClass::CameraIOClass (uint8_t numInput, uint8_t numOutput ) {

    if (numInput > 1){
        
        if (numOutput > 1){
            //MIMO (Multi Input Multi Output)
            #if MIMO
            this->create = &mimoCreate;
            this->destroy = &mimoDestroy;
            this->registerInput = &mimoRegIn;
            this->registerOutput = &mimoRegOut;
            this->start = &mimoStart;
            this->stop = &mimoStop;
            this->pause = &mimoPause;
            this->resume = &mimoResume;
            #endif
        }
        else {
            // MISO (Multi Input Single Output)
            #if MISO
            this->create = &misoCreate;
            this->destroy = &misoDestroy;
            this->registerInput = &misoRegIn;
            this->registerOutput = &misoRegOut;
            this->start = &misoStart;
            this->stop = &misoStop;
            this->pause = &misoPause;
            this->resume = &misoResume;
            #endif
        }
    } else {
        if (numOutput > 1){
            //SIMO (Single Input Multi Output)
            #if SIMO
            this->create = &simoCreate;
            this->destroy = &simoDestroy;
            this->registerInput = &simoRegIn;
            this->registerOutput = &simoRegOut;
            this->start = &simoStart;
            this->stop = &simoStop;
            this->pause = &simoPause;
            this->resume = &simoResume;
            #endif
        }
        else {
            // SISO (Single Input Single Output)
            this->create = &sisoCreate;
            this->destroy = &sisoDestroy;
            this->registerInput = &sisoRegIn;
            this->registerOutput = &sisoRegOut;
            this->start = &sisoStart;
            this->stop = &sisoStop;
            this->pause = &sisoPause;
            this->resume = &sisoResume;
        }
    }
}

