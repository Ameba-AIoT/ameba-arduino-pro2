#ifndef AMEBA_UTILS_SOCKETLISTENER_H
#define AMEBA_UTILS_SOCKETLISTENER_H

#include <pthread.h>

#include <utils/socket_client.h>

class SocketListener
{
	bool                                listen_flag_;
	const char                          *socket_name_;
	int                                 sock_id_;
	SocketClientCollection              *client_list_;
	pthread_mutex_t                     clients_lock_;
	int                                 ctrl_pipe_[2];
	pthread_t                           thread_id_;
	bool                                use_cmd_num_;

public:
	SocketListener(const char *socketName, bool listen);
	SocketListener(const char *socketName, bool listen, bool useCmdNum);
	SocketListener(int socketFd, bool listen);

	virtual                             ~SocketListener();
	int                                 StartListener();
	int                                 StartListener(int backlog);
	int                                 StopListener();

	void                                SendBroadcast(int code, const char *msg, bool addErrno);
	void                                SendBroadcast(const char *msg);
	bool                                Release(SocketClient *c)
	{
		return Release(c, true);
	}

protected:
	virtual bool                        OnDataAvailable(SocketClient *c) = 0;

private:
	bool                                Release(SocketClient *c, bool wakeup);
	static void                         *ThreadStart(void *obj);
	void                                RunListener();
	void                                Init(const char *socketName, int socketFd, bool listen, bool useCmdNum);
};
#endif //AMEBA_UTILS_SOCKETLISTENER_H
