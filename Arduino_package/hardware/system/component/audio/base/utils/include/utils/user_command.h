
#ifndef AMEBA_UTILS_USER_CMD_HANDLER_H
#define AMEBA_UTILS_USER_CMD_HANDLER_H

#include <list>

class SocketClient;

class UserCommand
{
private:
	const char              *user_command_;

public:
	UserCommand(const char *cmd);
	virtual                 ~UserCommand() {}
	virtual int             RunCommand(SocketClient *c, int argc, char **argv) = 0;

	const char             *GetCommand()
	{
		return user_command_;
	}
};
typedef std::list<UserCommand *> FrameworkCommandCollection;

#endif //AMEBA_UTILS_STORAGED_USER_CMD_HANDLER_H