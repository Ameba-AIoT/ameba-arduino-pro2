#include "ard_ssl.h"
#include <sockets.h> 
#include <lwip/netif.h>
#include <mbedtls/ssl.h>
#include <mbedtls/net_sockets.h>
#include <mbedtls/error.h>
#include <mbedtls/debug.h>
#include <mbedtls/platform.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <FreeRTOS.h>

#define ARDUINO_MBEDTLS_DEBUG_LEVEL     0   // Set to 0 to disable debug messsages, 5 to enable all debug messages
#define MBEDTLS_EXPORT_KEY              0


static mbedtls_ctr_drbg_context* drbg_ctx = NULL;
static mbedtls_entropy_context* ent_ctx = NULL;

static int my_verify(void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags) 
{
    char buf[1024];
    ((void)data);

    mbedtls_x509_crt_info(buf, (sizeof(buf) - 1), "", crt);

    if(ARDUINO_MBEDTLS_DEBUG_LEVEL < 3)
        return(0);

    printf( "\nVerify requested for (Depth %d):\n", depth );
    printf( "%s", buf );

    if ((*flags) == 0)
        printf(" This certificate has no flags\n");
    else
    {
        mbedtls_x509_crt_verify_info(buf, sizeof( buf ), " ! ", *flags);
        printf("%s\n", buf);
    }

    return(0);
}

static void* my_calloc(size_t nelements, size_t elementSize)
{
    size_t size;
    void *ptr = NULL;

    size = nelements * elementSize;
    ptr = pvPortMalloc(size);
//  ptr = malloc(size);

    if(ptr)
        memset(ptr, 0, size);

    return ptr;
}

static void my_debug(void *ctx, int level, const char *file, int line, const char *str )
{
    const char *p, *basename;

    ctx = ctx;     // Remove unused parameter warning
    // Extract basename from file
    for( p = basename = file; *p != '\0'; p++ )
        if( *p == '/' || *p == '\\' )
            basename = p + 1;

    printf("%s:%04d: |%d| %s", basename, line, level, str );

    if (MBEDTLS_EXPORT_KEY) {
        // Code to format and output TLS 1.2 secrets necessary for Wireshark decoding
        static uint8_t in_client_random = 0;
        static uint8_t in_master_secret = 0;
        static uint8_t hexdump_lines_to_process = 0;
        static uint8_t key_done = 0;
        static char out_string[200] = {0};
        if ((level == 3)&&(!key_done)) {
            if (strstr(str, "dumping 'client hello, random bytes'")) {
                in_client_random = 1;
                hexdump_lines_to_process = 2;
                strcpy(out_string, "CLIENT_RANDOM ");
                return;
            } else if (strstr(str, "dumping 'master secret'")) {
                in_master_secret = 1;
                hexdump_lines_to_process = 3;
                strcat(out_string, " ");
                return;
            } else if ((!in_client_random && !in_master_secret) || hexdump_lines_to_process == 0) {
                return;
            }

            // Parse "0000:  64 df 18 71 ca 4a 4b e4 63 87 2a ef 5f 29 ca ff  ..."
            str = strstr(str, ":  ");
            if (!str || strlen(str) < 3 + 3*16) {
                goto reset;         // not the expected hex buffer
            }
            str += 3;               // skip over ":  "

            // Process sequences of "hh "
            for (int i = 0; i < 3 * 16; i += 3) {
                char c1 = str[i], c2 = str[i + 1], c3 = str[i + 2];
                if ((('0' <= c1 && c1 <= '9') || ('a' <= c1 && c1 <= 'f')) &&
                    (('0' <= c2 && c2 <= '9') || ('a' <= c2 && c2 <= 'f')) &&
                    c3 == ' ') {
                    char str1[2] = {c1,0};
                    char str2[2] = {c2,0};
                    strcat(out_string, str1);
                    strcat(out_string, str2);
                } else {
                    goto reset;     // unexpected non-hex char
                }
            }

            if (--hexdump_lines_to_process != 0 || !in_master_secret) {
                return;             // line is not yet finished
            }

    reset:
            hexdump_lines_to_process = 0;
            in_client_random = in_master_secret = 0;
            key_done = 1;
            strcat(out_string, "\n");   // finish key log line
            printf("============== Wireshark TLS decryption key ==============\n");
            printf("%s", out_string);
            printf("==========================================================\n");
        }
    }
}

//Adding definition here as complier was not able to find this function
extern int mbedtls_ssl_conf_psk(mbedtls_ssl_config *conf,
                        const unsigned char *psk, size_t psk_len,
                        const unsigned char *psk_identity, size_t psk_identity_len);

