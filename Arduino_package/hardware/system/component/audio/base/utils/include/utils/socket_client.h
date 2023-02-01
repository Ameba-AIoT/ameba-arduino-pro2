#ifndef AMEBA_UTILS_SOCKET_CLIENT_H
#define AMEBA_UTILS_SOCKET_CLIENT_H

//#include "List.h"
#include <list>

#include <pthread.h>
//#include <cutils/atomic.h>
#include <sys/types.h>
#include <sys/uio.h>

class SocketClient
{
	int                             socket_;
	bool                            socket_owned_;
	pthread_mutex_t                 write_mutex_;

	// Peer process ID
	pid_t                           pid_;
	// Peer user ID
	uid_t                           uid_;
	// Peer group ID
	gid_t                           gid_;

	// Reference count (starts at 1)
	pthread_mutex_t                 ref_count_mutex_;
	int                             ref_count_;
	int                             cmd_num_;
	bool                            use_cmd_num_;

public:
	SocketClient(int sock, bool owned);
	SocketClient(int sock, bool owned, bool useCmdNum);
	virtual                         ~SocketClient();

	int                             GetSocket()
	{
		return socket_;
	}
	pid_t                           GetPid() const
	{
		return pid_;
	}
	uid_t                           GetUid() const
	{
		return uid_;
	}
	gid_t                           GetGid() const
	{
		return gid_;
	}
	void                            SetCmdNum(int cmdNum)
	{
		cmd_num_ = cmdNum;
	}
	int                             GetCmdNum()
	{
		return cmd_num_;
	}

	// Send null-terminated C strings:
	int                             SendMsg(int code, const char *msg, bool addErrno);
	int                             SendMsg(int code, const char *msg, bool addErrno, bool useCmdNum);
	int                             SendMsg(const char *msg);

	int                             SendCode(int code);
	int                             SendBinaryMsg(int code, const void *data, int len);
	int                             SendData(const void *data, int len);
	int                             SendDatav(struct iovec *iov, int iovcnt);

	void                            AddRefCount();
	bool                            DecRefCount();

	static                          char *QuoteArg(const char *arg);

private:
	void                            Init(int socket, bool owned, bool useCmdNum);
	int                             SendDataLockedv(struct iovec *iov, int iovcnt);
};

typedef std::list<SocketClient *> SocketClientCollection;

#endif //AMEBA_UTILS_SOCKET_CLIENT_H
