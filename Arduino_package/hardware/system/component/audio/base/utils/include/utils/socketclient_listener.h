#ifndef AMEBA_UTILS_SOCKET_CLIENT_LISTENER_H
#define AMEBA_UTILS_SOCKET_CLIENT_LISTENER_H

#include "utils/socket_listener.h"

class SocketClientListener : public SocketListener
{
	char                            sock_buffer_[64 * 1024] __attribute__((aligned(4)));

public:
	SocketClientListener(const char *socket);
	virtual                         ~SocketClientListener() {}

protected:
	virtual bool                    OnDataAvailable(SocketClient *cli);
	virtual void                    OnEvent(void *evt, int size) = 0;
};

#endif //AMEBA_UTILS_SOCKET_CLIENT_LISTENER_H
