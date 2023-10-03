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
#endif

#include <sys/time.h>
#include <unistd.h>

#define BUFSIZE 1024

//const char *hostname = "192.168.2.29";
const char *hostname = "0.0.0.0";
int portno = 5001;

long base_current_time = 0;
long get_current_time_with_ms(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    long millisecondsSinceEpoch = ((long)(tv.tv_sec)) * 1000 + ((long)(tv.tv_usec)) / 1000;

    if (base_current_time == 0) {
        base_current_time = millisecondsSinceEpoch;
        return 0;
    } else {
        return millisecondsSinceEpoch - base_current_time;
    }
}

int main(int argc, char **argv) {
    int n;
    struct sockaddr_in serveraddr;
    int serverlen = sizeof(serveraddr);
    char buf[BUFSIZE];

    hostname = argv[1];

    /* socket: create the socket */
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

    /* build the server's Internet address */
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(hostname);
    serveraddr.sin_port = htons(portno);

    while (1) {
        memset(buf, 0, BUFSIZE);
        sprintf(buf, "%ld", get_current_time_with_ms());

        /* send the message to the server */
        n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serveraddr, serverlen);
        if (n < 0) {
            printf("ERROR in sendto\r\n");
            return -1;
        }
#if defined(__WIN32__) // MINGW64
        Sleep(5);
#else
        usleep(5 * 1000);
#endif
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
