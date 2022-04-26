#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])

{
  int in, out;
  char buf[10];
  in = open("in.txt", O_RDONLY);
  int size = lseek(in, 0, SEEK_END);
  lseek(in, 0, SEEK_SET);
  out = open("out.txt", O_RDWR | O_APPEND);
  int pd;
  while (read(in, buf, size) == size)
    pd = write(out,buf,size);
  close(in);close(out);
  if (pd != -1)
    printf("Success");
  else
    printf("Error");
}