#ifndef _H265_H
#define _H265_H

#include "dlist.h"		//list management
#include "basic_types.h"
#include "osdep_service.h"
//#include "osdep_api.h"

#define H265_DEBUG 0

#if H265_DEBUG
#define H265_PRINTF(fmt, args...)	printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#define H265_ERROR(fmt, args...)	printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#else
#define H265_PRINTF(fmt, args...)
#define H265_ERROR(fmt, args...)
#endif

#define MAX_NUM_NAL_PER_FRM     4

#define H265_VPS 	0x40
#define H265_SPS 	0x42
#define H265_PPS 	0x44
#define H265_IFRAME     0x26
#define H265_PFRAME     0X02

struct rtp_nal_obj_ext {
	u8 start_code_len;
	unsigned char nal_header;
	unsigned char nal_header_ext;
	u8 is_fu_start;
	u8 is_fu_end;
	u8 must_not_drop;
	u8 do_not_send;
	int offset;
};

struct rtp_h265_obj {
	int num_nal;
	struct rtp_nal_obj_ext nal_obj[MAX_NUM_NAL_PER_FRM];
};

#endif /*_H265_H*/

#if 0

#ifndef _H265_H
#define _H265_H

#include "dlist.h"			//list management
#include "basic_types.h"
#include "osdep_service.h"
//#include "osdep_api.h"

#define H265_DEBUG 0

#if H265_DEBUG
#define H265_PRINTF(fmt, args...)	printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#define H265_ERROR(fmt, args...)	printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#else
#define H265_PRINTF(fmt, args...)
#define H265_ERROR(fmt, args...)
#endif

/* in favor of rtp fragmentation */
struct rtp_h265_obj {
	u8 start_code_len;
	unsigned char nal_header;
	u8 is_fu_start;
	u8 is_fu_end;
	u8 must_not_drop;
};


/********************************h265 over rtp******************************/


#endif /*_H265_H*/
#endif