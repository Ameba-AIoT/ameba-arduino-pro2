/*------------------------------------------------------------------------*/
/* Sample Code of OS Dependent Functions for FatFs                        */
/* (C)ChaN, 2018                                                          */
/*------------------------------------------------------------------------*/


#include "ff.h"


#if FF_USE_LFN == 3	/* Dynamic memory allocation */

/*------------------------------------------------------------------------*/
/* Allocate a memory block                                                */
/*------------------------------------------------------------------------*/

void *ff_memalloc(  /* Returns pointer to the allocated memory block (null if not enough core) */
	UINT msize		/* Number of bytes to allocate */
)
{
	return malloc(msize);	/* Allocate a new memory block with POSIX API */
}


/*------------------------------------------------------------------------*/
/* Free a memory block                                                    */
/*------------------------------------------------------------------------*/

void ff_memfree(
	void *mblock	/* Pointer to the memory block to free (nothing to do if null) */
)
{
	free(mblock);	/* Free the memory block with POSIX API */
}

#endif



#if FF_FS_REENTRANT	/* Mutal exclusion */

#include "osdep_service.h"

/* in those api, return 0 is mean fail */

int ff_cre_syncobj(BYTE vol, FF_SYNC_t *sobj)
{
	*sobj = malloc(sizeof(_mutex));
	if (!*sobj) {
		return 0;
	}
	rtw_mutex_init(*sobj);
	return 1;
}

int ff_req_grant(FF_SYNC_t sobj)
{
	rtw_mutex_get(sobj);
	return 1;
}

void ff_rel_grant(FF_SYNC_t sobj)
{
	rtw_mutex_put(sobj);
}

int ff_del_syncobj(FF_SYNC_t sobj)
{
	rtw_mutex_free(sobj);
	free(sobj);
	return 1;
}

#endif