int start_ssl_client(sslclient_context *ssl_client, uint32_t ipAddress, uint32_t port, unsigned char* rootCABuff, unsigned char* cli_cert, unsigned char* cli_key, unsigned char* pskIdent, unsigned char* psKey, char* SNI_hostname)
{
    int ret = 0;
    int timeout;
    int enable = 1;
    int keep_idle = 30;
    mbedtls_x509_crt* cacert = NULL;
    mbedtls_x509_crt* _cli_crt = NULL;
    mbedtls_pk_context* _clikey_rsa = NULL;

    do {
        ssl_client->socket = -1;
        ssl_client->socket = lwip_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (ssl_client->socket < 0) {
            printf("ERROR: opening socket failed! \r\n");
            ret = -1;
            break;
        }

        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = ipAddress;
        serv_addr.sin_port = htons(port);

        mbedtls_platform_set_calloc_free(my_calloc,vPortFree);

        if (lwip_connect(ssl_client->socket, ((struct sockaddr *)&serv_addr), sizeof(serv_addr)) < 0) {
            lwip_close(ssl_client->socket);
            printf("ERROR: Connect to Server failed! \r\n");
            ret = -1;
            break;
        } else {
        /*
        if (lwip_connect(ssl_client->socket, ((struct sockaddr *)&serv_addr), sizeof(serv_addr)) == 0) {
            timeout = ssl_client->recvTimeout;
            lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
            timeout = 30000;
            lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
            lwip_setsockopt(ssl_client->socket, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable));
            lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
        } else {
            printf("ERROR: Connect to Server failed!\r\n");
            ret = -1;
            break;
        }
        */
            timeout = ssl_client->recvTimeout;
            lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
            lwip_setsockopt(ssl_client->socket, IPPROTO_TCP, TCP_KEEPIDLE, &keep_idle, sizeof(keep_idle));

            ssl_client->ssl = (mbedtls_ssl_context *)malloc(sizeof(mbedtls_ssl_context));
            ssl_client->conf = (mbedtls_ssl_config *)malloc(sizeof(mbedtls_ssl_config));
            
            if (drbg_ctx == NULL) {
                drbg_ctx = (mbedtls_ctr_drbg_context *)malloc(sizeof(mbedtls_ctr_drbg_context));
            }
            ssl_client->ctr_drbg = drbg_ctx;

            if(ent_ctx == NULL) {
                 ent_ctx = (mbedtls_entropy_context *)malloc(sizeof(mbedtls_entropy_context));
            }
            ssl_client->entropy = ent_ctx;

            if (( ssl_client->ssl == NULL )||( ssl_client->conf == NULL )||(ssl_client->ctr_drbg == NULL) || (ssl_client->entropy == NULL)) {
                printf("ERROR: malloc ssl failed! \r\n");
                ret = -1;
                break;
            }
            mbedtls_ssl_init(ssl_client->ssl);
            mbedtls_ssl_config_init(ssl_client->conf);
            mbedtls_ctr_drbg_init(ssl_client->ctr_drbg);
            mbedtls_entropy_init(ssl_client->entropy);

            if (ARDUINO_MBEDTLS_DEBUG_LEVEL > 0) {
                mbedtls_ssl_conf_verify(ssl_client->conf, my_verify, NULL);
                mbedtls_ssl_conf_dbg(ssl_client->conf, my_debug, NULL);
                mbedtls_debug_set_threshold(ARDUINO_MBEDTLS_DEBUG_LEVEL);
            }

            mbedtls_ssl_conf_read_timeout(ssl_client->conf, timeout);
            mbedtls_ssl_set_bio(ssl_client->ssl, &ssl_client->socket, mbedtls_net_send, NULL, mbedtls_net_recv_timeout);

            if((mbedtls_ssl_config_defaults(ssl_client->conf, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
                printf("ERROR: mbedtls ssl config defaults failed! \r\n");
                ret = -1;
                break;
            }

            if (rootCABuff != NULL) {
                // Configure mbedTLS to use certificate authentication method
                cacert = (mbedtls_x509_crt *) mbedtls_calloc( sizeof(mbedtls_x509_crt), 1);
                mbedtls_x509_crt_init(cacert);
                if (mbedtls_x509_crt_parse(cacert, rootCABuff, (strlen((char*)rootCABuff)) + 1) != 0) {
                    printf("ERROR: mbedtls x509 crt parse failed! \r\n");
                    ret = -1;
                    break;
                }
                mbedtls_ssl_conf_ca_chain(ssl_client->conf, cacert, NULL);
                mbedtls_ssl_conf_authmode(ssl_client->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
            } else if (pskIdent != NULL && psKey != NULL) {
                // Configure mbedTLS to use PSK authentication method
                // Check for max length and even number of chars
                uint16_t pskey_char_len = strlen((char*)psKey);
                if ( ((pskey_char_len % 2) != 0) || (pskey_char_len > 2*MBEDTLS_PSK_MAX_LEN) ) {
                    printf("ERROR: TLS PSK not in valid hex format or too long \n");
                    return -1;
                }
                uint16_t psk_len = pskey_char_len/2;
                unsigned char psk[MBEDTLS_PSK_MAX_LEN];
                // Convert PSK from hexadecimal chars to binary
                for (int i = 0; i < pskey_char_len; i = i + 2) {
                    char c = psKey[i];
                    // Convert first 4 bits
                    if (c >= '0' && c <= '9') {
                        c = c - '0';
                    } else if (c >= 'A' && c <= 'F') {
                        c = c - 'A' + 10;
                    } else if (c >= 'a' && c <= 'f') {
                        c = c - 'a' + 10;
                    } else {
                        printf("ERROR: TLS PSK not in valid hex format \n");
                        return -1;
                    }
                    psk[i/2] = c << 4;
                    c = psKey[i+1];
                    // Convert next 4 bits
                    if (c >= '0' && c <= '9') {
                        c = c - '0';
                    } else if (c >= 'A' && c <= 'F') {
                        c = c - 'A' + 10;
                    } else if (c >= 'a' && c <= 'f') {
                        c = c - 'a' + 10;
                    } else {
                        printf("ERROR: TLS PSK not in valid hex format \r\n");
                        return -1;
                    }
                    psk[i/2] |= c;
                }
                if (mbedtls_ssl_conf_psk(ssl_client->conf, psk, psk_len, pskIdent, strlen((char*)pskIdent)) != 0) {
                    printf("ERROR: mbedtls conf psk failed! \r\n");
                }
            } else {
                mbedtls_ssl_conf_authmode(ssl_client->conf, MBEDTLS_SSL_VERIFY_NONE);
            }

            if( ( ret = mbedtls_ctr_drbg_seed( ssl_client->ctr_drbg, mbedtls_entropy_func, ssl_client->entropy, NULL, 0 ) ) != 0 ) {
                printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
                ret = -1;
                break;
            }

            mbedtls_ssl_conf_rng(ssl_client->conf, mbedtls_ctr_drbg_random, ssl_client->ctr_drbg);

            if ((cli_cert != NULL) && (cli_key != NULL)) {
                _cli_crt = (mbedtls_x509_crt *) mbedtls_calloc( sizeof(mbedtls_x509_crt), 1);
                if (_cli_crt == NULL) {
                    printf("ERROR: malloc client_crt failed! \r\n");
                    ret = -1;
                    break;
                }
                mbedtls_x509_crt_init(_cli_crt);

                _clikey_rsa = (mbedtls_pk_context *) mbedtls_calloc( sizeof(mbedtls_pk_context), 1);
                if (_clikey_rsa == NULL) {
                    printf("ERROR: malloc client_rsa failed! \r\n");
                    ret = -1;
                    break;
                }
                mbedtls_pk_init(_clikey_rsa);

                if (mbedtls_x509_crt_parse(_cli_crt, cli_cert, strlen((char*)cli_cert)+1) != 0) {
                    printf("ERROR: mbedtls x509 parse client_crt failed! \r\n");
                    ret = -1;
                    break;
                }

                // for mbedtls 3.0.0
                //if (mbedtls_pk_parse_key(_clikey_rsa, cli_key, strlen((char*)cli_key)+1, NULL, 0, mbedtls_ctr_drbg_random, ssl_client->ctr_drbg ) != 0) {
                // for mbedtls 2.28.1
                if (mbedtls_pk_parse_key(_clikey_rsa, cli_key, (strlen((char*)cli_key) + 1), NULL, 0) != 0) {
                    printf("ERROR: mbedtls x509 parse client_rsa failed! \r\n");
                    ret = -1;
                    break;
                }
                mbedtls_ssl_conf_own_cert(ssl_client->conf, _cli_crt, _clikey_rsa);
            }

            if((mbedtls_ssl_setup(ssl_client->ssl, ssl_client->conf)) != 0) {
                printf("ERROR: mbedtls ssl setup failed!\r\n");
                ret = -1;
                break;
            }

            if (mbedtls_ssl_set_hostname(ssl_client->ssl, SNI_hostname) != 0) {
                printf("ERROR: mbedtls ssl set hostname failed.");
            }

            ret = mbedtls_ssl_handshake(ssl_client->ssl);
            if (ret < 0) {
                printf("ERROR: mbedtls ssl handshake failed: -0x%04X \r\n", -ret);
                ret = -1;
            } else { 
                if (ARDUINO_MBEDTLS_DEBUG_LEVEL > 0) {
                    printf("mbedTLS SSL handshake success \r\n");
                }
            }
        }
    } while (0);

    if (_clikey_rsa) {
        mbedtls_pk_free(_clikey_rsa);
        mbedtls_free(_clikey_rsa);
        _clikey_rsa = NULL;
    }

    if (_cli_crt) {
        mbedtls_x509_crt_free(_cli_crt);
        mbedtls_free(_cli_crt);
        _cli_crt = NULL;
    }

    if (cacert) {
        mbedtls_x509_crt_free(cacert);
        mbedtls_free(cacert);
        cacert = NULL;
    }

    if (ret < 0) {
        if (ssl_client->socket >= 0) {
            mbedtls_net_free((mbedtls_net_context *)&ssl_client->socket);
            ssl_client->socket = -1;
        }

        if (ssl_client->ssl != NULL) {
            mbedtls_ssl_free(ssl_client->ssl);
            free(ssl_client->ssl);
            ssl_client->ssl = NULL;
        }
        if (ssl_client->conf != NULL) {
            mbedtls_ssl_config_free(ssl_client->conf);
            free(ssl_client->conf);
            ssl_client->conf = NULL;
        }
    }
    return ssl_client->socket;
}

void stop_ssl_socket(sslclient_context *ssl_client)
{
    lwip_shutdown(ssl_client->socket, SHUT_RDWR);
    lwip_close(ssl_client->socket);
    ssl_client->socket = -1;

    if (ssl_client->ssl != NULL) {
        mbedtls_ssl_free(ssl_client->ssl);
        free(ssl_client->ssl);
        ssl_client->ssl = NULL;
    }
    if (ssl_client->conf != NULL) {
        mbedtls_ssl_config_free(ssl_client->conf);
        free(ssl_client->conf);
        ssl_client->conf = NULL;
    }
}

int send_ssl_data(sslclient_context *ssl_client, const uint8_t *data, uint16_t len)
{
    int ret = -1;

    if (ssl_client->ssl != NULL) {
        ret = mbedtls_ssl_write(ssl_client->ssl, data, len);
    }

    return ret;
}

int get_ssl_receive(sslclient_context *ssl_client, uint8_t* data, int length, int flag)
{
    int ret = 0;
    int recv_timeout;

    if (ssl_client->ssl == NULL) {
        return 0;
    }

    if (flag & 0x01) {
        recv_timeout = 100;
        mbedtls_ssl_conf_read_timeout(ssl_client->conf, recv_timeout);
    }

    memset(data, 0, length);
    ret = mbedtls_ssl_read(ssl_client->ssl, data, length);

    if (ret <= 0) {
        switch(ret) {
            case MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY:
                mbedtls_ssl_close_notify(ssl_client->ssl);
                break;
            case MBEDTLS_ERR_SSL_WANT_READ:
                break;
            case MBEDTLS_ERR_SSL_WANT_WRITE:
                break;
            case MBEDTLS_ERR_SSL_TIMEOUT:
                break;
            default:
                //printf("mbedtls_ssl_read returned: -0x%04X \r\n", -ret);
                stop_ssl_socket(ssl_client);
                break;
        }
    }

    if ((flag & 0x01)) {
        recv_timeout = ssl_client->recvTimeout;
        mbedtls_ssl_conf_read_timeout(ssl_client->conf, recv_timeout);
    }

    return ret;
}

int get_ssl_sock_errno(sslclient_context *ssl_client) {
// https://www.nongnu.org/lwip/2_1_x/upgrading.html
// socket API: according to the standard, SO_ERROR now only returns asynchronous errors.
// All other/normal/synchronous errors are (and always were) available via 'errno'.
//    int so_error;
//    socklen_t len = sizeof(so_error);
//    lwip_getsockopt(ssl_client->socket, SOL_SOCKET, SO_ERROR, &so_error, &len);
//    return so_error;
    (void) ssl_client->socket;
    return errno;
}

int get_ssl_bytes_avail(sslclient_context *ssl_client) {
    if (ssl_client->ssl != NULL) {
        return mbedtls_ssl_get_bytes_avail(ssl_client->ssl);
    } else {
        return 0;
    }
}
