#include <complex.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argv, char* argc[]){
  int fd = creat(argc[1],0640);
  write(fd, argc[2], strlen(argc[2]));
  close(fd);
  return 0;
}
