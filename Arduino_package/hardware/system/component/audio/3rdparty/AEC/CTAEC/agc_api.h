#ifndef	__AGC_H__
#define	__AGC_H__

#ifdef __cplusplus
extern "C" {
#endif


#define	AGC_STATE_MEMORY_SIZE	2*236	// words (32-bit word)

typedef enum {
	ALC_MODE = 0,
	DRC_MODE,
	LIMITER_MODE,
} AGC_MODES ;

typedef struct {
	int16_t FrameSize ;             // in samples 80 @ 8000Hz and 160 @ 16000Hz
	int16_t RMSDetectorEnable ;     // '1' - RMS based signal level detector, '0' - peak input level detector
	int16_t ReferenceLvl ;          // in dBFS 0,3,6,7... 24dB :0->0dB, 3->-3dB, 6->-6dB, 7->-7dB...24->-24dB
	int16_t RefThreshold ;          //Max reference level threshold (in dBFS) in DRC/Limiter modes.
	int16_t Ratio1 ;                //Compression ratio for Reference/RefThreshold level
	int16_t Threshold1 ;            //dBFS, AGC referece Threshold1
	int16_t Ratio2 ;                //Compression ratio for Threshold1
	int16_t Threshold2 ;            //dBFS, AGC referece Threshold2
	int16_t Ratio3 ;                //Compression ratio for Threshold2
	int16_t Kneewidth ;             //Kneewidth : 0-10 , Gain soft smoothing kneewidth size
	int16_t MaxGainLimit ;          //30/24/18/12/6 => 30dB/24dB/18dB/12dB/6dB, Default value = 30 (30dB)
	int16_t NoiseFloorAdaptEnable;  // '=1(enable)': Calculating the noisefloor level and used it as the NoiseGateLvl along with the API configured      value. '=0(disable)': no effect
	int16_t NoiseGateLvl ;          //The Noise floor level -dBFS, if the input -dBFS is larger than this, then AGC active

	int16_t Mode ;                  // ALC_MODE or LIMITTER_MODE or DRC_MODE
	// an initial loud voice signal does not cause a sudden burst of excessive modulation
	int16_t AttackTime ;            // 20- 1000 (ms) in steps 10 (ms) , smoothing gain
	// defined as the period elapsed between applying a higher signal level to the input and obtaining the output level */
	int16_t ReleaseTime ;           // 20-1000(ms) in steps 10 (ms), smoothing gain
	// defined as the time required for attaining the output level with the respective level */
	int32_t SamplingRate ;          // 8000 -> 8000Hz, 16000->16000Hz
} AGC_CTRL_PARAMS ;

typedef struct {
	int16_t NoiseGateLvl ;  //40..70dBFS in steps 1(dB): 40->-40dBFS...70->-70dBFS Minimum noise level, AGC is inactive below this level
	int16_t AGCEnable ;     //Enable/Disbale at run time
	int16_t ReferenceLvl ;  //in dB 0,3,6,7... 24dBFS :0->0dBFS, 3->-3dBFS, 6->-6dBFS, 7->-7dBFS...24->-24dBFS,..30->-30dBFS
	int16_t RefThreshold ;  //Max reference level threshold (in dBFS).
} AGC_RTCTRL_PARAMS ;

int32_t CT_AGC_GetStateMemorySize(int32_t SamplingRate, int16_t FrameSize) ;
int16_t CT_AGC_Init(int32_t *AGCMemory, AGC_CTRL_PARAMS *CtrlCfg) ;
int16_t CT_AGC_Process(int32_t *AGCMemory, int16_t *Input, int16_t *Output, int16_t FrameLen, AGC_RTCTRL_PARAMS *RTCtrlCfg) ;

#ifdef __cplusplus
}
#endif

#endif

