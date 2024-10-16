#include <complex.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argv, char* argc[]){
  int fd = open("in.in", O_RDWR);
  char buff, x = 'X';
  while(read(fd, &buff, 1)){
    if(buff == 'x'){
      lseek(fd, -1, SEEK_CUR);
      write(fd, &x, 1);
    }
  }
  close(fd);
  return 0;
}
