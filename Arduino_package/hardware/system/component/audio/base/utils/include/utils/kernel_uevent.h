#ifndef AMEBA_UTILS_KERNEL_UEVENT_H
#define AMEBA_UTILS_KERNEL_UEVENT_H

#include <stdbool.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

ssize_t         RecvUeventKernel(int socket, void *buffer, size_t length, bool require_group, uid_t *uid);

#ifdef __cplusplus
}
#endif

#endif /* AMEBA_UTILS_KERNEL_UEVENT_H */
