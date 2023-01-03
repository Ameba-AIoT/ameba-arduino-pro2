#ifndef __ROT_DEBUG_H__
#define __ROT_DEBUG_H__

//#define CFG_ROT_DEBUG

#ifdef CFG_ROT_DEBUG

#define ROT_DRV_NAME    ROT
/*
 * Debug level definiation
 */
#define ROT_DBG_LV_ERROR        0x01
#define ROT_DBG_LV_TRACE        0x02
#define ROT_DBG_LV_REGDUMP      0x04
#define ROT_DBG_LV_INFO         0x08
#define ROT_DBG_LV_REGALL       0x10
#define ROT_DBG_LV_ALL          0xff

#define ROT_DBG_LEVEL   ROT_DBG_LV_ERROR

#define ROT_DBG(fmt, args...)	printf(fmt, ##args)

/* Functions Define */
#define ROT_DBG_ERROR(fmt, args...)                                                      \
                do {                                                                            \
                        ROT_DBG("[ROT] E/%s(%d) :" fmt "\n",__func__, __LINE__ , ##args);       \
                } while(0)
#define ROT_DBG_INFO(fmt, args...)                                                       \
                do {                                                                            \
                        if (ROT_DBG_LEVEL & ROT_DBG_LV_INFO) {                                  \
                                ROT_DBG("[ROT] I/%s(%d) :" fmt"\n",__func__, __LINE__, ##args); \
                        }                                                                       \
                } while(0)
#else
#define ROT_DBG_ERROR(fmt, args...)      do { } while(0)
#define ROT_DBG_INFO(fmt, args...)       do { } while(0)
#endif

#endif /* __ROT_DEBUG_H__ */
