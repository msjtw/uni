#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++){
        int fd = open(argv[i], O_RDONLY);
        int chars = lseek(fd, 0, SEEK_END);
        chars *= sizeof(char);
        printf("file size: %d\n", chars);
        close(fd);
    }
}
