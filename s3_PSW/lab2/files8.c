#include <ctype.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    char buff;
    bool popsuted = false;
    int poz = 0;
    while (read(fd,&buff,1)) {
        if(!isascii(buff)){
            popsuted = true;
            printf("nie ascii %d->%c<-\n", poz, buff);
            break;
        }
        poz++;
    }
    if(popsuted){
        printf("NIE ASCII\n");
    }
    else{
        printf("JEST ASCII\n");
    }

    close(fd);
    return 0;
}
