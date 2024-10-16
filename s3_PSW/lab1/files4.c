#include "stdio.h"
#include <complex.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  int fd = open(argv[1],O_RDONLY);
  lseek(fd, SEEK_END, 0);
  do{
    char buff;
    read(fd, &buff, 1);
    printf("%c", buff);
  }while(lseek(fd, -1, SEEK_CUR));
  close(fd);
  return 0;
}
