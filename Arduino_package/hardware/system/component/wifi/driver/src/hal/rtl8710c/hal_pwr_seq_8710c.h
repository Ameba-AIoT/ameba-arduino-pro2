#ifndef REALTEK_POWER_SEQUENCE_8710C
#define REALTEK_POWER_SEQUENCE_8710C

#include "HalPwrSeqCmd.h"

/*
	Check document WM-20130111-JackieLau-RTL8723B_Power_Architecture v02.vsd
	There are 6 HW Power States:
	0: POFF--Power Off
	1: PDN--Power Down
	2: CARDEMU--Card Emulation
	3: ACT--Active Mode
	4: LPS--Low Power State
	5: SUS--Suspend

	The transision from different states are defined below
	TRANS_CARDEMU_TO_ACT
	TRANS_ACT_TO_CARDEMU
	TRANS_CARDEMU_TO_SUS
	TRANS_SUS_TO_CARDEMU
	TRANS_CARDEMU_TO_PDN
	TRANS_ACT_TO_LPS
	TRANS_LPS_TO_ACT

	TRANS_END
*/

#define RTL8710C_TRANS_CARDEMU_TO_ACT \
	/* format */									\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/ 		\
	{0x0050, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(0)|BIT(1)), 0}, /*0x50[0:1] = 0x0 ungate XTAL AFE/RF Clock output*/ \
	{0x0055, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(7)), (BIT(7))}, /*0x54[15] = 0x1 enable BIT_CK5M_EN*/ \
	{0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(0)), (BIT(0))}, /*0x04[24] = 0x1 power on RF module*/ \
	{0x0004, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(3), BIT(3)}, /*0x04[3] = 1 enable MAC partial on circuit*/ \
	{0x0004, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)}, /*0x04[0] = 1 enable MAC PMC function*/ \
	{0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), BIT(0)}, /*0x20[0] = 1 turn on FSM, inform WLAN PMC to power on WLAN*/ \
	{0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_POLLING, BIT(0), 0}, /*polling until 0x20[0] = 0, wait until Power Ready*/ \
	{0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(0)|BIT(1)), (BIT(0)|BIT(1))}, /*0x04[16:17] = 0x3 enable BB*/ \
	{0x087c, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(31)), (0)}, /*0x87c[31] = 0, 1: stop CK320&CK88*/ \
	{0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (BIT(1)|BIT(2)), (BIT(1)|BIT(2))}, /*0x04[25:26] = 0x3, bit[25] 1: Reset RF Module (low active), bit[26] 1: Reset RF SDM Module (low active)*/ \
	{0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK, PWR_BASEADDR_MAC, PWR_CMD_WRITE, (0xFF), (0)}, /*0x300[15:8] = 0x0 AXI DMA*/ \

#define RTL8710C_TRANS_ACT_TO_CARDEMU													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, (BIT(1)|BIT(2)), 0},/*0x4[26:25] = 0 disable RF module*/	\
	{0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(0), 0},/*0x04[16] = 0 Whole BB is reset*/	\
	{0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), BIT(1)}, /*0x20[1] = 1 turn off MAC by HW state machine*/	\
	{0x0020, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT(1), 0}, /*wait till 0x20[1] = 0 polling until return 0 to disable*/	\
	{0x0004, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0}, /*0x4[0] = 0 Disable WLAN PMC function*/ \
	{0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC, PWR_CMD_WRITE, BIT(0), 0}, /*0x4[24] = 0 power off RF*/ \

#define RTL8710C_TRANS_CARDDIS_TO_CARDEMU \
	/* format */
/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/ 	\

#define RTL8710C_TRANS_CARDEMU_TO_CARDDIS \
	/* format */							\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/ 		\

#define RTL8710C_TRANS_END															\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0xFFFF, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,0,PWR_CMD_END, 0, 0}, //

extern WLAN_PWR_CFG rtl8710C_card_enable_flow[];
extern WLAN_PWR_CFG rtl8710C_card_disable_flow[];

#endif

