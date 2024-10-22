#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void awrite(int fd1, int fd2){
    char buff;
    while(read(fd1, &buff, 1)){
        write(fd2, &buff, 1);
    }
    buff = '\n';
    write(fd2, &buff,1);
}

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDWR);
    lseek(fd2, 0, SEEK_SET);
        
    lseek(fd1, -11, SEEK_END);
    awrite(fd1, fd2);

    lseek(fd1, 1, SEEK_END);
    int count = 0;
    do{
        lseek(fd1, -2, SEEK_CUR);
        char buff;
        read(fd1, &buff, 1);
        if(buff == ' ' || buff == '\n'){
            count++;
        }
    }while(count < 12);
    awrite(fd1,fd2);

    lseek(fd1, 1, SEEK_END);
    count = 0;
    do{
        lseek(fd1, -2, SEEK_CUR);
        char buff;
        read(fd1, &buff, 1);
        if(buff == '\n')
            count++;
    }while(count < 11);
    awrite(fd1, fd2);

    close(fd1);
    close(fd2);
    return 0;
}
