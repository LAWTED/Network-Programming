#include <stdio.h>      /* for printf () and fprintf () */
#include <sys/socket.h> /* for socket(), sendto () and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset () */
#include <unistd.h>     /* for close() */

#define ECHOMAX 255 /* Longest String to echo*/

// 172.30.26.84
// 39.105.203.33

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    struct sockaddr_in fromAddr;     /* source address of echo */
    unsigned short echoServPort;     /* Echo server port */
    unsigned int fromSize;           /* In-out of address size from recvfrom() */

    char *servIP;
    char *echoString;
    char echoBuffer[ECHOMAX + 1];

    int echoStringLen;
    int respStringLen;

    if ((argc < 3))
    {
        printf("Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];
    echoString = argv[2];
    if (((echoStringLen = strlen(echoString)) > ECHOMAX))
        printf("Echo word too long. \n");
    char *echoArray[argc];
    for (int i = 2; i < argc; i++)
    {
        echoArray[i] = argv[i];
    }
    // if (argc == 4)
    //     echoServPort = atoi(argv[3]);
    // else
    echoServPort = 7;

    for (int i = 2; i < argc; i++)
    {
        /* Create a datagram/UDP socket */
        if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
            printf("Socket() failed.\n");

        /* Construct the server address structure */
        memset(&echoServAddr, 0, sizeof(echoServAddr));
        echoServAddr.sin_family = AF_INET;
        echoServAddr.sin_addr.s_addr = inet_addr(servIP);
        echoServAddr.sin_port = htons(echoServPort);

        printf("Sending: %s\n", echoArray[i]);
        char *echoSendStringTmp = echoArray[i];
        /* Send the String to the server*/
        if ((sendto(sock, echoSendStringTmp, strlen(echoSendStringTmp), 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr))) != strlen(echoSendStringTmp))
            printf("sendto() sent a different number of bytes than expected.\n");
        /* Recv a response */
        fromSize = sizeof(fromAddr);
        if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *)&fromAddr, &fromSize)) != strlen(echoSendStringTmp))
            printf("recvfrom() failed\n");

        if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
        {
            printf("Error: received a packet from unknown source.\n");
            exit(1);
        }

        /* null-terminate the received data*/
        echoBuffer[respStringLen] = '\0';
        printf("Received: %s\n", echoBuffer);
    }
    close(sock);
    exit(0);
}