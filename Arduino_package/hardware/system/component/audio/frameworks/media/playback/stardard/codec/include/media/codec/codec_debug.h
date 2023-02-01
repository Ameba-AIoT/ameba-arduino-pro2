/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_DEBUG_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_DEBUG_H

#include "osal_c/osal_errnos.h"

#include "media/codec/omxil/OMX_Types.h"
#include "media/codec/omxil/OMX_Core.h"
#include "media/codec/omxil/OMX_Component.h"
#include "media/codec/omxil/OMX_IndexExt.h"

namespace ameba::media
{

inline static const char *OmxToString(OMX_PORTDOMAINTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_PortDomainAudio:
		return "Audio";
	default:
		return def;
	}
}

inline static const char *OmxToString(OMX_DIRTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_DirInput:
		return "Input";
	case OMX_DirOutput:
		return "Output";
	default:
		return def;
	}
}

inline static const char *OmxToString(OMX_NUMERICALDATATYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_NumericalDataSigned:
		return "Signed";
	case OMX_NumericalDataUnsigned:
		return "Unsigned";
	default:
		return def;
	}
}

inline static const char *OmxToString(OMX_AUDIO_PCMMODETYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_AUDIO_PCMModeLinear:
		return "Linear";
	case OMX_AUDIO_PCMModeALaw:
		return "ALaw";
	case OMX_AUDIO_PCMModeMULaw:
		return "MULaw";
	default:
		return def;
	}
}

inline static const char *OmxToString(OMX_AUDIO_CODINGTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_AUDIO_CodingUnused:
		return "Unused";
	case OMX_AUDIO_CodingAutoDetect:
		return "AutoDetect";
	case OMX_AUDIO_CodingPCM:
		return "PCM";
	case OMX_AUDIO_CodingADPCM:
		return "ADPCM";
	case OMX_AUDIO_CodingAMR:
		return "AMR";
	case OMX_AUDIO_CodingGSMFR:
		return "GSMFR";
	case OMX_AUDIO_CodingGSMEFR:
		return "GSMEFR";
	case OMX_AUDIO_CodingGSMHR:
		return "GSMHR";
	case OMX_AUDIO_CodingPDCFR:
		return "PDCFR";
	case OMX_AUDIO_CodingPDCEFR:
		return "PDCEFR";
	case OMX_AUDIO_CodingPDCHR:
		return "PDCHR";
	case OMX_AUDIO_CodingTDMAFR:
		return "TDMAFR";
	case OMX_AUDIO_CodingTDMAEFR:
		return "TDMAEFR";
	case OMX_AUDIO_CodingQCELP8:
		return "QCELP8";
	case OMX_AUDIO_CodingQCELP13:
		return "QCELP13";
	case OMX_AUDIO_CodingEVRC:
		return "EVRC";
	case OMX_AUDIO_CodingSMV:
		return "SMV";
	case OMX_AUDIO_CodingG711:
		return "G711";
	case OMX_AUDIO_CodingG723:
		return "G723";
	case OMX_AUDIO_CodingG726:
		return "G726";
	case OMX_AUDIO_CodingG729:
		return "G729";
	case OMX_AUDIO_CodingAAC:
		return "AAC";
	case OMX_AUDIO_CodingMP3:
		return "MP3";
	case OMX_AUDIO_CodingSBC:
		return "SBC";
	case OMX_AUDIO_CodingVORBIS:
		return "VORBIS";
	case OMX_AUDIO_CodingWMA:
		return "WMA";
	case OMX_AUDIO_CodingRA:
		return "RA";
	case OMX_AUDIO_CodingMIDI:
		return "MIDI";
	default:
		return def;
	}
}

inline static const char *OmxToString(OMX_EVENTTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_EventCmdComplete:
		return "CmdComplete";
	case OMX_EventError:
		return "Error";
	case OMX_EventMark:
		return "Mark";
	case OMX_EventPortSettingsChanged:
		return "PortSettingsChanged";
	case OMX_EventBufferFlag:
		return "BufferFlag";
	case OMX_EventResourcesAcquired:
		return "ResourcesAcquired";
	case OMX_EventComponentResumed:
		return "ComponentResumed";
	case OMX_EventDynamicResourcesAvailable:
		return "DynamicResourcesAvailable";
	case OMX_EventPortFormatDetected:
		return "PortFormatDetected";
	default:
		return def;
	}
}

static inline const char *OmxToString(OMX_STATETYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_StateInvalid:
		return "Invalid";
	case OMX_StateLoaded:
		return "Loaded";
	case OMX_StateIdle:
		return "Idle";
	case OMX_StateExecuting:
		return "Executing";
	case OMX_StatePause:
		return "Pause";
	case OMX_StateWaitForResources:
		return "WaitForResources";
	default:
		return def;
	}
}

static inline const char *OmxToString(OMX_COMMANDTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_CommandStateSet:
		return "StateSet";
	case OMX_CommandFlush:
		return "Flush";
	case OMX_CommandPortDisable:
		return "PortDisable";
	case OMX_CommandPortEnable:
		return "PortEnable";
	case OMX_CommandMarkBuffer:
		return "MarkBuffer";
	default:
		return def;
	}
}

