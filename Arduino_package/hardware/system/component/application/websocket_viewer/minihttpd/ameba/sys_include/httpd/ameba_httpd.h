#ifndef _AMEBA_HTTPD_H_
#define _AMEBA_HTTPD_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HTTPD_THREAD_SINGLE     0
#define HTTPD_SECURE_NONE       1

struct http_request {
	char *path;
	size_t path_len;
};

struct httpd_conn {
    void *obj;
	struct http_request request;
};

typedef void (*http_cb_t)(struct httpd_conn *conn);

void minihttpd_conn_dump_header(struct httpd_conn *conn);
int minihttpd_request_get_header_field(struct httpd_conn *conn, const char *name, char **value);
void minihttpd_free(void *ptr);
int minihttpd_request_is_method(struct httpd_conn *conn, const char *method);
void minihttpd_conn_close(struct httpd_conn *conn);
void minihttpd_response_method_not_allowed(struct httpd_conn *conn, void *data);
void minihttpd_response_method_header_start(struct httpd_conn *conn, const char *result, const char *mine_type, int len);
void minihttpd_response_write_header_finish(struct httpd_conn *conn);
void minihttpd_response_write_header(struct httpd_conn *conn, const char *name, const char *value);
int minihttpd_start(int port, int a, int b, int thread_mode, int security);
void minihttpd_reg_page_callback(const char *dir, http_cb_t callback);
void minihttpd_clear_page_callbacks(void);
void minihttpd_response_internal_server_error(struct httpd_conn *conn, void *data);
void minihttpd_response_write_data(struct httpd_conn *conn, void *body, size_t body_size);
void minihttpd_response_write_header_start(struct httpd_conn *conn, const char *res, const char *mime_type, size_t len);
size_t minihttpd_request_read_data(struct httpd_conn *conn, void *body, int bodylen);
void minihttpd_response_bad_request(struct httpd_conn *conn, const char *output);
int minihttpd_request_get_query_key(struct httpd_conn *conn, const char *key, char **value);

#ifdef __cplusplus
}
#endif

#endif //
