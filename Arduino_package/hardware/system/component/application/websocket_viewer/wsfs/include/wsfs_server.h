/*
 * Copyright (c) 2025 Realtek Semiconductor Corp.
 * All rights reserved.
 */

#ifndef WSFS_SERVER_H
#define WSFS_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef enum wsfs_status {
	WSFS_STATUS_OK = 0,
	WSFS_STATUS_INVALID_ARGUMENT,
	WSFS_STATUS_ALLOCATION_FAILED,
	WSFS_STATUS_IO_ERROR,
	WSFS_STATUS_PROTOCOL_ERROR,
	WSFS_STATUS_INVALID_STATE
} wsfs_status_t;

typedef enum wsfs_opcode {
	WSFS_OPCODE_CONTINUATION = 0x0,
	WSFS_OPCODE_TEXT = 0x1,
	WSFS_OPCODE_BINARY = 0x2,
	WSFS_OPCODE_CLOSE = 0x8,
	WSFS_OPCODE_PING = 0x9,
	WSFS_OPCODE_PONG = 0xA
} wsfs_opcode_t;

typedef struct wsfs_message_view {
	wsfs_opcode_t opcode;
	const uint8_t *data;
	size_t length;
} wsfs_message_view_t;

struct wsfs_connection;
typedef struct wsfs_connection wsfs_connection_t;

typedef void (*wsfs_on_open_fn)(wsfs_connection_t *conn);
typedef void (*wsfs_on_message_fn)(wsfs_connection_t *conn,
				   const wsfs_message_view_t *msg);
typedef void (*wsfs_on_close_fn)(wsfs_connection_t *conn,
				 uint16_t close_code);

typedef struct wsfs_callbacks {
	wsfs_on_open_fn on_open;
	wsfs_on_message_fn on_message;
	wsfs_on_close_fn on_close;
} wsfs_callbacks_t;

typedef struct wsfs_server_config {
	const char *host;
	uint16_t port;
	size_t max_clients;
	size_t recv_buffer_size;
	size_t max_frame_size;
	size_t handshake_buffer_cap;
	wsfs_callbacks_t callbacks;
} wsfs_server_config_t;

typedef struct wsfs_server {
	void *impl;
} wsfs_server_t;

struct wsfs_connection {
	void *impl;
};

wsfs_status_t wsfs_server_init(wsfs_server_t *server,
			       const wsfs_server_config_t *config);
void wsfs_server_deinit(wsfs_server_t *server);
wsfs_status_t wsfs_server_run(wsfs_server_t *server);
void wsfs_server_request_stop(wsfs_server_t *server);

wsfs_status_t wsfs_connection_send_text(wsfs_connection_t *conn,
					const char *text, size_t length);
wsfs_status_t wsfs_connection_send_binary(wsfs_connection_t *conn,
					  const uint8_t *payload,
					  size_t length);
wsfs_status_t wsfs_connection_close(wsfs_connection_t *conn,
				    uint16_t close_code);

void wsfs_connection_set_user_data(wsfs_connection_t *conn, void *data);
void *wsfs_connection_get_user_data(const wsfs_connection_t *conn);
const char *wsfs_connection_peer_ip(const wsfs_connection_t *conn);
uint16_t wsfs_connection_peer_port(const wsfs_connection_t *conn);

void wsfs_server_config_defaults(wsfs_server_config_t *config);

#ifdef __cplusplus
}
#endif

#endif /* WSFS_SERVER_H */
