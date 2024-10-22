#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);

    printf("znaki od konca:\n");
    lseek(fd, -1, SEEK_END);
    char buff;
    do{
        read(fd, &buff, 1);
        printf("%c", buff);
    } while (lseek(fd, -2, SEEK_CUR) >= 0); 

    printf("\nlinie od konca:\n");
    int last = lseek(fd, -3, SEEK_END);
    do {
        read(fd, &buff, 1);
        int curr = lseek(fd, 0, SEEK_CUR);
        if(buff == '\n'){
            do {
                read(fd, &buff, 1);
                printf("%c", buff);
            }while (isalnum(buff));
            lseek(fd, curr, SEEK_SET);
        }
    }while (lseek(fd, -2, SEEK_CUR) > 0);
    
    return 0;
}
