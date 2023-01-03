#ifndef __NS_API_H__
#define	__NS_API_H__


#define	NS_STATE_MEM_SIZE	640
#define	NS_SCRATCH_MEM_SIZE	700

typedef struct NS_CTRL_PARAMS {
	//int16_t WNSEnable;    // 0 -disable, 1 - enable
	int16_t NSEnable;
	int32_t	SamplingRate;   // 8000->8000Hz, 16000->16000Hz
} NS_CTRL_PARAMS;

typedef struct NS_RTCTRL_PARAMS {
	int16_t	NSLevel;        // 0 -> disable, 3->3dB,4->4dB,5->5dB....20->20dB in 1d steps
	//int16_t WNSLevel;     //0 - disable, 1- low, 2 - midium, 3 - high
} NS_RTCTRL_PARAMS;

int32_t Noise_Suppression_GetStateMemorySize(int32_t SamplingRate);
int32_t Noise_Suppression_GetScratchMemorySize(int32_t SamplingRate);
int16_t Noise_Suppression_Init(int32_t *NSMemory, NS_CTRL_PARAMS *CtrlCfg, int32_t *WorkBuffer);
int16_t Noise_Suppression_Process(int32_t *NSMemory, int16_t *InpBuffer, int16_t *OutBuffer, int16_t FrameSize, NS_RTCTRL_PARAMS *RTCtrlCfg);

#endif
