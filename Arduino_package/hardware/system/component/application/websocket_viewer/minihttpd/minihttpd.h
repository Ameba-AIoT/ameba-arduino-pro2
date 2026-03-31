#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct string_s {
	char *start;
	int len;
} string_t;

typedef struct server_t_ server_t;
typedef struct conn_t_ conn_t;
typedef void (*callback_func_t)(conn_t *conn, void *param);

// server
server_t *server_new();
int server_start(server_t *server, int port, int num_worker);
int server_close(server_t *server);
void server_reg_callback(server_t *server, const char *path, callback_func_t func, void *param);
void server_clear_callbacks(server_t *server);

// client information
void client_get_path(conn_t *conn, string_t *s);
void client_get_method(conn_t *conn, string_t *s);
void client_get_proto(conn_t *conn, string_t *s);
int  client_get_header_field(conn_t *conn, const char *name, char **value);
void client_dump_header(conn_t *conn);

// client response handling
void client_response_write_header_start(conn_t *conn, const char *resp, const char *type, int content_len);
void client_response_write_header(conn_t *conn, const char *key, const char *value);
void client_response_write_header_finish(conn_t *conn);
void client_response_write_data(conn_t *conn, void *data, int len);

#ifdef __cplusplus
};
#endif
