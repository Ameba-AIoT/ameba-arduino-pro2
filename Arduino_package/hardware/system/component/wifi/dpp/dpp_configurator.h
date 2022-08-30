#ifndef __DPP_CONFIGURATOR_H__
#define __DPP_CONFIGURATOR_H__
#include "dpp.h"

int DPP_configurator_set_BR(dpp_adapter *pdpp_adapter, u8 *BR_QR_SCAN, u32 BR_QR_len);
int DPP_Init_Configurator(dpp_adapter *pdpp_adapter);
void DPP_Configurator_Config_callback(u8 *buf, u32 length, void *userdata);
u32 DPP_On_Auth_Response(dpp_adapter *pdpp_adapter, u8 *buf, u32 length);
void DPP_Send_Auth_Confirm(dpp_adapter *pdpp_adapter);
u32 DPP_On_Configuration_Request(dpp_adapter *padapter, u8 *buf, u32 length);
#endif