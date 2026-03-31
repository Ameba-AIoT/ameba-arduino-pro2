/*
 * Copyright (c) 2025 Realtek Semiconductor Corp.
 * All rights reserved.
 */

#ifndef WSFS_INTERNAL_H
#define WSFS_INTERNAL_H

#include <signal.h>
#include <stdint.h>
#include <stddef.h>

#include "wsfs_socket.h"
#include "wsfs_server.h"

/* Log levels */
#define WSFS_LOG_NONE  0
#define WSFS_LOG_ERROR 1
#define WSFS_LOG_INFO  2
#define WSFS_LOG_DEBUG 3

#define WSFS_LOG_LEVEL WSFS_LOG_DEBUG

/* Level-controlled print macros */
#if WSFS_LOG_LEVEL >= WSFS_LOG_ERROR
#define WSFS_ERROR_PRINTF(...) do { printf("[ERROR] %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); } while (0)
#else
#define WSFS_ERROR_PRINTF(...) do { } while (0)
#endif

#if WSFS_LOG_LEVEL >= WSFS_LOG_INFO
#define WSFS_INFO_PRINTF(...) do { printf("[INFO] %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); } while (0)
#else
#define WSFS_INFO_PRINTF(...) do { } while (0)
#endif

#if WSFS_LOG_LEVEL >= WSFS_LOG_DEBUG
#define WSFS_DEBUG_PRINTF(...) do { printf("[DEBUG] %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); } while (0)
#else
#define WSFS_DEBUG_PRINTF(...) do { } while (0)
#endif

typedef struct wsfs_buffer {
	uint8_t *data;
	size_t length;
	size_t capacity;
} wsfs_buffer_t;

typedef struct wsfs_send_frame {
	uint8_t *data;
	size_t length;
	size_t offset;
} wsfs_send_frame_t;

typedef struct wsfs_send_queue {
	wsfs_send_frame_t *frames;
	size_t count;
	size_t capacity;
	size_t queued_bytes;
} wsfs_send_queue_t;

typedef enum wsfs_connection_state {
	WSFS_CONN_HANDSHAKE,
	WSFS_CONN_OPEN,
	WSFS_CONN_CLOSING,
	WSFS_CONN_CLOSED
} wsfs_connection_state_t;

typedef struct wsfs_frame_reader {
	uint8_t header[14];
	size_t header_count;
	size_t header_required;
	uint8_t fin;
	wsfs_opcode_t opcode;
	uint8_t masked;
	uint8_t mask[4];
	uint64_t declared_length;
	uint64_t received_length;
	wsfs_buffer_t payload;
} wsfs_frame_reader_t;

struct wsfs_server_impl;

typedef struct wsfs_connection_impl {
	wsfs_connection_t api;
	wsfs_socket_t fd;
	wsfs_connection_state_t state;
	struct wsfs_server_impl *server;
	size_t slot_index;

	wsfs_buffer_t handshake_buffer;
	wsfs_frame_reader_t frame_reader;
	wsfs_buffer_t message_buffer;
	wsfs_opcode_t message_opcode;
	uint8_t fragmented_in_progress;

	wsfs_send_queue_t send_queue;

	char peer_ip[64];
	uint16_t peer_port;
	void *user_data;
	uint8_t handshake_complete;
	uint8_t close_sent;
	uint8_t close_received;
} wsfs_connection_impl_t;

typedef struct wsfs_slot {
	wsfs_socket_t fd;
	wsfs_connection_impl_t *conn;
	uint8_t wants_write;
} wsfs_slot_t;

typedef struct wsfs_server_impl {
	wsfs_server_config_t config;
	wsfs_socket_t listen_fd;
	volatile sig_atomic_t stop_flag;

	wsfs_slot_t *slots;
	size_t slot_count;

	uint8_t *recv_scratch;
	fd_set read_fds_master;
	fd_set write_fds_master;
	int max_fd;
} wsfs_server_impl_t;

static inline wsfs_server_impl_t *
wsfs_server_get_impl(wsfs_server_t *server)
{
	return server != NULL ? (wsfs_server_impl_t *)server->impl : NULL;
}

