
#include "stdio.h"
#include <complex.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int fd = open(argv[1],O_RDONLY);
    int maxi = 0;
    char buff;
    int count = 0;
    while(read(fd,&buff,1)){
        if(buff == '\n'){
            if(count > maxi){
                maxi = count;
            }
            count = 0;
        }
        else{
            count++;
        }
    }
    printf("Longest line in file: %d characters", maxi);
    close(fd);
    return 0;
}
