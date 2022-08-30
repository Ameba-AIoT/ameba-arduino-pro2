/**************************************************************************************************
  Filename:       joylink_adapter.h
  Revised:        $Date: 2015-10-14
  Revision:       $Revision: 1.0, Zhang Hua

  Description:    This file contains the Joylink profile definitions and
                  prototypes.

  Copyright 2010 - 2013 JD.COM. All rights reserved.

**************************************************************************************************/


#ifndef __JOYLINK_ADAPTER_H__
#define __JOYLINK_ADAPTER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "joylink_sdk.h"

typedef struct {
	uint32_t second;
	uint32_t usecond;
} jl_timestamp_t;

/*************************************************
Function: jl_adapter_send_data
Description: SDK适配接口，GATTS Characteristic发送数据
Calls: GATTS Characteristic发送数据接口
Called By: @jl_send_frame：SDK内部函数
Input: @data：发送的数据
       @data_len：发送的数据长度
Output: None
Return: 0：成功
       -1：失败
Others:
*************************************************/
int32_t jl_adapter_send_data(uint8_t *buf, uint32_t size);

/*************************************************
Function: jl_adapter_set_config_data
Description: SDK适配接口，获取配网与绑定参数
Calls: 配网与绑定接口
Called By: @jl_process_user_data：SDK内部函数
Input: @data->ssid：配网数据，WiFi SSID
       @data->ssid_len：WiFi SSID长度
       @data->password：配网数据，WiFi密码
       @data->password_len：WiFi密码长度
       @data->url：绑定云端链接
       @data->url_len：绑定云端链接长度
       @data->token：绑定参数
       @data->token_len：绑定参数长度
Output: None
Return: 0：成功
       -1：失败
Others: 设置激活绑定接口：joylink_dev_active_start(data->url, data->token);
*************************************************/
int32_t jl_adapter_set_config_data(jl_net_config_data_t *data);

/*************************************************
Function: jl_adapter_set_system_time
Description: SDK适配接口，设置系统时间
Calls: 设置系统时间接口
Called By: SDK内部函数
Input: @time->second：秒
       @time->usecond：微妙
Output: None
Return: 0：成功
       -1：失败
Others: None
*************************************************/
int32_t jl_adapter_set_system_time(jl_timestamp_t *time);

#ifdef __cplusplus
}
#endif

#endif /* __JOYLINK_ADAPTER_H__ */
