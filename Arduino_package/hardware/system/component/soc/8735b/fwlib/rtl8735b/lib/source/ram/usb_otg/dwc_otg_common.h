/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
#include "basic_types.h"
#include "osdep_service.h"
//#include "va_list.h"
#include <stdarg.h>

#include "diag.h"
#include "dwc_otg_dbg.h"
#include "dwc_os.h"


typedef struct _RAM_OTG_FUNCTION_TABLE_ {
	VOID   *(*RamMemSet)(void *dest, int byte, SIZE_T size);
	VOID   *(*RamMemCpy)(void *dest, void const *src, SIZE_T size);
	int (*RamMemCmp)(void const *m1, void const *m2, SIZE_T size);
	int (*RamStrnCmp)(const char *s1, const char *s2, SIZE_T size);
	int (*RamStrCmp)(const char *s1, const char *s2);
	SIZE_T(*RamStrLen)(char const *str);
	char   *(*RamStrCpy)(char *to, char const *from);
	char   *(*RamStrDup)(char const *str);
	int (*RamAtoi)(const char *str, int32_t *value);
	int (*RamAtoui)(const char *str, uint32_t *value);
	int (*RamVsnPrintf)(char *str, int size, const char *format, ...);
	u32(*RamSPrintf)(u8 *buf, const char *fmt, ...);
	int (*RamSnPrintf)(char *dst, int count, const char *src, ...);
	u8     *(*RamZmalloc)(u32 sz);
	u8     *(*RamZmallocAtomic)(u32 sz);
	VOID (*RamMfree)(u8 *pbuf, u32 sz);
	dwc_spinlock_t    *(*RamSpinlockAlloc)(void);
	VOID (*RamSpinlockFree)(dwc_spinlock_t *lock);
	VOID (*RamSpinlock)(dwc_spinlock_t *lock);
	VOID (*RamSpinUnlock)(dwc_spinlock_t *lock);
	VOID (*RamSpinIrqSave)(dwc_spinlock_t *lock, dwc_irqflags_t *flags);
	VOID (*RamSpinIrqRestore)(dwc_spinlock_t *lock, dwc_irqflags_t flags);
	dwc_mutex_t *(*RamMutexAlloc)(void);
	VOID (*RamMutexFree)(dwc_mutex_t *mutex);
	VOID (*RamMutexLock)(dwc_mutex_t *mutex);
	int (*RamMutexTryLock)(dwc_mutex_t *mutex);
	VOID (*RamMutexUnLock)(dwc_mutex_t *mutex);
	uint32_t(*RamUDelay)(uint32_t usecs);
	void (*RamMSleep)(uint32_t msecs);
	VOID (*timer_callback)(unsigned long data);
	dwc_timer_t *(*RamTimerAlloc)(char *name, dwc_timer_callback_t cb, void *data);
	VOID (*RamTimerFree)(dwc_timer_t *timer);
	VOID (*RamTimerSche)(dwc_timer_t *timer, uint32_t time_ms);
	VOID (*RamTimerCancel)(dwc_timer_t *timer);
	VOID (*RamEnterCritical)(void);
	VOID (*RamExitCritical)(void);
} RAM_OTG_FUNCTION_TABLE, *PRAM_OTG_FUNCTION_TABLE;



// Global Variable
extern RAM_OTG_FUNCTION_TABLE gRamOTGFunTbl;

// Funtion Prototype
// ROM
void dwc_otg_wrapper_init_boot(IN  VOID);
void dwc_otg_power_init(IN VOID);

VOID RtlInitListhead_Otg(IN  _list *list);
u32    RtlIsListEmpty_Otg(IN  _list *phead);
VOID RtlListInsertHead_Otg(IN  _list *plist, IN  _list *phead);
VOID RtlListInsertTail_Otg(IN  _list *plist, IN  _list *phead);
_list *RtlListGetNext_Otg(IN  _list *plist);
VOID RtlListDelete_Otg(IN _list *plist);

extern  char *DWC_STRDUP_ROM(char const *str);
extern  int DWC_ATOI_ROM(const char *str, int32_t *value);
extern  int DWC_ATOUI_ROM(const char *str, uint32_t *value);
// RAM



