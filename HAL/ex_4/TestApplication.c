#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
  int fd;
  int status =0;

  fd = open("/dev/mygpio_16", O_RDWR);

  status = close(fd);

  fd = open("/dev/mygpio_21", O_RDWR);

  status = close(fd);

  return status;
}