static inline const char *OmxToString(OMX_INDEXTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_IndexParamPriorityMgmt:
		return "ParamPriorityMgmt";
	case OMX_IndexParamAudioInit:
		return "ParamAudioInit";
	case OMX_IndexParamNumAvailableStreams:
		return "ParamNumAvailableStreams";
	case OMX_IndexParamActiveStream:
		return "ParamActiveStream";
	case OMX_IndexParamComponentSuspended:
		return "ParamComponentSuspended";
	case OMX_IndexAutoPauseAfterCapture:
		return "AutoPauseAfterCapture";
	case OMX_IndexParamContentURI:
		return "ParamContentURI";
	case OMX_IndexParamCustomContentPipe:
		return "ParamCustomContentPipe";
	case OMX_IndexParamDisableResourceConcealment:
		return "ParamDisableResourceConcealment";
	case OMX_IndexConfigMetadataItemCount:
		return "ConfigMetadataItemCount";
	case OMX_IndexConfigContainerNodeCount:
		return "ConfigContainerNodeCount";
	case OMX_IndexConfigMetadataItem:
		return "ConfigMetadataItem";
	case OMX_IndexConfigCounterNodeID:
		return "ConfigCounterNodeID";
	case OMX_IndexConfigPriorityMgmt:
		return "ConfigPriorityMgmt";
	case OMX_IndexParamStandardComponentRole:
		return "ParamStandardComponentRole";
	case OMX_IndexParamPortDefinition:
		return "ParamPortDefinition";
	case OMX_IndexParamCompBufferSupplier:
		return "ParamCompBufferSupplier";
	case OMX_IndexParamAudioPortFormat:
		return "ParamAudioPortFormat";
	case OMX_IndexParamAudioPcm:
		return "ParamAudioPcm";
	case OMX_IndexParamAudioAac:
		return "ParamAudioAac";
	case OMX_IndexParamAudioRa:
		return "ParamAudioRa";
	case OMX_IndexParamAudioMp3:
		return "ParamAudioMp3";
	case OMX_IndexParamAudioAdpcm:
		return "ParamAudioAdpcm";
	case OMX_IndexParamAudioG723:
		return "ParamAudioG723";
	case OMX_IndexParamAudioG729:
		return "ParamAudioG729";
	case OMX_IndexParamAudioAmr:
		return "ParamAudioAmr";
	case OMX_IndexParamAudioWma:
		return "ParamAudioWma";
	case OMX_IndexParamAudioSbc:
		return "ParamAudioSbc";
	case OMX_IndexParamAudioMidi:
		return "ParamAudioMidi";
	case OMX_IndexParamAudioGsm_FR:
		return "ParamAudioGsm_FR";
	case OMX_IndexParamAudioMidiLoadUserSound:
		return "ParamAudioMidiLoadUserSound";
	case OMX_IndexParamAudioG726:
		return "ParamAudioG726";
	case OMX_IndexParamAudioGsm_EFR:
		return "ParamAudioGsm_EFR";
	case OMX_IndexParamAudioGsm_HR:
		return "ParamAudioGsm_HR";
	case OMX_IndexParamAudioPdc_FR:
		return "ParamAudioPdc_FR";
	case OMX_IndexParamAudioPdc_EFR:
		return "ParamAudioPdc_EFR";
	case OMX_IndexParamAudioPdc_HR:
		return "ParamAudioPdc_HR";
	case OMX_IndexParamAudioTdma_FR:
		return "ParamAudioTdma_FR";
	case OMX_IndexParamAudioTdma_EFR:
		return "ParamAudioTdma_EFR";
	case OMX_IndexParamAudioQcelp8:
		return "ParamAudioQcelp8";
	case OMX_IndexParamAudioQcelp13:
		return "ParamAudioQcelp13";
	case OMX_IndexParamAudioEvrc:
		return "ParamAudioEvrc";
	case OMX_IndexParamAudioSmv:
		return "ParamAudioSmv";
	case OMX_IndexParamAudioVorbis:
		return "ParamAudioVorbis";
	case OMX_IndexConfigCommonScale:
		return "ConfigCommonScale";
	case OMX_IndexConfigCommonInputCrop:
		return "ConfigCommonInputCrop";
	case OMX_IndexConfigCommonOutputCrop:
		return "ConfigCommonOutputCrop";
	case OMX_IndexParamOtherPortFormat:
		return "ParamOtherPortFormat";
	case OMX_IndexConfigOtherPower:
		return "ConfigOtherPower";
	case OMX_IndexConfigOtherStats:
		return "ConfigOtherStats";
	case OMX_IndexConfigTimeScale:
		return "ConfigTimeScale";
	case OMX_IndexConfigTimeClockState:
		return "ConfigTimeClockState";
	case OMX_IndexConfigTimeActiveRefClock:
		return "ConfigTimeActiveRefClock";
	case OMX_IndexConfigTimeCurrentMediaTime:
		return "ConfigTimeCurrentMediaTime";
	case OMX_IndexConfigTimeCurrentWallTime:
		return "ConfigTimeCurrentWallTime";
	case OMX_IndexConfigTimeCurrentAudioReference:
		return "ConfigTimeCurrentAudioReference";
	case OMX_IndexConfigTimeMediaTimeRequest:
		return "ConfigTimeMediaTimeRequest";
	case OMX_IndexConfigTimeClientStartTime:
		return "ConfigTimeClientStartTime";
	case OMX_IndexConfigTimePosition:
		return "ConfigTimePosition";
	case OMX_IndexConfigTimeSeekMode:
		return "ConfigTimeSeekMode";
	default:
		return def;
	}
}

