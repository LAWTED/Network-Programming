#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# define ECHOMAX 255
int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in echoServAddr;
  struct sockaddr_in fromAddr;

}