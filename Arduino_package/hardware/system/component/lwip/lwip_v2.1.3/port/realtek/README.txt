LWIP_NETCONN_SEM_PER_THREAD Notes:
Use one (thread-local) semaphore per thread calling socket/netconn functions instead of allocating one
semaphore per netconn (and per select etc.)
 * ATTENTION: a thread-local semaphore for API calls is needed:
 * - LWIP_NETCONN_THREAD_SEM_GET() returning a sys_sem_t*
 * - LWIP_NETCONN_THREAD_SEM_ALLOC() creating the semaphore
 * - LWIP_NETCONN_THREAD_SEM_FREE() freeing the semaphore
 * The latter 2 can be invoked up by calling netconn_thread_init()/netconn_thread_cleanup().
 * Ports may call these for threads created with sys_thread_new().

LWIP_NETCONN_SEM_PER_THREAD Test Procedure:
1. Enable both macro (LWIP_NETCONN_SEM_PER_THREAD & LWIP_NETCONN_FULLDUPLEX) in opt.h
2. Uncomment #define configNUM_THREAD_LOCAL_STORAGE_POINTERS 1 under "inc\FreeRTOSconfig.h"
3. First call sys_arch_netconn_sem_alloc() before initiating a connection

* The APIs: 
	sys_arch_netconn_sem_get()
	sys_arch_netconn_sem_alloc() 
	sys_arch_netconn_sem_free()
is referenced from : https://github.com/lwip-tcpip/lwip/blob/master/contrib/ports/freertos/sys_arch.c