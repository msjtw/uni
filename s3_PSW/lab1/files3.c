#include "stdio.h"
#include <complex.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  int fd1 = open(argv[1], O_RDONLY);
  int fd2 = open(argv[2], O_WRONLY);
  char buff;
  while (read(fd1, &buff,1)) {
    write(fd2, &buff, 1);
  }

  close(fd1);
  close(fd2);
}
