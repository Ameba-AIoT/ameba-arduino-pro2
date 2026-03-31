/*
 * Copyright (c) 2025 Realtek Semiconductor Corp.
 * All rights reserved.
 */

#ifndef WSFS_SOCKET_H
#define WSFS_SOCKET_H

#include <errno.h>

#define WSFS_PLATFORM_LWIP

#if defined(WSFS_PLATFORM_LWIP)

#include <lwip/opt.h>
#include <lwip/sockets.h>
#include <lwip/inet.h>
#include <lwip/netdb.h>
#include <lwip/errno.h>
#include <lwip_netconf.h>

typedef int wsfs_socket_t;
typedef socklen_t wsfs_socklen_t;

#define WSFS_INVALID_SOCKET (-1)
#define WSFS_SOCKET_ERROR (-1)

static inline int wsfs_socket_close(wsfs_socket_t s)
{
	return lwip_close(s);
}

static inline int wsfs_socket_select(int nfds, fd_set *readfds,
				     fd_set *writefds, fd_set *exceptfds,
				     struct timeval *timeout)
{
	return lwip_select(nfds, readfds, writefds, exceptfds, timeout);
}

static inline int wsfs_socket_errno(void)
{
	return errno;
}

#else /* WSFS_PLATFORM_LWIP */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef int wsfs_socket_t;
typedef socklen_t wsfs_socklen_t;

#define WSFS_INVALID_SOCKET (-1)
#define WSFS_SOCKET_ERROR (-1)

static inline int wsfs_socket_close(wsfs_socket_t s)
{
	return close(s);
}

static inline int wsfs_socket_select(int nfds, fd_set *readfds,
				     fd_set *writefds, fd_set *exceptfds,
				     struct timeval *timeout)
{
	return select(nfds, readfds, writefds, exceptfds, timeout);
}

static inline int wsfs_socket_errno(void)
{
	return errno;
}

#endif /* WSFS_PLATFORM_LWIP */

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

#endif /* WSFS_SOCKET_H */
