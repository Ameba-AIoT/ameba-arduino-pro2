#ifndef AMEBA_UTILS_FRAMEWORKSOCKETLISTENER_H
#define AMEBA_UTILS_FRAMEWORKSOCKETLISTENER_H

#include "socket_listener.h"
#include "user_command.h"

class SocketClient;

class SocketServerListener : public SocketListener
{
public:
	static const int                CMD_ARGS_MAX = 26;

private:
	int                             command_count_;
	bool                            seq_enable_;
	FrameworkCommandCollection      *command_list_;
	bool                            skip_to_next_nullbyte_;

public:
	SocketServerListener(const char *socketName);
	SocketServerListener(const char *socketName, bool withSeq);
	SocketServerListener(int sock);
	virtual                         ~SocketServerListener() {}

protected:
	void                            RegisterCmd(UserCommand *cmd);
	virtual bool                    OnDataAvailable(SocketClient *c);

private:
	void                            DispatchCommand(SocketClient *c, char *data);
	void                            Init(const char *socketName, bool withSeq);
};
#endif  //AMEBA_UTILS_FRAMEWORKSOCKETLISTENER_H
