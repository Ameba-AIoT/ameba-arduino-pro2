#ifndef     __AEC_API_H__
#define     __AEC_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef	int16_t 	INT16 ;
typedef	int32_t 	INT32 ;

#define AEC_STATE_MEM_SIZE      12000 //7600 //3780 //3372  // 64ms @ 16000Hz
#define AEC_SCRATCH_MEM_SIZE    10000 //3000 //3780 //3372  // 64ms @ 16000Hz

/* AEC Control parameter structure at Initialisation time*/
typedef struct AEC_CTRL_PARAMS {	/* keep variables in same order */
	INT16 AudioBargeInEnable;
	INT16 EchoTailLen;      // 64(ms) or 128(ms)			/* AEC_ECHO_TAIL_LENHTH */
	INT16 AECEnable;        // 0- disable, 1- enable
	INT16 PPEnable;         // 0 -disable, 1 - enable
	INT16 HPFEnable;        // 0- disable, 1 - enable
	INT16 CNGEnable;        // 0- disabel, 1 - enable
	INT16 CNGInitialLvl;    // 0-10, 0->33dB,.. 10->70dB
	INT16 CNGAdjustLvl;     // 0 = none, 1 = normal, 2 = fast
	INT16 DTControl;        // 1 - Type1 (allow some low residual), 2 - Type2a (may attenuate upto 6dB local), 3 - Type2b (may attenuate upto 9dB local)
	INT16 PTime;            // 10(ms) or 20(ms)
	INT16 BulkDelay;        // in milli seconds : 0-50(ms)
	INT16 PPLevel;          // 1-15
	INT16 NSEnable;         // 0-NO, 1- YES
	INT16 Mode;             // mono - 1 and stereo -2, default - 1
	INT32 SamplingRate;     // 8000 = 8000Hz, 16000 = 16000Hz
	AGC_CTRL_PARAMS AGCCfg;
} AEC_CTRL_PARAMS;

/* AEC Control parameter structure at runtime control*/
typedef struct AEC_RTCTRL_PARAMS {
	INT16 AdaptationControl;    //! 0 = stop, 1 = allow,
} AEC_RTCTRL_PARAMS;
/*
typedef struct NS_RTCTRL_PARAMS
{
	INT16 NSLevel;
} NS_RTCTRL_PARAMS;
*/

INT32 AEC_GetScratchMemorySize(INT16 ECTail, INT32 fs, INT16 PTime, INT16 Mode);
INT32 AEC_GetStateMemorySize(INT16 ECTail, INT32 fs, INT16 pTime, INT16 ECEnable, INT16 PPEnable, INT16 NSRequired, INT16 BulkDelay, INT16 Mode);
INT16 AEC_Init(INT32 *AECMemory, AEC_CTRL_PARAMS *AECCtrlParams, INT16 *a, INT16 *b, INT32 *WorkBuffer);
INT16 AEC_Process(INT32 *AECMemory, INT16 *rin, INT16 *sin, INT16 *sout, AEC_RTCTRL_PARAMS *AECRTCfg, NS_RTCTRL_PARAMS *NSRTCfg, AGC_RTCTRL_PARAMS *AGCRTCfg);

INT16 AEC_SET_PPLevel(INT32 *AECMemory, INT16 PPLevel);
//INT16 AEC_SET_NSLevel (INT32 *AECMemory, INT16 NSLevel) ;
//INT16 AEC_SET_AGCRefLevel (INT32 *AECMemory, INT16 RefLevel, INT16 NoiseGateLvl) ;
INT16 AEC_SET_Enable(INT32 *AECMemory, INT16 AECEnable);

#ifdef __cplusplus
}
#endif

#endif
/*****************************************************************************/


