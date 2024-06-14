/************************************************************************************************/
// qr_code_stdlib.c
/************************************************************************************************/

#include "config.h"

#if USE_QR_CODE_STDLIB

#include "osdep_service.h"

void* qr_code_malloc(u32 sz)
{
    void* pbuf = rtw_malloc(sz);
    if (pbuf == NULL) {
        printf("%s: pbuf alloc fail!\r\n", __FUNCTION__);
    }
    return pbuf;
}

void qr_code_free(void* pbuf)
{
    rtw_free(pbuf);
}

void qr_code_memcpy(void* dst, void* src, u32 sz)
{
    rtw_memcpy(dst, src, sz);
}

int qr_code_memcmp(void* dst, void* src, u32 sz)
{
    return !rtw_memcmp(dst, src, sz);
}

void qr_code_memset(void* pbuf, int c, u32 sz)
{
    rtw_memset(pbuf, c, sz);
}

void* qr_code_calloc(u32 cnt, u32 sz)
{
    void* pbuf = rtw_malloc(cnt * sz);
    if (pbuf == NULL) {
        printf("%s: pbuf alloc fail!\r\n", __FUNCTION__);
    } else {
        rtw_memset(pbuf, 0, cnt * sz);
    }
    return pbuf;
}

void* qr_code_realloc(void* old_pbuf, u32 new_sz)
{
    void* new_pbuf;

    if (old_pbuf == NULL) {
        new_pbuf = rtw_malloc(new_sz);
        if (new_pbuf == NULL) {
            printf("%s: new_pbuf alloc fail!\r\n", __FUNCTION__);
        }
        return new_pbuf;
    }

    if (new_sz == 0) {
        rtw_free(new_sz);
        return NULL;
    }

    new_pbuf = rtw_malloc(new_sz);
    if (new_pbuf == NULL) {
        printf("%s: new_pbuf alloc fail!\r\n", __FUNCTION__);
    } else {
        rtw_memcpy(new_pbuf, old_pbuf, new_sz);
        rtw_free(old_pbuf);
    }
    return new_pbuf;
}

void* qr_code_memmove(void* dst, void* src, u32 sz)
{
    void* pbuf;

    if (dst == NULL || src == NULL) {
        return NULL;
    }

    if (sz == 0) {
        return dst;
    }

    pbuf = rtw_malloc(sz);
    if (pbuf == NULL) {
        printf("%s: pbuf alloc fail!\r\n", __FUNCTION__);
        return NULL;
    } else {
        rtw_memcpy(pbuf, src, sz);
        rtw_memcpy(dst, pbuf, sz);
        rtw_free(pbuf);
        return dst;
    }
}

void* qr_code_memchr(void* pbuf, int c, u32 cnt)    // QR_MODE_ALNUM
{
    return NULL;
}

#endif
