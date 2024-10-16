#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
  int fd = open("aaaa.txt", O_RDONLY);
  if(fd == -1){
    printf("Kod %d\n", errno);
    perror("Otwieranie pliku");
  }
  return 0;
}
