#include <unistd.h>
#include <stdio.h>
int main(void)
{
  char *arg[] = {"/bin/ls", 0};
  // char* arg[] = {"ls", "-l", "-R", "-a", NULL};
  // fork, and exec within child process
  if (fork() == 0)
  {
    printf("In child process:\n");
    execv("/bin/ls", arg);
    printf("I will nerver be called\n");
  }
  printf("Execution continues in parent precess\n");
}