#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    for(int i = 1; i < argc; i++){
        int fd = open(argv[i], O_RDONLY, 0664);
        char buf[20];
        int n;
        while((n=read(fd,buf,20)) > 0){
            printf("%s", buf);
        }
        close(n);
    }
    return 0;
}