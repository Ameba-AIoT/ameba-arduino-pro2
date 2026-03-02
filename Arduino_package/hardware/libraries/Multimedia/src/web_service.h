/*
 * Copyright (c) 2025 Realtek Semiconductor Corp.
 * All rights reserved.
 */

#ifndef WEB_SERVICE_H
#define WEB_SERVICE_H
void start_websocket_viewer(void);
int wsh264_send_frame(int stream_id, uint8_t *data_addr, uint32_t size);
void ws_viewer_set_buf(unsigned int buf);
void ws_viewer_set_len(unsigned int len);
#endif /* WEB_SERVICE_H */
