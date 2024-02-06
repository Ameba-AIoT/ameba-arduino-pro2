#include "server_drv.h"
#include "platform_stdlib.h"

#ifdef __cplusplus
extern "C" {
#include "ard_socket.h"
}
#endif

int ServerDrv::startClient(uint32_t ipAddress, uint16_t port, uint8_t protMode, tBlockingMode blockMode)
{
    int sock;
    if (blockMode == BLOCKING_MODE) {
        // printf("\r\n[INFO] %s WiFi client is set to blocking mode \n", __FUNCTION__);
        sock = start_client(ipAddress, port, protMode);
    } else {
        // printf("\r\n[INFO] %s WiFi client is set to non-blocking mode \n", __FUNCTION__);
        sock = start_client(ipAddress, port, protMode);
        set_nonblocking(sock);
    }
    return sock;
}

#if 0
int ServerDrv::startClientV6(const char *ipv6Address, uint16_t port, uint8_t protMode) {
    //printf("\n\r[INFO] %s ipv6 addr: %s\n", __FUNCTION__, ipv6Address);
    int sock;

    sock = start_client_v6((char *)ipv6Address, port, portMode);

    return sock;
}

int ServerDrv::startClientv6(uint32_t *ipv6Address, uint16_t port, uint8_t portMode) {
    int sock;
    sock = start_clientv6(ipv6Address, port, protMode);
    //printf("\n\r[INFO] %s sock value: %x\n", __FUNCTION__, sock);
    return sock;
}
#endif

int ServerDrv::startServer(uint16_t port, uint8_t portMode, tBlockingMode blockMode)
{
    int sock;
    if (blockMode == BLOCKING_MODE) {
        // printf("\r\n[INFO] %s WiFi server is set to blocking mode \n", __FUNCTION__);
        // if (getIPv6Status() == 0) {
        sock = start_server(port, portMode);
        if (sock >= 0) {
            if (portMode == TCP_MODE) {
                // Make it listen to socket with max 20 connections
                sock_listen(sock, 1);
            }
        }
        // } else {
        //     sock = start_server_v6(port, portMode);
        //     if (sock >= 0) {
        //         if (portMode == TCP_MODE) {
        //             //Make it listen to socket with max 20 connections
        //              sock_listen(sock, 20);
        //         }
        //     }
        // }
    } else {
        // printf("\r\n[INFO] %s WiFi server is set to non-blocking mode \n", __FUNCTION__);
        // if (getIPv6Status() == 0) {
        sock = start_server(port, portMode);
        set_nonblocking(sock);
        if (sock >= 0) {
            if (portMode == TCP_MODE) {
                // Make it listen to socket with max 20 connections
                sock_listen(sock, 1);
            }
        }
        // } else {
        //     sock = start_server_v6(port, portMode);
        //     set_nonblocking(sock);
        //     if (sock >= 0) {
        //         if (portMode == TCP_MODE) {
        //             //Make it listen to socket with max 20 connections
        //             sock_listen(sock, 20);
        //         }
        //     }
        // }
    }
    return sock;
}

int ServerDrv::getAvailable(int sock)
{
    // if (getIPv6Status() == 0) {
    return get_available(sock);
    // } else {
    //     return get_available_v6(sock);
    // }
}

int ServerDrv::availData(int sock)
{
    int ret;
    uint8_t c[1460];
    if (sock < 0) {
        return 0;
    }

    if (_available) {
        return 1;
    } else {
        ret = get_receive(sock, c, 1460, 1, &_peer_addr, &_peer_port);
        if (ret == 1) {
            _available = true;
            return 1;
        } else {
            return ret;
        }
    }
}

bool ServerDrv::recvData(int sock, uint8_t *_data, uint32_t _dataLen)
{
    int ret;
    _available = false;

    ret = recv_data(sock, _data, _dataLen, 0);

    return ret;
}

bool ServerDrv::getData(int sock, uint8_t *data, uint8_t peek)
{
    int ret = 0;
    int flag = 0;

    if (peek) {
        flag |= 1;
    } else {
        _available = false;
    }

    ret = get_receive(sock, data, 1, flag, &_peer_addr, &_peer_port);

    if (ret == 1) {
        return true;
    }

    return false;
}

int ServerDrv::getDataBuf(int sock, uint8_t *_data, uint32_t _dataLen)
{
    int ret;
    _available = false;

    // if (getIPv6Status() == 0) {
    ret = get_receive(sock, _data, _dataLen, 0, &_peer_addr, &_peer_port);
    // } else {
    //     ret = get_receive_v6(sock, _data, _dataLen, 0, &_peer_addr, &_peer_port);
    // }

    return ret;
}

int ServerDrv::getLastErrno(int sock)
{
    return get_sock_errno(sock);
}

void ServerDrv::stopSocket(int sock)
{
    close_socket(sock);
    _available = false;
}

bool ServerDrv::sendData(int sock, const uint8_t *data, uint32_t len)
{
    int ret;
    int flag = 0;

    if (sock < 0) {
        return false;
    }

    ret = send_data(sock, data, len, flag);
    if (ret <= 0) {
        return false;
    }
    return true;
}

bool ServerDrv::sendtoData(int sock, const uint8_t *data, uint32_t len, uint32_t peer_ip, uint16_t peer_port)
{
    int ret;

    if (sock < 0) {
        return false;
    }
    // if (getIPv6Status() == 0) {
    ret = sendto_data(sock, data, len, peer_ip, peer_port);
    //    printf("\r\n[INFO] %s ret = %d\n", __FUNCTION__, ret);
    // } else {
    //     ret = sendto_data_v6(sock, data, len, peer_ip, peer_port);
    // }
    if (ret == 0) {
        return false;
    }

    return true;
}

void ServerDrv::getRemoteData(int sock, uint32_t *ip, uint16_t *port)
{
    sock = sock;
    *ip = _peer_addr;
    *port = _peer_port;
}

int ServerDrv::setSockRecvTimeout(int sock, int timeout)
{
    return set_sock_recv_timeout(sock, timeout);
}

#if 0
int ServerDrv::enableIPv6() {
    return enable_ipv6();
}

int ServerDrv::getIPv6Status() {
    return get_ipv6_status();
}

void ServerDrv::setIPv6UDPServer(void) {
    ipv6_udp_server();
}
#endif
