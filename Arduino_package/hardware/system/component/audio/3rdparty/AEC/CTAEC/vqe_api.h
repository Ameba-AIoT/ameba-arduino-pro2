#ifndef     __VQE_API_H__
#define     __VQE_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef	int16_t 	INT16;
typedef	int32_t 	INT32;

#define VQE_SND_STATE_MEM_SIZE         (6100)       //32-bit words
#define VQE_RCV_STATE_MEM_SIZE         (2100)       //32-bit words

#define VQE_SCRATCH_MEM_SIZE           (1800)       //32-bit words
typedef struct {
	INT16 DoA;              //in degrees
	INT16 ERLE;             //in dB
	INT16 SinLvldB;         //in dBFs
	INT16 SoutLvldB;        //indBFs after AGC (if AGC is enabled)
	INT16 DTState;          //0 = single talk  or 1 = doulble talk
	INT16 HCDetectState;    //1 = detected, 0 = not detected
} VQE_SND_STATE;

typedef struct {
	INT16 RinLvldB;
	INT16 RoutLvldB;
	INT16 HCDetectState;    //1 = detected, 0 = not detected
} VQE_RCV_STATE;


/* AEC Control parameter structure at Initialisation time*/
typedef struct {
	INT16 AudioBargeInEnable;
	INT16 EchoTailLen;              // 64(ms) or 128(ms)                    /* AEC_ECHO_TAIL_LENHTH */
	INT16 AECEnable;                // 0- disable, 1- enable
	INT16 PPEnable;                 // 0 -disable, 1 - enable
	INT16 HPFEnable;                // 0- disable, 1 - enable
	INT16 CNGEnable;                // 0- disabel, 1 - enable
	INT16 CNGInitialLvl;            // 0-10, 0->40dB,.. 10->70dB
	INT16 CNGAdjustLvl;             // 0 = none, 1 = normal, 2 = fast
	INT16 DTControl;                // 1-5, 1-Type1, 2-Type2a, 3 - Type2b, 4 - Type2c, 5 - Type3
	INT16 PTime;                    // 10(ms) or 20(ms)
	INT16 BulkDelay;                // in milli seconds, application should allocate required memory
	INT16 PPLevel;                  // 1-18
	INT16 NSEnable;                 // 0-NO, 1- YES
	INT16 Mode;                     //mono - 1 and stereo -2, default - 1
	INT32 SamplingRate;             // 8000 = 8000Hz, 16000 = 16000Hz
} VQE_AEC_CTRL_PARAMS;

/* AEC Control parameter structure at runtime control*/
typedef struct {
	INT16 AdaptationControl;        //! 0 = stop, 1 = allow,
	INT16 PPLevel;                  //post filter  suppression level 1-18
} VQE_AEC_RTCTRL_PARAMS;

/* NS Control parameter structure at Initialisation time*/
typedef struct {
	INT16   HPFEnable;              // 0 -disable, 1- enable
	INT16   NSEnable;
	INT16   NSGainSlowConvergenceEnable;
	INT32   SamplingRate;           // 8000->8000Hz, 16000->16000Hz
} VQE_NS_CTRL_PARAMS;

/* NS Control parameter structure at runtime control*/
typedef struct {
	INT16   NSLevel;                // 0 -> disable, 3->3dB,4->4dB,5->5dB....20->20dB in 1d steps
} VQE_NS_RTCTRL_PARAMS;


/* AGC Control parameter structure at Initialisation time*/
typedef enum {
	VQE_ALC_MODE = 0,
	VQE_LIMITER_MODE,
} VQE_AGC_MODES;

typedef struct {
	INT16 DetectorOpt;      // '1' - RMS level detector, '0' - pleak level detector
	INT16 ReferenceLvl;     // in dBFS 0,3,6,7... 24dB :0->0dB, 3->-3dB, 6->-6dB, 7->-7dB...24->-24dB
	INT16 NoiseGateLvl;     // The Noise floor level -dBFS, if the input -dBFS is larger than this, then AGC active
	INT16 Mode;             // ALC_MODE or LIMITTER_MODE
	// an initial loud voice signal does not cause a sudden burst of excessive modulation
	INT16 AttackTime;       // 1- 500 (ms) in steps 1 (ms) , smoothing gain
	// defined as the period elapsed between applying a higher signal level to the input and obtaining the output level */
	INT16 ReleaseTime;      // 1-500(ms) in steps 1 (ms), smoothing gain
	// defined as the time required for attaining the output level with the respective level */
	INT16 MaxGainLimit;     // 30/24/18/12/6 => 30dB/24dB/18dB/12dB/6dB, Default value = 30 (30dB)
	INT16 NoiseFloorAdapt
	;// '=1(enable)': Calculating the noisefloor level and used it as the NoiseGateLvl along with the API configured      value. '=0(disable)': no effect, used API configured NoiseDateLvl value
	INT32 SamplingRate;     //8000 -> 8000Hz, 16000->16000Hz
	INT16 FrameSize;        // in samples
	INT16 RefThreshold;     //Max reference level threshold (in dBFS) in DRC/Limiter.
	INT16 Ratio1;           //Compression ratio for Reference/RefThreshold level  in Q10 format
	INT16 Threshold1;       //The max dBFS of the AGC output (if the input dBFS will be compressed to the threshold)
	INT16 Ratio2;           //Compression ratio for Threshold1  in Q0 format
	INT16 Threshold2;       //The max dBFS of the AGC output (if the input dBFS will be compressed to the threshold)
	INT16 Ratio3;           //Compression ratio for Threshold3 in Q0 format
	INT16 Kneewidth;        //Kneewidth : 0-10, default value = 0

} VQE_AGC_CTRL_PARAMS;

