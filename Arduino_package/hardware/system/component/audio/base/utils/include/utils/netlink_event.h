#ifndef AMEBA_UTILS_NETLINKEVENT_H
#define AMEBA_UTILS_NETLINKEVENT_H

#include "utils/netlink_listener.h"
#include <linux/if.h>
#include <linux/if_addr.h>
#include <linux/if_link.h>
#include <linux/netfilter/nfnetlink.h>
#include <linux/netfilter/nfnetlink_log.h>

#define NL_PARAMS_MAX 32

typedef unsigned short uint16_t;

const int LOCAL_QLOG_NL_EVENT = 112;
const int LOCAL_NFLOG_PACKET = NFNL_SUBSYS_ULOG << 8 | NFULNL_MSG_PACKET;

class NetlinkEvent
{
public:
	enum class Action {
		kUnknown = 0,
		kAdd = 1,
		kRemove = 2,
		kChange = 3,
		kLinkUp = 4,
		kLinkDown = 5,
		kAddressUpdated = 6,
		kAddressRemoved = 7,
		kRdnss = 8,
		kRouteUpdated = 9,
		kRouteRemoved = 10,
	};

private:
	int                     uevent_seq_;
	char                    *uevent_path_;
	Action                  uevent_action_;
	char                    *uevent_subsystem_;
	char                    *uevent_params_[NL_PARAMS_MAX];

public:
	NetlinkEvent();
	virtual                 ~NetlinkEvent();

	bool                    DecodeUevent(char *buffer, int size, int format = NetlinkListener::NETLINK_FORMAT_ASCII);
	const char              *FindParam(const char *paramName);
	const char              *GetSubsystem()
	{
		return uevent_subsystem_;
	}
	Action                  GetAction()
	{
		return uevent_action_;
	}
	void                    DumpUeventMessage();

protected:
	bool                    ParseBinaryNetlinkMessage(char *buffer, int size);
	bool                    ParseAsciiNetlinkMessage(char *buffer, int size);
	bool                    ParseIfInfoMessage(const struct nlmsghdr *nh);
	bool                    ParseIfAddrMessage(const struct nlmsghdr *nh);
	bool                    ParseRtMessage(const struct nlmsghdr *nh);
};

#endif //AMEBA_UTILS_NETLINKEVENT_H