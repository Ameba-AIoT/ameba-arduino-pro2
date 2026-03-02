#include "Arduino.h"

#include "ard_socket.h"

#include <lwip/netif.h>
#include <lwip/sockets.h>
#include <platform_stdlib.h>
#include <platform_opts.h>
#include <lwip_netconf.h>
#include <wifi_ind.h>

#define MAX_RECV_SIZE   1500
#define MAX_SEND_SIZE   256
#define UDP_SERVER_PORT 5002
#define TCP_SERVER_PORT 5003

#if defined(LWIP_IPV6) && (LWIP_IPV6 == 1)
extern struct netif xnetif[];
#endif

static int EXAMPLE_IPV6 = 0;

int start_client(uint32_t ipAddress, uint16_t port, uint8_t protMode)
{
    int enable = 1;
    int timeout;
    int _sock;

    // create socket
    if (protMode == TCP_MODE) {
        _sock = lwip_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    } else {
        _sock = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    if (_sock < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Create socket failed\n", __FUNCTION__);
        return -1;
    }
    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Create socket successfully\n");

    // initialize structure dest
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = ipAddress;
    serv_addr.sin_port = htons(port);

    // Connecting to server
    if (protMode == TCP_MODE) {
        // TCP MODE
        if (connect(_sock, ((struct sockaddr *)&serv_addr), sizeof(serv_addr)) == 0) {
            amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Connect to Server successfully!\n");
            timeout = 3000;
            lwip_setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
            timeout = 30000;
            lwip_setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
            lwip_setsockopt(_sock, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable));
            lwip_setsockopt(_sock, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
            return _sock;
        } else {
            amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Connect to server failed\n", __FUNCTION__);
            close_socket(_sock);
            return -1;
        }
    } else {
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Udp client setup Server's information successful!\n");
    }
    return _sock;
}

int start_clientv6(uint32_t *ipv6Address, uint16_t port, uint8_t protMode)
{
    int enable = 1;
    int timeout;
    int _sock;

    // create socket
    if (protMode == TCP_MODE) {
        _sock = lwip_socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    } else {
        _sock = lwip_socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    }
    if (_sock < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Create socket failed\n", __FUNCTION__);
        return -1;
    }
    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Create socket successfully\n");

    // initialize structure dest
    struct sockaddr_in6 serv_addr6;
    memset(&serv_addr6, 0, sizeof(serv_addr6));
    serv_addr6.sin6_family = AF_INET6;
    serv_addr6.sin6_port = htons(port);
    // inet_pton(AF_INET6, TCP_SERVER_IP_TEST, &(serv_addr6.sin6_addr));
    for (int xxx = 0; xxx < 4; xxx++) {    // IPv6 address
        serv_addr6.sin6_addr.un.u32_addr[xxx] = ipv6Address[xxx];
    }

    // connection starts
    if (protMode == TCP_MODE) {
        if (connect(_sock, (struct sockaddr *)(&serv_addr6), sizeof(serv_addr6)) == -1) {
            amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Connect to server failed\n", __FUNCTION__);
        }
        amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Connect to server successfully\n");

        if (connect(_sock, (struct sockaddr *)(&serv_addr6), sizeof(serv_addr6)) == 0) {
            // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Connect to Server successfully!\r\n");
            timeout = 3000;
            lwip_setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
            timeout = 30000;
            lwip_setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
            lwip_setsockopt(_sock, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable));
            lwip_setsockopt(_sock, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
            return _sock;
        } else {
            amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Connect to Server failed!\r\n", __FUNCTION__);
            close_socket(_sock);
            return -1;
        }
    } else {
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Udp client setup Server's information successful!\r\n");
    }

    return _sock;
}

int start_client_v6(char ipv6Address[], uint16_t port, uint8_t protMode)
{
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] ard_socket.cpp  start_client_v6\n");
    // int enable = 1;
    // int timeout;
    // int _sock;
    int client_fd;
    struct sockaddr_in6 ser_addr;

#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
    struct sockaddr_in6 src_addr6;
    ip6_addr_t dest_addr6;
#endif

    // create socket
    if (protMode == TCP_MODE) {
        if ((client_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            amb_ard_printf(ARD_LOG_ERR, "\n\r[ERROR] Create socket failed\n");
            return -1;
        }
        // amb_ard_printf(ARD_LOG_INF, "\n\r[INFO] Create socket successfully\n");
    } else {
        if ((client_fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
            amb_ard_printf(ARD_LOG_ERR, "\n\r[ERROR] Create socket failed\n");
            return -1;
        }
        // amb_ard_printf(ARD_LOG_INF, "\n\r[INFO] Create socket successfully\n");
    }

    // initialize value in dest
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin6_family = AF_INET6;
    if (protMode == TCP_MODE) {
        ser_addr.sin6_port = htons(TCP_SERVER_PORT);
    } else {
        ser_addr.sin6_port = htons(UDP_SERVER_PORT);
    }
    inet_pton(AF_INET6, ipv6Address, &(ser_addr.sin6_addr));

#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
    inet6_addr_to_ip6addr(&dest_addr6, &(ser_addr.sin6_addr));

    if (ip6_addr_ismulticast_linklocal(&dest_addr6) || ip6_addr_ismulticast_iflocal(&dest_addr6)
        || ip6_addr_islinklocal(&dest_addr6)) {
        memset(&src_addr6, 0, sizeof(src_addr6));
        src_addr6.sin6_family = AF_INET6;
        if (protMode == TCP_MODE) {
            src_addr6.sin6_port = htons(TCP_SERVER_PORT);
        } else {
            src_addr6.sin6_port = htons(UDP_SERVER_PORT);
        }
        inet6_addr_from_ip6addr(&src_addr6.sin6_addr, (ip6_addr_t *)&xnetif[0].ip6_addr[0]);

        if (bind(client_fd, (struct sockaddr *)&src_addr6, sizeof(src_addr6)) != 0) {
            amb_ard_printf(ARD_LOG_ERR, "\n\r[ERROR] Bind socket failed\n");
            closesocket(client_fd);
            return -1;
        }
    }
#endif
    if (protMode == TCP_MODE) {
        // Connecting to server
        if (connect(client_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) == -1) {
            amb_ard_printf(ARD_LOG_ERR, "\n\r[ERROR] Connect to server failed\n");
        } else {
            amb_ard_printf(ARD_LOG_INF, "\n\r[INFO] Connect to server successfully\n");
        }
    }
    return client_fd;
}

int set_nonblocking(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}

int start_server(uint16_t port, uint8_t protMode)
{
    int _sock;
    int timeout;

    // create socket
    if (protMode == TCP_MODE) {
        timeout = 3000;
        _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Create TCP socket successfully\n");
    } else {
        timeout = 1000;
        _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Create UDP socket successfully\n");
    }

    if (_sock < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Opening socket\n", __FUNCTION__);
        return -1;
    }

    // initialize structure dest
    struct sockaddr_in localHost;
    memset(&localHost, 0, sizeof(localHost));

    localHost.sin_family = AF_INET;
    localHost.sin_port = htons(port);
    localHost.sin_addr.s_addr = INADDR_ANY;

    // Assign a port number to socket
    if (bind(_sock, ((struct sockaddr *)&localHost), sizeof(localHost)) < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s On binding\n", __FUNCTION__);
        return -1;
    }
    // lwip_fcntl(_sock, F_SETFL, O_NONBLOCK);
    return _sock;
}

int start_server_v6(uint16_t port, uint8_t protMode)
{
    int _sock;
    int timeout;

    // create socket
    if (protMode == TCP_MODE) {    // TCP
        timeout = 3000;
        _sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Create TCP socket successfully\n");
    } else {    // UDP
        // timeout = 1000;
        _sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
        // setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Create UDP socket successfully\n");
    }

    if (_sock < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Create socket failed\n", __FUNCTION__);
        return -1;
    }

    // initialize structure dest
    struct sockaddr_in6 localHost;
    memset(&localHost, 0, sizeof(localHost));
    localHost.sin6_family = AF_INET6;
    localHost.sin6_port = htons(port);
    localHost.sin6_addr = (struct in6_addr)IN6ADDR_ANY_INIT;

    // Assign a port number to socket
    if (bind(_sock, (struct sockaddr *)&localHost, sizeof(localHost)) < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Bind socket failed\n", __FUNCTION__);
        closesocket(_sock);
        return -1;
    }
    // lwip_fcntl(_sock, F_SETFL, O_NONBLOCK);
    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Bind socket successfully\n");
    return _sock;
}

int get_sock_errno(int sock)
{
    // https://www.nongnu.org/lwip/2_1_x/upgrading.html
    // socket API: according to the standard, SO_ERROR now only returns asynchronous errors.
    // All other/normal/synchronous errors are (and always were) available via 'errno'.

    //    int so_error;
    //    socklen_t len = sizeof(so_error);
    //    lwip_getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
    //    return so_error;

    if (fcntl(sock, F_GETFL, 0) & O_NONBLOCK) {
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] %s Non blocking\r\n", __FUNCTION__);
        return 0;
    }

    return errno;
}

int set_sock_recv_timeout(int sock, int timeout)
{
    return lwip_setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
}

void close_socket(int sock)
{
    lwip_close(sock);
}

int enable_ipv6(void)
{
    EXAMPLE_IPV6 = 1;

    return EXAMPLE_IPV6;
}

int get_ipv6_status(void)
{
    // return current ipv6 enabled status
    return EXAMPLE_IPV6;
}

// TCP
int sock_listen(int sock, int max)
{
    if (listen(sock, max) < 0) {
        // amb_ard_printf(ARD_LOG_ERR, "\r\n ERROR on listening\r\n");
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Listen socket failed, socket closed\n", __FUNCTION__);
        close_socket(sock);
        return -1;
    }
    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Listen socket successfully\n");
    return 0;
}

int get_available(int sock)
{
    int enable = 1;
    int timeout;
    int client_fd;
    int err;
    struct sockaddr_in cli_addr;

    socklen_t client = sizeof(cli_addr);

    do {
        client_fd = lwip_accept(sock, ((struct sockaddr *)&cli_addr), &client);
        if (client_fd < 0) {
            err = get_sock_errno(sock);
            if (err != EAGAIN) {
                break;
            }
        }
    } while (client_fd < 0);

    if (client_fd < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Accept connection failed\n", __FUNCTION__);
        return -1;
    } else {
        timeout = 3000;
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        timeout = 30000;
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));

        lwip_setsockopt(client_fd, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable));
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] MEM_SIZE %d \n", MEM_SIZE);
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] PBUF_POOL_SIZE %d \n", PBUF_POOL_SIZE);
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] TCP_SND_BUF %d \n", TCP_SND_BUF);

        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Accept connection successfully\n");
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] A client connected to this server :\r\n[PORT]: %d\r\n[IP]: %s\r\n\r\n", ntohs(cli_addr.sin_port), inet_ntoa(cli_addr.sin_addr.s_addr));
        amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] A client connected to this server \n\t [PORT]: %d \n\t [IP]: %s \n", ntohs(cli_addr.sin_port), inet_ntoa(cli_addr.sin_addr.s_addr));
        return client_fd;
    }
}