/* AGC Control parameter structure at runtime control*/
typedef struct {
	INT16 AGCEnable;        //Enable/Disbale at run time
	INT16 NoiseGateLvl;     //40..70dBFS in steps 1(dB): 40->-40dBFS...70->-70dBFS Minimum noise level, AGC is inactive below this level
	INT16 ReferenceLvl;     //in dB 0,3,6,7... 24dBFS :0->0dBFS, 3->-3dBFS, 6->-6dBFS, 7->-7dBFS...24->-24dBFS,..30->-30dBFS
	INT16 RefThreshold;     //Max reference level threshold (in -dBFS).
} VQE_AGC_RTCTRL_PARAMS;

typedef struct {
	INT16 MM;                   //1-6 number mics in array
	INT16 BFEnable;
	INT16 MicArrayType;
	INT16 MicSpacing;           //in mm
	INT16 DOAEstimationEnable;  //for future use
	INT16 EndfireArray;
	INT16 AICEnable;
	INT32 SamplingRate;         //16000/32000/44100/48000
} VQE_BF_CTRL_PARAMS;

typedef struct {
	INT16 BFEnable;             //1=enable, 0=disable
	INT16 DOAEnable;            //for future use
	INT16 BFPFIntensity;
} VQE_BF_RTCTRL_PARAMS;


INT32 VQE_SND_GetStateMemorySize(INT32 SamplingRate, INT16 ECTail, INT16 PPLevel, INT16 BuilkDelay, INT16 Mode, INT16 NSEnable, INT16 AGCEnable, INT16 EQEnable,
								 INT16 HCEnable, INT16 MM, INT16 MicArrayType, INT16 BFEnable, INT16 DOAEnable, INT16 PTime);
INT32 VQE_SND_GetScratchMemorySize(INT32 SamplingRate, INT16 ECTail, INT16 Mode, INT16 PTime, INT16 MM, INT16 BFEnable, INT16 DOAEnable,
								   INT16    MicArrayType);

INT16 VQE_SND_Init(INT32 *VQESndMem, VQE_AEC_CTRL_PARAMS *AECCfg, VQE_NS_CTRL_PARAMS *NSCfg, VQE_AGC_CTRL_PARAMS *AGCCfg, void *EQCfg, void *HCCfg,
				   VQE_BF_CTRL_PARAMS *BFCfg, INT32 *WorkBuffer, INT16 FrameSize);

INT16 VQE_SND_Process(INT32 *VQESndMem, INT16 *Rin, INT16 *Sin, INT16 *Sout, VQE_AEC_RTCTRL_PARAMS *AECRTCfg, VQE_NS_RTCTRL_PARAMS *NSRTCfg,
					  VQE_AGC_RTCTRL_PARAMS *AGCRTCfg, void *EQRTCfg, void *HCRTCfg, void *BFRTCfg, void *VQESNDState);


INT32 VQE_RCV_GetStateMemorySize(INT32 SamplingRate, INT16 NSEnable, INT16 AGCEnable, INT16 EQEnable, INT16 HCEnable, INT16 PTime);
INT32 VQE_RCV_GetScratchMemorySize(INT32 SamplingRate, INT16 NSEnable, INT16 AGCEnable);

INT16 VQE_RCV_Init(INT32 *VQERcvMem, VQE_NS_CTRL_PARAMS *NSCfg, VQE_AGC_CTRL_PARAMS *AGCCfg, void *EQCfg, void *HCCfg, INT32 *WorkBuffer, INT16 FrameSize);
INT16 VQE_RCV_Process(INT32 *VQERcvMem, INT16 *Inp, INT16 *Out, VQE_NS_RTCTRL_PARAMS *NSRTCfg, VQE_AGC_RTCTRL_PARAMS *AGCRTCfg, void *EQRTCfg, void *HCRTCfg,
					  void *VQERCVState);


INT16 AEC_SET_PPLevel(INT32 *VQESNDMem, INT16 PPLevel);
INT16 AEC_SET_Enable(INT32 *VQESNDMem, INT16 AECEnable);

INT16 AEC_SET_ConvergenceTime(INT32 *VQESNDMem, INT16 ConvergeceTime);
INT16 AEC_SET_Enable(INT32 *VQESNDMem, INT16 Enable);

#ifdef __cplusplus
}
#endif

#endif
/*****************************************************************************/