static inline const char *OmxToString(OMX_INDEXEXTTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_IndexConfigCallbackRequest:
		return "ConfigCallbackRequest";
	case OMX_IndexConfigCommitMode:
		return "ConfigCommitMode";
	case OMX_IndexConfigCommit:
		return "ConfigCommit";
	case OMX_IndexParamAudioAmebaOpus:
		return "OMX_IndexParamAudioAmebaOpus";
	case OMX_IndexParamAudioAmebaFlac:
		return "OMX_IndexParamAudioAmebaFlac";
	case OMX_IndexParamNalStreamFormatSupported:
		return "ParamNalStreamFormatSupported";
	case OMX_IndexParamNalStreamFormat:
		return "ParamNalStreamFormat";
	case OMX_IndexParamNalStreamFormatSelect:
		return "ParamNalStreamFormatSelect";
	default:
		return OmxToString((OMX_INDEXTYPE)i, def);
	}
}

static inline const char *OmxToString(OMX_ERRORTYPE i, const char *def = "??")
{
	switch (i) {
	case OMX_ErrorNone:
		return "None";
	case OMX_ErrorInsufficientResources:
		return "InsufficientResources";
	case OMX_ErrorUndefined:
		return "Undefined";
	case OMX_ErrorInvalidComponentName:
		return "InvalidComponentName";
	case OMX_ErrorComponentNotFound:
		return "ComponentNotFound";
	case OMX_ErrorInvalidComponent:
		return "InvalidComponent";
	case OMX_ErrorBadParameter:
		return "BadParameter";
	case OMX_ErrorNotImplemented:
		return "NotImplemented";
	case OMX_ErrorUnderflow:
		return "Underflow";
	case OMX_ErrorOverflow:
		return "Overflow";
	case OMX_ErrorHardware:
		return "Hardware";
	case OMX_ErrorInvalidState:
		return "InvalidState";
	case OMX_ErrorStreamCorrupt:
		return "StreamCorrupt";
	case OMX_ErrorPortsNotCompatible:
		return "PortsNotCompatible";
	case OMX_ErrorResourcesLost:
		return "ResourcesLost";
	case OMX_ErrorNoMore:
		return "NoMore";
	case OMX_ErrorVersionMismatch:
		return "VersionMismatch";
	case OMX_ErrorNotReady:
		return "NotReady";
	case OMX_ErrorTimeout:
		return "Timeout";
	case OMX_ErrorSameState:
		return "SameState";
	case OMX_ErrorResourcesPreempted:
		return "ResourcesPreempted";
	case OMX_ErrorPortUnresponsiveDuringAllocation:
		return "PortUnresponsiveDuringAllocation";
	case OMX_ErrorPortUnresponsiveDuringDeallocation:
		return "PortUnresponsiveDuringDeallocation";
	case OMX_ErrorPortUnresponsiveDuringStop:
		return "PortUnresponsiveDuringStop";
	case OMX_ErrorIncorrectStateTransition:
		return "IncorrectStateTransition";
	case OMX_ErrorIncorrectStateOperation:
		return "IncorrectStateOperation";
	case OMX_ErrorUnsupportedSetting:
		return "UnsupportedSetting";
	case OMX_ErrorUnsupportedIndex:
		return "UnsupportedIndex";
	case OMX_ErrorBadPortIndex:
		return "BadPortIndex";
	case OMX_ErrorPortUnpopulated:
		return "PortUnpopulated";
	case OMX_ErrorComponentSuspended:
		return "ComponentSuspended";
	case OMX_ErrorDynamicResourcesUnavailable:
		return "DynamicResourcesUnavailable";
	case OMX_ErrorMbErrorsInFrame:
		return "MbErrorsInFrame";
	case OMX_ErrorFormatNotDetected:
		return "FormatNotDetected";
	case OMX_ErrorContentPipeOpenFailed:
		return "ContentPipeOpenFailed";
	case OMX_ErrorContentPipeCreationFailed:
		return "ContentPipeCreationFailed";
	case OMX_ErrorSeperateTablesUsed:
		return "SeperateTablesUsed";
	case OMX_ErrorTunnelingUnsupported:
		return "TunnelingUnsupported";
	default:
		return def;
	}
}

static inline const char *OmxToString(res_t i, const char *def = "??")
{
	return ToString(i);
}

}  // namespace ameba::media

#endif // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_DEBUG_H