int get_available_v6(int sock)
{
    int enable = 1;
    int timeout;
    int client_fd;
    int err;
    struct sockaddr_in6 cli_addr;

    socklen_t client = sizeof(struct sockaddr_in6);

    do {
        client_fd = lwip_accept(sock, ((struct sockaddr *)&cli_addr), &client);
        if (client_fd < 0) {
            err = get_sock_errno(sock);
            if (err != EAGAIN) {
                break;
            }
        }
    } while (client_fd < 0);

    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Get_available_v6 client_fd: %d\r\n", client_fd);

    if (client_fd < 0) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Accept connection failed\n", __FUNCTION__);
        return -1;
    } else {
        timeout = 3000;
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        timeout = 30000;
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
        lwip_setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Accept connection successfully\n");
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] A client connected to this server :\r\n[PORT]: %d\r\n[IPv6]:%s\r\n\r \n", ntohl(cli_addr.sin6_port), inet6_ntoa(cli_addr.sin6_addr.un.u32_addr[4]));
        return client_fd;
    }
}

int recv_data(int sock, const uint8_t *data, uint32_t len, int flag)
{
    int ret;

    ret = lwip_recv(sock, (void *)data, len, flag);

    return ret;
}

int send_data(int sock, const uint8_t *data, uint32_t len, int flag)
{
#if 1
    int ret;
    ret = lwip_send(sock, data, len, flag);
    return ret;
#else

// 1 TCP segment (1460 MSS size)
#define CHUNK_SIZE 512
    size_t offset = 0;
    ssize_t sent = 0;
    ssize_t total_sent = 0;
    size_t remaining, to_send;

    while (offset < len) {
        remaining = len - offset;
        to_send = remaining > CHUNK_SIZE ? CHUNK_SIZE : remaining;

        sent = lwip_send(sock, data + offset, to_send, 0);

        if (sent > 0) {
            offset += sent;
            total_sent += sent;
            sys_msleep(1);

        } else if (sent < 0 && (errno == EWOULDBLOCK || errno == EAGAIN)) {
            // socket not ready, wait for writable
            fd_set wfds;
            FD_ZERO(&wfds);
            FD_SET(sock, &wfds);

            // 20ms wait
            struct timeval tv = {0, 20000};
            int ret = lwip_select(sock + 1, NULL, &wfds, NULL, &tv);
            if (ret <= 0) {
                // timeout or error, retry
                continue;
            }
        } else {
            // real error
            return -1;
        }
    }
    // success
    return total_sent;
#endif
}

