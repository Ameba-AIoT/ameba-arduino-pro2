#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__WIN32__) // MINGW64
//#include <winsock.h>
#include <winsock2.h>
#include <windows.h>
#elif defined(__linux__) // ubuntu
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif defined(__APPLE__) // macOS
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#endif
#include <unistd.h>

#define BUFSIZE 1024

//const char *hostname = "192.168.2.29";
const char *hostname = "0.0.0.0";
int portno = 5001;

int main(int argc, char **argv) {
    int n;
    struct sockaddr_in serveraddr;
#if defined(__APPLE__)
    socklen_t serverlen = sizeof(serveraddr);
#else
    int serverlen = sizeof(serveraddr);
#endif
    char buf[BUFSIZE];
    int counter = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        return -1;
    }
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
        perror("ERROR opening socket");
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
        counter = (counter + 1) % 10;
        sprintf(buf, "%d", counter);

        /* send the message to the server */
        n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serveraddr, serverlen);
        if (n < 0) {
            perror("ERROR in sendto");
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
