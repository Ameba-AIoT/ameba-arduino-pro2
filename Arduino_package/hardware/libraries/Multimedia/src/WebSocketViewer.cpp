#include <Arduino.h>
#include "WebSocketViewer.h"
#include "htdocs.h"

WebSocketViewer::WebSocketViewer(void)
{
}

WebSocketViewer::~WebSocketViewer(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }

    if (deinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Websocket viewer deinit failed\n");
    }
}

int WebSocketViewer::loadWebResourcesFromSD(unsigned char **buf, int *len)
{
    vfs_init(NULL);
    ret = vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);
    if (ret < 0) {
        printf("vfs_user_register fail (%d)\n\r", ret);
        return -1;
    }

    FILE *fp = fopen("sd:/htdocs.bin", "r");
    if (fp == NULL) {
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    *len = ftell(fp);
    printf("htdocs size:%d bytes\r\n", *len);
    fseek(fp, 0, SEEK_SET);
    *buf = (unsigned char *)malloc(*len);
    if (buf == NULL) {
        printf("malloc for %s failed\r\n", "sd:/htdocs.bin");
        fclose(fp);
        return -1;
    }
    fseek(fp, 0, SEEK_SET);
    fread(*buf, 1, *len, fp);
    fclose(fp);
    return 0;
}

void WebSocketViewer::loadWebResources(int websocket_from_sd)
{
    if (websocket_from_sd == 1) {
        // From sd card
        ret = loadWebResourcesFromSD(&websocket_viewer_buf, &websocket_viewer_len);
        if (ret < 0) {
            printf("Init fail\r\n");
            return;
        } else {
            printf("buf %p len %d\r\n", websocket_viewer_buf, websocket_viewer_len);
        }
    } else {
        // From array
        websocket_viewer_buf = (unsigned char *)htdocs_data;
        websocket_viewer_len = htdocs_len;
    }
}

void WebSocketViewer::init(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&websocket_viewer_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] Audio init failed\n");
        return;
    }

    if (_p_mmf_context) {
        mm_module_ctrl(_p_mmf_context, CMD_WEB_VIEWER_SET_BUF, (int)websocket_viewer_buf);
        mm_module_ctrl(_p_mmf_context, CMD_WEB_VIEWER_SET_LEN, (int)websocket_viewer_len);
    } else {
        printf("web viewer open fail\n\r");
    }
}

void WebSocketViewer::begin(void)
{
    mm_module_ctrl(_p_mmf_context, CMD_WEB_VIEWER_APPLY, 0);
}

mm_context_t *WebSocketViewer::deinit(mm_context_t *p)
{
    return mm_module_close(p);
}
