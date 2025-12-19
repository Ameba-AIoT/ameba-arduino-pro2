#ifndef __WEBSOCKETVIEWER_H__
#define __WEBSOCKETVIEWER_H__

#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "vfs.h"

#ifdef __cplusplus
}
#endif

#include "module_web_viewer.h"

class WebSocketViewer: public MMFModule {
public:
    WebSocketViewer(void);
    ~WebSocketViewer(void);

    int loadWebResourcesFromSD(unsigned char **buf, int *len);
    void loadWebResources(int websocket_from_sd);
    void init(void);
    void begin(void);
    mm_context_t *deinit(mm_context_t *p);

private:
    int ret = 0;
    unsigned char *websocket_viewer_buf = NULL;
    int websocket_viewer_len = 0;
};

#endif
