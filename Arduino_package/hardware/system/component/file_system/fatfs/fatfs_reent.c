#include "ff.h"
#include "ffconf.h"
#if _FS_REENTRANT
#include "osdep_service.h"

/* in those api, return 0 is mean fail */

int ff_cre_syncobj (BYTE vol, _SYNC_t* sobj)
{
	*sobj = malloc(sizeof(_mutex));
	if(!*sobj) return 0;
	rtw_mutex_init(*sobj);
	return 1;
}

int ff_req_grant (_SYNC_t sobj)
{
	rtw_mutex_get(sobj);
	return 1;
}

void ff_rel_grant (_SYNC_t sobj)
{
	rtw_mutex_put(sobj);
}

int ff_del_syncobj (_SYNC_t sobj)
{
	rtw_mutex_free(sobj);
	free(sobj);
	return 1;
}
#endif
				   