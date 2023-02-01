/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
* @file     a2dp_app_config.h
* @brief    a2dp trx event id.
* @details  
* @author   sherman
* @date     2021-10-20
* @version  v1.0
* *************************************************************************************
*/

#ifndef _A2DP_APP_CONFIG_H_
#define _A2DP_APP_CONFIG_H_

/* ------------------------------- Data Types ------------------------------- */

enum A2DP_SINK_EVENT {
	A2DP_SINK_IPC_HANDSHAKE_COMPLETE = 0,
	A2DP_SINK_STREAM_DATA_IN ,
	A2DP_SINK_STREAM_DATA_HANDLE_INIT ,
	A2DP_SINK_STREAM_DATA_HANDLE_DEINIT ,
	/* playback status */
	A2DP_SINK_PLAYBACK_PLAYING ,
	A2DP_SINK_PLAYBACK_STOPPED ,
	A2DP_SINK_PLAYBACK_PAUSED ,
	A2DP_SINK_PLAYBACK_FWD_SEEK ,
	A2DP_SINK_PLAYBACK_REV_SEEK ,
	/* volume set status */
	A2DP_SINK_VOLUME_SET
};

enum A2DP_CODEC_TYPE {
	A2DP_SBC_CODEC = 0
};

#endif /* _A2DP_APP_CONFIG_H_ */