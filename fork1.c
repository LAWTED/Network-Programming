#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  pid_t t;
  t = fork();
  printf("fork returned %d\n", t);
  exit(0);
  // fork() retuns 0 to the child process
  // and returns the process ID of the child process to the parent process
}