static inline void
wsfs_server_set_impl(wsfs_server_t *server, wsfs_server_impl_t *impl)
{
	if (server != NULL)
		server->impl = impl;
}

static inline wsfs_connection_impl_t *
wsfs_connection_get_impl(wsfs_connection_t *conn)
{
	return conn != NULL ? (wsfs_connection_impl_t *)conn->impl : NULL;
}

static inline void
wsfs_connection_set_impl(wsfs_connection_t *conn, wsfs_connection_impl_t *impl)
{
	if (conn != NULL)
		conn->impl = impl;
}

#define WSFS_DEFAULT_HOST "0.0.0.0"
#define WSFS_DEFAULT_PORT 9001
#define WSFS_DEFAULT_MAX_CLIENTS 16
#define WSFS_DEFAULT_RECV_BUFFER_SIZE 4096
#define WSFS_DEFAULT_MAX_FRAME_SIZE (1024 * 1024)
#define WSFS_DEFAULT_HANDSHAKE_BUFFER_CAP (8 * 1024)
#define WSFS_DEFAULT_SEND_QUEUE_CAP (512 * 1024)

wsfs_status_t wsfs_connection_init(wsfs_connection_impl_t *conn,
		   wsfs_server_impl_t *server, wsfs_socket_t fd);
void wsfs_connection_deinit(wsfs_connection_impl_t *conn);
wsfs_status_t wsfs_enqueue_raw(wsfs_connection_impl_t *conn, const uint8_t *data,
		       size_t length);
wsfs_status_t wsfs_connection_flush_pending(wsfs_connection_impl_t *conn,
				  uint16_t *close_code);
void wsfs_update_poll_events(wsfs_server_impl_t *server,
		     wsfs_connection_impl_t *conn);
void wsfs_refresh_fd_sets(wsfs_server_impl_t *server);
wsfs_status_t wsfs_connection_queue_frame(wsfs_connection_impl_t *conn,
					  wsfs_opcode_t opcode, uint8_t fin,
					  const uint8_t *payload,
					  size_t length, int is_control);
wsfs_status_t wsfs_connection_queue_close(wsfs_connection_impl_t *conn,
					  uint16_t close_code);

wsfs_status_t wsfs_connection_send_frame_blocking(wsfs_connection_impl_t *conn,
						   wsfs_opcode_t opcode, uint8_t fin,
						   const uint8_t *payload,
						   size_t length, int is_control);

wsfs_status_t wsfs_frame_reader_init(wsfs_frame_reader_t *reader,
				     size_t initial_capacity);
void wsfs_frame_reader_reset(wsfs_frame_reader_t *reader);
int wsfs_frame_reader_needs_header(wsfs_frame_reader_t *reader);
size_t wsfs_frame_reader_header_bytes(wsfs_frame_reader_t *reader);
uint8_t *wsfs_frame_reader_header_buffer(wsfs_frame_reader_t *reader);
wsfs_status_t wsfs_frame_reader_parse_header(wsfs_frame_reader_t *reader,
					     const wsfs_server_config_t *cfg,
					     uint16_t *close_code);
wsfs_status_t wsfs_frame_reader_consume_payload(wsfs_frame_reader_t *reader,
						const uint8_t *data,
						size_t length,
						const wsfs_server_config_t *cfg,
						size_t *consumed,
						uint16_t *close_code);
int wsfs_frame_is_control(const wsfs_frame_reader_t *reader);
int wsfs_frame_is_fin(const wsfs_frame_reader_t *reader);
uint64_t wsfs_frame_payload_length(const wsfs_frame_reader_t *reader);
wsfs_buffer_t *wsfs_frame_payload_buffer(wsfs_frame_reader_t *reader);

void *wsfs_realloc(void *ptr, size_t new_size, const char *func);
void *wsfs_malloc(size_t size, const char *func);
void wsfs_free(void *ptr, const char *func);

#endif /* WSFS_INTERNAL_H */
