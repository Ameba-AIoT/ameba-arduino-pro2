#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__WIN32__) // MINGW64
//#include <winsock.h>
#include <winsock2.h>
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)// ubuntu 32 bits  and OS X 64bits
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#error
#endif

#include <sys/time.h>

#define BUFSIZE 1024
#define PORT 5001

long get_current_time_with_ms(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    long millisecondsSinceEpoch = ((long)(tv.tv_sec)) * 1000 + ((long)(tv.tv_usec)) / 1000;

    return millisecondsSinceEpoch;
}

long early_diff = 0;

long ameba_epoch = 0;
long sys_epoch = 0;

long datacount = 0;
long total_shift = 0;

void process_data(char *buf) {
    long data;
    long timediff;
    long current_epoch;

    // Packet content is Ameba's current system time
    data = atol(buf);

    if (ameba_epoch == 0) {
        /* We sync Ameba's system and PC's system time on first packet */
        ameba_epoch = data;
        sys_epoch = get_current_time_with_ms();
    } else {
        /* Calculate the delay */
        current_epoch = get_current_time_with_ms();
        timediff = (current_epoch - sys_epoch) - (data - ameba_epoch);

        if (-timediff > early_diff) {
            /* This packet came in earlier than expected. It means there is some delay at first packet. Record this deley. */
            early_diff = -timediff;
        }

        total_shift += timediff;
        datacount++;

        if (datacount % 1000 == 0) {
            printf("\r\ndata count: %ld\t average delay:%f ms", datacount, (early_diff + total_shift * 1.0 / datacount));
        }
    }
}

int main(int argc, char **argv) {
    printf("Please wait.");

    int optval = 1;

    struct sockaddr_in serveraddr, clientaddr;
#if defined(__CYGWIN__) || defined(__WIN32__)
    int clientaddr_len = sizeof(clientaddr);
#else
    unsigned int clientaddr_len = sizeof(clientaddr);
#endif

    struct hostent *hostp;
    char *hostaddrp;

    int n;
    char buf[BUFSIZE];

#if defined(__WIN32__) // MINGW64
    // Declare and initialize variables
    WSADATA wsaData = {0};
    int iResult = 0;
    SOCKET sockfd = INVALID_SOCKET;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d \r\n", iResult);
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("ERROR %d opening socket \r\n",  WSAGetLastError());
        return -1;
    }
#else
    int sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("ERROR %d opening socket\r\n", sockfd);
        return -1;
    }
#endif

#if defined(__CYGWIN__) || defined(__WIN32__)
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval , sizeof(int));
#else
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
#endif

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
        printf("ERROR on binding\r\n");
    }

    while (1) {
        memset(buf, 0, BUFSIZE);
        n = recvfrom(sockfd, buf, (BUFSIZE - 1), 0, (struct sockaddr *)(&clientaddr), &clientaddr_len);
        if (n < 0) {
            printf("\r\nERROR in recvfrom\r\n");
            return -1;
        }
        process_data(buf);
    }

#if defined(__WIN32__) // MINGW64
    iResult = closesocket(sockfd);
    if (iResult == SOCKET_ERROR) {
        printf("closesocket failed with error: %d \r\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // Clean up and quit.
    printf("Exiting. \r\n");
    WSACleanup();
#endif

    return 0;
}
