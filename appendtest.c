
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
  int pos = lseek(out,0,SEEK_CUR);
  printf("initial the cursor is on:%d\n",pos);
  pos = lseek(out,5, SEEK_CUR);
  printf("now the cursor is on:%d\n",pos);
  int pd;
  while (read(in, buf, size) == size)
    pd = write(out,buf,size);
    pos = lseek(out,0,SEEK_CUR);
    printf("while writing the cursor is on:%d\n", pos);
  close(in);close(out);
  if (pd != -1)
    printf("Success");
  else
    printf("Error");
}
// when using O_APPEND the initial pos is on 0 and
// it will change to the SEEK_END when write and the lseek before it won't work!