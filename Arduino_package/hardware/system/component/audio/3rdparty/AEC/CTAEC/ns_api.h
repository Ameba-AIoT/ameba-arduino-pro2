#ifndef __NS_API_H__
#define	__NS_API_H__


#define	NS_STATE_MEM_SIZE	780
#define	NS_SCRATCH_MEM_SIZE	500

typedef struct NS_CTRL_PARAMS {
	int16_t HPFEnable;          //HPF (highpass filter with fc = 140Hz) , '0' - HPF is disable, '1' - HPF is enable
	int16_t NSEnable;
	int32_t	SamplingRate;       // 8000->8000Hz, 16000->16000Hz
} NS_CTRL_PARAMS;

typedef struct NS_RTCTRL_PARAMS {
	int16_t	NSLevel;            // 0 -> disable, 3->3dB,4->4dB,5->5dB....20->20dB in 1d steps
} NS_RTCTRL_PARAMS;

int32_t Noise_Suppression_GetStateMemorySize(int32_t SamplingRate);
int32_t Noise_Suppression_GetScratchMemorySize(int32_t SamplingRate);
int16_t Noise_Suppression_Init(int32_t *NSMemory, NS_CTRL_PARAMS *CtrlCfg, int32_t *WorkBuffer);
int16_t Noise_Suppression_Process(int32_t *NSMemory, int16_t *InpBuffer, int16_t *OutBuffer, int16_t FrameSize, NS_RTCTRL_PARAMS *RTCtrlCfg);

#endif
