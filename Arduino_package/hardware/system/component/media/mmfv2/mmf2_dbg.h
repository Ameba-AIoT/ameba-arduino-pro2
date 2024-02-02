#ifndef __MMF_DBG_H_
#define __MMF_DBG_H_

#include <stdint.h>

// Define debug group
#define	_MMF_DBG_RTSP_              0x00000001
#define	_MMF_DBG_RTP_               0x00000002
#define	_MMF_DBG_ISP_               0x00000004
#define	_MMF_DBG_ENCODER_           0x00000008
#define	_MMF_DBG_VIDEO_             0x00000010
#define	_MMF_DBG_AUDIO_             0x00000020
#define	_MMF_DBG_MODULE_            0x00000040
#define	_MMF_DBG_LINKER_            0x00000080

extern uint32_t ConfigDebugMmfErr;
extern uint32_t ConfigDebugMmfWarn;
extern uint32_t ConfigDebugMmfInfo;

#define DBG_MMF_ERR_MSG_ON(x)       (ConfigDebugMmfErr |= (x))
#define DBG_MMF_WARN_MSG_ON(x)      (ConfigDebugMmfWarn |= (x))
#define DBG_MMF_INFO_MSG_ON(x)      (ConfigDebugMmfInfo |= (x))

#define DBG_MMF_ERR_MSG_OFF(x)      (ConfigDebugMmfErr &= ~(x))
#define DBG_MMF_WARN_MSG_OFF(x)     (ConfigDebugMmfWarn &= ~(x))
#define DBG_MMF_INFO_MSG_OFF(x)     (ConfigDebugMmfInfo &= ~(x))


#define RTSP_ERR_PREFIX         "[RTSP Err]"
#define RTSP_WARN_PREFIX        "[RTSP Wrn]"
#define RTSP_INFO_PREFIX        "[RTSP Inf]"

#define RTP_ERR_PREFIX         "[RTP Err]"
#define RTP_WARN_PREFIX        "[RTP Wrn]"
#define RTP_INFO_PREFIX        "[RTP Inf]"

#ifndef ISP_ERR_PREFIX
#define ISP_ERR_PREFIX         "[ISP Err]"
#endif
#ifndef ISP_WARN_PREFIX
#define ISP_WARN_PREFIX        "[ISP Wrn]"
#endif
#ifndef ISP_INFO_PREFIX
#define ISP_INFO_PREFIX        "[ISP Inf]"
#endif

#ifndef ENCODER_ERR_PREFIX
#define ENCODER_ERR_PREFIX         "[Enc Err]"
#endif
#ifndef ENCODER_WARN_PREFIX
#define ENCODER_WARN_PREFIX        "[Enc Wrn]"
#endif
#ifndef ENCODER_INFO_PREFIX
#define ENCODER_INFO_PREFIX        "[Enc Inf]"
#endif

#ifndef VIDEO_ERR_PREFIX
#define VIDEO_ERR_PREFIX         "[VID Err]"
#endif
#ifndef VIDEO_WARN_PREFIX
#define VIDEO_WARN_PREFIX        "[VID Wrn]"
#endif
#ifndef VIDEO_INFO_PREFIX
#define VIDEO_INFO_PREFIX        "[VID Inf]"
#endif

#ifndef AUDIO_ERR_PREFIX
#define AUDIO_ERR_PREFIX         "[AUD Err]"
#endif
#ifndef AUDIO_WARN_PREFIX
#define AUDIO_WARN_PREFIX        "[AUD Wrn]"
#endif
#ifndef AUDIO_INFO_PREFIX
#define AUDIO_INFO_PREFIX        "[AUD Inf]"
#endif

#ifndef MODULE_ERR_PREFIX
#define MODULE_ERR_PREFIX		 "[MODULE Err]"
#endif
#ifndef MODULE_WARN_PREFIX
#define MODULE_WARN_PREFIX		 "[MODULE Wrn]"
#endif
#ifndef MODULE_INFO_PREFIX
#define MODULE_INFO_PREFIX		 "[MODULE Inf]"
#endif

#ifndef LINKER_ERR_PREFIX
#define LINKER_ERR_PREFIX		 "[LINKER Err]"
#endif
#ifndef LINKER_WARN_PREFIX
#define LINKER_WARN_PREFIX		 "[LINKER Wrn]"
#endif
#ifndef LINKER_INFO_PREFIX
#define LINKER_INFO_PREFIX		 "[LINKER Inf]"
#endif

#define MMF_PRINTK      printf

#define RTSP_DBG_ERROR(...)													\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_RTSP_)						\
					MMF_PRINTK("\n\r" RTSP_ERR_PREFIX __VA_ARGS__);			\
			}while(0)
#define RTP_DBG_ERROR(...)													\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_RTP_)						\
					MMF_PRINTK("\n\r" RTP_ERR_PREFIX __VA_ARGS__);			\
			}while(0)
