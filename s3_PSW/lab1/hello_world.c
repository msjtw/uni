#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    for (int i= 1; i < argc; i++) {
      printf("argument %d %s \n", i, argv[i]);
    }
    printf("Koniec...\n");
    return 0;
}
