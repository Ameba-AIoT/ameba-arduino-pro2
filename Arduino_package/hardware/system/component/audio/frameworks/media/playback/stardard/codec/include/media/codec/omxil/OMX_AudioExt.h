/*
 * Copyright (c) 2010 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/** OMX_AudioExt.h - OpenMax IL version 1.1.2
 * The OMX_AudioExt header file contains extensions to the
 * definitions used by both the application and the component to
 * access video items.
 */

#ifndef OMX_AudioExt_h
#define OMX_AudioExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Core.h>

typedef enum OMX_AUDIO_CODINGEXTTYPE {
	OMX_AUDIO_CodingAmebaUnused = OMX_AUDIO_CodingKhronosExtensions + 0x00100000,
	OMX_AUDIO_CodingAmebaOPUS,        /**< OPUS encoded data */
	OMX_AUDIO_CodingAmebaFLAC,        /**< Any variant of FLAC encoded data */
} OMX_AUDIO_CODINGEXTTYPE;

typedef struct OMX_AUDIO_PARAM_AMEBA_OPUSTYPE {
	OMX_U32 nSize;            /**< size of the structure in bytes */
	OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
	OMX_U32 nPortIndex;       /**< port that this structure applies to */
	OMX_U32 nChannels;        /**< Number of channels */
	OMX_U32 nBitRate;         /**< Bit rate of the encoded data data.  Use 0 for variable
                                   rate or unknown bit rates. Encoding is set to the
                                   bitrate closest to specified  value (in bps) */
	OMX_U32 nSampleRate;      /**< Sampling rate of the source data.  Use 0 for
                                   variable or unknown sampling rate. */
	OMX_U32 nAudioBandWidth;  /**< Audio band width (in Hz) to which an encoder should
                                   limit the audio signal. Use 0 to let encoder decide */
} OMX_AUDIO_PARAM_AMEBA_OPUSTYPE;

/** FLAC params */
typedef struct OMX_AUDIO_PARAM_AMEBAFLACTYPE {
	OMX_U32 nSize;            /**< size of the structure in bytes */
	OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
	OMX_U32 nPortIndex;       /**< port that this structure applies to */
	OMX_U32 nChannels;        /**< Number of channels */
	OMX_U32 nSampleRate;      /**< Sampling rate of the source data.  Use 0 for
                                   unknown sampling rate. */
	OMX_U32 nCompressionLevel;/**< FLAC compression level, from 0 (fastest compression)
                                   to 8 (highest compression */
} OMX_AUDIO_PARAM_FLACTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_AudioExt_h */
/* File EOF */