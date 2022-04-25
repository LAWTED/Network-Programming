#include <stdio.h>      /* for printf () and fprintf () */
#include <sys/socket.h> /* for socket(), sendto () and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset () */
#include <unistd.h>     /* for close() */

#define ECHOMAX 255 /* Longest String to echo*/

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;
    char echoBuffer[ECHOMAX];
    unsigned short echoServPort;
    int recvMsgSize;

    if (argc != 2)
    {
        printf("Usage: %s <UDP SERVER PORT>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);

    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        printf("Socket() failed.\n");

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    if ((bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr))) < 0)
        printf("bind() failed.\n");

    while (1)
    {
        cliAddrLen = sizeof(echoClntAddr);

        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *)&echoClntAddr, &cliAddrLen)) < 0)
            printf("recvfrom() failed.\n");

        printf("Handing client %s:UDP%d Receiving: %s\n", inet_ntoa(echoClntAddr.sin_addr), getpid(), echoBuffer);

        if ((sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *)&echoClntAddr, sizeof(echoClntAddr))) != recvMsgSize)
            printf("sendto() sent a different number of bytes than expected.\n");
    }
}