// UDP
int sendto_data(int sock, const uint8_t *data, uint32_t len, uint32_t peer_ip, uint16_t peer_port)
{
    int ret;
    struct sockaddr_in peer_addr;

    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = peer_ip;
    peer_addr.sin_port = htons(peer_port);

    ret = lwip_sendto(sock, data, len, 0, ((struct sockaddr *)&peer_addr), sizeof(struct sockaddr_in));

    return ret;
}

int sendto_data_v6(int sock, const void *send_data, size_t len, uint32_t peer_ip, uint16_t peer_port)
{
    int ret = 0;
    struct sockaddr_in6 peer_addr;

    peer_ip = peer_ip;
    peer_port = peer_port;

    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin6_family = AF_INET6;
    peer_addr.sin6_port = htons(UDP_SERVER_PORT);
    inet_pton(AF_INET6, (char *)peer_ip, &(peer_addr.sin6_addr));

    ret = lwip_sendto(sock, send_data, len, 0, ((struct sockaddr *)&peer_addr), sizeof(peer_addr));

    return ret;
}

int get_receive(int sock, uint8_t *data, int length, int flag, uint32_t *peer_addr, uint16_t *peer_port)
{
    int ret = 0;
    struct sockaddr from;
    socklen_t fromlen;

    uint8_t backup_recvtimeout = 0;
    int backup_recv_timeout, recv_timeout;
    socklen_t len;

    if (flag & 0x01) {
        // for MSG_PEEK, we try to peek packets by changing receiving timeout to 10ms
        ret = lwip_getsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &backup_recv_timeout, &len);
        if (ret >= 0) {
            recv_timeout = 10;
            ret = lwip_setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));
            if (ret >= 0) {
                backup_recvtimeout = 1;
            }
        }
    }
    ret = lwip_recvfrom(sock, data, length, flag, &from, &fromlen);

    if (ret >= 0) {
        if (peer_addr != NULL) {
            *peer_addr = ((struct sockaddr_in *)&from)->sin_addr.s_addr;
        }
        if (peer_port != NULL) {
            *peer_port = ntohs(((struct sockaddr_in *)&from)->sin_port);
        }
    }

    if ((flag & 0x01) && (backup_recvtimeout == 1)) {
        // restore receiving timeout
        lwip_setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &backup_recv_timeout, sizeof(recv_timeout));
    }

    return ret;
}