#ifdef ISP_DBG_ERROR
#undef ISP_DBG_ERROR
#define ISP_DBG_ERROR(...)													\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_ISP_)						\
					MMF_PRINTK("\n\r" ISP_ERR_PREFIX __VA_ARGS__);			\
			}while(0)
#endif
#define ENCODER_DBG_ERROR(...)												\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_ENCODER_)					\
					MMF_PRINTK("\n\r" ENCODER_ERR_PREFIX __VA_ARGS__);		\
			}while(0)

#define VIDEO_DBG_ERROR(...)												\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_VIDEO_)					\
					MMF_PRINTK("\n\r" VIDEO_ERR_PREFIX __VA_ARGS__);		\
			}while(0)
#define AUDIO_DBG_ERROR(...)												\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_AUDIO_)					\
					MMF_PRINTK("\n\r" AUDIO_ERR_PREFIX __VA_ARGS__);		\
			}while(0)
#define MODULE_DBG_ERROR(...)												\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_MODULE_)					\
					MMF_PRINTK("\n\r" MODULE_ERR_PREFIX __VA_ARGS__);		\
			}while(0)
#define LINKER_DBG_ERROR(...)												\
			do {															\
				if (ConfigDebugMmfErr&_MMF_DBG_LINKER_)					\
					MMF_PRINTK("\n\r" LINKER_ERR_PREFIX __VA_ARGS__);		\
			}while(0)

// DBG_WARNING
#define RTSP_DBG_WARNING(...)												\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_RTSP_)						\
					MMF_PRINTK("\n\r" RTSP_WARN_PREFIX __VA_ARGS__);		\
			}while(0)
#define RTP_DBG_WARNING(...)												\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_RTP_)						\
					MMF_PRINTK("\n\r" RTP_WARN_PREFIX __VA_ARGS__);			\
			}while(0)
#define ISP_DBG_WARNING(...)												\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_ISP_)						\
					MMF_PRINTK("\n\r" ISP_WARN_PREFIX __VA_ARGS__);			\
			}while(0)
#define ENCODER_DBG_WARNING(...)											\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_ENCODER_)					\
					MMF_PRINTK("\n\r" ENCODER_WARN_PREFIX __VA_ARGS__);		\
			}while(0)
#define VIDEO_DBG_WARNING(...)											\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_VIDEO_)					\
					MMF_PRINTK("\n\r" VIDEO_WARN_PREFIX __VA_ARGS__);		\
			}while(0)
#define AUDIO_DBG_WARNING(...)											\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_AUDIO_)					\
					MMF_PRINTK("\n\r" AUDIO_WARN_PREFIX __VA_ARGS__);		\
			}while(0)
#define MODULE_DBG_WARNING(...)												\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_MODULE_)					\
					MMF_PRINTK("\n\r" MODULE_WARN_PREFIX __VA_ARGS__);		\
			}while(0)
#define LINKER_DBG_WARNING(...)												\
			do {															\
				if (ConfigDebugMmfWarn&_MMF_DBG_LINKER_)					\
					MMF_PRINTK("\n\r" LINKER_WARN_PREFIX __VA_ARGS__);		\
			}while(0)

// DBG_INFO
#define RTSP_DBG_INFO(...)													\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_RTSP_)						\
					MMF_PRINTK("\n\r" RTSP_INFO_PREFIX __VA_ARGS__);		\
			}while(0)
#define RTP_DBG_INFO(...)													\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_RTP_)						\
					MMF_PRINTK("\n\r" RTP_INFO_PREFIX __VA_ARGS__);			\
			}while(0)
#define ISP_DBG_INFO(...)													\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_ISP_)						\
					MMF_PRINTK("\n\r" ISP_INFO_PREFIX __VA_ARGS__);			\
			}while(0)
#define ENCODER_DBG_INFO(...)												\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_ENCODER_)					\
					MMF_PRINTK("\n\r" ENCODER_INFO_PREFIX __VA_ARGS__);		\
			}while(0)
#define VIDEO_DBG_INFO(...)											\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_VIDEO_)					\
					MMF_PRINTK("\n\r" VIDEO_INFO_PREFIX __VA_ARGS__);		\
			}while(0)
#define AUDIO_DBG_INFO(...)											\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_AUDIO_)					\
					MMF_PRINTK("\n\r" AUDIO_INFO_PREFIX __VA_ARGS__);		\
			}while(0)
#define MODULE_DBG_INFO(...)												\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_MODULE_)					\
					MMF_PRINTK("\n\r" MODULE_INFO_PREFIX __VA_ARGS__);		\
			}while(0)
#define LINKER_DBG_INFO(...)												\
			do {															\
				if (ConfigDebugMmfInfo&_MMF_DBG_LINKER_)					\
					MMF_PRINTK("\n\r" LINKER_INFO_PREFIX __VA_ARGS__);		\
			}while(0)
#endif

void mm_set_abort_func(void (*func)(void));

void mmf2_abort(void);