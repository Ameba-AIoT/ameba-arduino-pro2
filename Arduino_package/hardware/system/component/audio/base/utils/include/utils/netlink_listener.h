#ifndef AMEBA_UTILS_NETLINKLISTENER_H
#define AMEBA_UTILS_NETLINKLISTENER_H

#include "socket_listener.h"

class NetlinkEvent;

class NetlinkListener : public SocketListener
{
	char                socket_buffer_[64 * 1024] __attribute__((aligned(4)));
	int                 mFormat;
public:
	static const int    NETLINK_FORMAT_ASCII = 0;
	static const int    NETLINK_FORMAT_BINARY = 1;
	static const int    NETLINK_FORMAT_BINARY_UNICAST = 2;
	NetlinkListener(int socket);
	NetlinkListener(int socket, int format);
	virtual             ~NetlinkListener() {}

protected:
	virtual bool        OnDataAvailable(SocketClient *cli);
	virtual void        OnEvent(NetlinkEvent *evt) = 0;
};

#endif //AMEBA_UTILS_NETLINKLISTENER_H