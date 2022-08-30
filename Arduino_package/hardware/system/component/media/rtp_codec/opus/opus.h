
#ifndef _OPUS_H
#define _OPUS_H

#include "dlist.h"      //list management
#include "basic_types.h"
#include "osdep_service.h"
//#include "osdep_api.h"

#define OPUS_DEBUG 1

#if OPUS_DEBUG
#define OPUS_PRINTF(fmt, args...)    printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#define OPUS_ERROR(fmt, args...)     printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#else
#define OPUS_PRINTF(fmt, args...)
#define OPUS_ERROR(fmt, args...)
#endif


//struct rtp_OPUS_obj {
//};


/*for debug purpose*/

#endif /*_OPUS_H*/