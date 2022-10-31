#ifndef	__AGC_H__
#define	__AGC_H__

#ifdef __cplusplus
extern "C" {
#endif


#define	AGC_STATE_MEMORY_SIZE	150		// words (32-bit word)

typedef enum {
	ALC_MODE = 0,
	DRC_MODE,
	LIMITER_MODE,
} AGC_MODES ;

typedef struct {
	int16_t FrameSize ;       // in samples
	int16_t ReferenceLvl ;	// in dB 0,3,6,7... 24dB :0->0dB, 3->-3dB, 6->-6dB, 7->-7dB...24->-24dB
	int16_t RefThreshold ;    //The max dBFS of the AGC output (if the input dBFS is larger than this, it will be compressed in the threshold)
	int16_t Mode ;		    // ALC_MODE or LIMITTER_MODE or DRC_MODE
	// an initial loud voice signal does not cause a sudden burst of excessive modulation
	int16_t AttackTime ;	    // 800- 2000 (ms) in steps 10 (ms)
	// defined as the period elapsed between applying a higher signal level to the input and obtaining the output level */
	int16_t ReleaseTime ;     // 800-2000(ms) in steps 10 (ms)
	// defined as the time required for attaining the output level with the respective level */
	int32_t SamplingRate ;    // 8000 -> 8000Hz, 16000->16000Hz
} AGC_CTRL_PARAMS ;

typedef struct {
	int16_t NoiseGateLvl ;    //40..70 in steps 1(dB): 40->40dB...70->70dB Minimum noise level, AGC is inactive below this level
	int16_t AGCEnable ;       //Enable/Disbale at run time
	int16_t ReferenceLvl ;	//in dB 0,3,6,7... 24dB :0->0dB, 3->-3dB, 6->-6dB, 7->-7dB...24->-24dB
	int16_t RefThreshold ;    //Max reference level threshold (in dB).
} AGC_RTCTRL_PARAMS ;

int32_t CT_AGC_GetStateMemorySize(int32_t SamplingRate, int16_t FrameSize) ;
int16_t CT_AGC_Init(int32_t *AGCMemory, AGC_CTRL_PARAMS *CtrlCfg) ;
int16_t CT_AGC_Process(int32_t *AGCMemory, int16_t *Input, int16_t *Output, int16_t FrameLen, AGC_RTCTRL_PARAMS *RTCtrlCfg) ;
int16_t CT_AGC_SET_OverScalingLevel(int32_t  *AGCMemory, int16_t OverScalingLvl) ;  //0 to 6, 0 = disable, 1->3dB,2->6dB,3->9dB,4->12dB,5->15dB,6->18dB

#ifdef __cplusplus
}
#endif

#endif

