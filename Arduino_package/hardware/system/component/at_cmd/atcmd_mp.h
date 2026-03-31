#ifndef __ATCMD_MP_H__
#define __ATCMD_MP_H__

typedef struct _at_command_mp_ext_item_ {
	const char	*mp_ext_cmd;
	int	(*mp_ext_fun)(void **argv, int argc);
	const char	*mp_ext_usage;
} at_mp_ext_item_t;

#endif
