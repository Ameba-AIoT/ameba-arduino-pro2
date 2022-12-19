/*
 * Copyright (c) 2022 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_HTTP_TLS_H
#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_HTTP_TLS_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace ameba::media
{

typedef unsigned char uint8_t;

void http_tls_free(void *tls_in);
void http_tls_close(void *tls_in);
int http_tls_handshake(void *tls_in, char *host);
void *http_tls_new(int *sock, char *client_cert, char *client_key, char *ca_certs);
int http_tls_read(void *tls_in, uint8_t *buf, size_t buf_len);
int http_tls_write(void *tls_in, uint8_t *buf, size_t buf_len);

}  // namespace ameba::media

#ifdef __cplusplus
}
#endif

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_HTTP_TLS_H