int get_receive_v6(int sock, void *recv_data, int len, int flags, uint32_t *peer_ip, uint16_t *peer_port)
{
    int ret = 0;
    struct sockaddr_in6 peer_addr;
    unsigned int peer_len = sizeof(struct sockaddr_in6);

    peer_ip = peer_ip;
    peer_port = peer_port;

    ret = lwip_recvfrom(sock, recv_data, len, flags, ((struct sockaddr *)&peer_addr), &peer_len);
    return ret;
}

void ipv6_udp_server(char *data_recv, const char *data_send)
{
    int server_fd;
    struct sockaddr_in6 client_addr;

    unsigned int addrlen = sizeof(struct sockaddr_in6);

    // char send_data[MAX_SEND_SIZE] = "Hi client!";
    // char recv_data[MAX_RECV_SIZE];

    // create socket
    server_fd = start_server_v6(UDP_SERVER_PORT, 1);

    while (1) {
        memset(data_recv, 0, MAX_RECV_SIZE);
        // if (get_receive_v6(server_fd, recv_data, MAX_SEND_SIZE, 0, UDP_SERVER_IP, UDP_SERVER_PORT) <= 0) {
        if (lwip_recvfrom(server_fd, data_recv, MAX_RECV_SIZE, 0, (struct sockaddr *)&client_addr, &addrlen) > 0) {
            amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Receive data : %s\n", data_recv);
            // Send Response
            if (lwip_sendto(server_fd, data_send, MAX_SEND_SIZE, 0, (struct sockaddr *)&client_addr, addrlen) == -1) {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] %s Send data failed\n", __FUNCTION__);
            } else {
                amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Send data successfully\n");
            }
        }
    }

    closesocket(server_fd);
    return;
}
