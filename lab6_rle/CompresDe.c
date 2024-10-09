#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

int main() {
    FILE *fd1 = fopen("compres.txt", "r");
    FILE *fd2 = fopen("decompres.txt", "w");

    if (!fd1 || !fd2) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    char buffer[SIZE];
    fread(buffer, sizeof(char), SIZE, fd1);
    char tmp = buffer[0];
    int i = 1;
    int count = 1;

    while (i < SIZE && buffer[i] != '\0') {
        while (tmp == buffer[i] && i < SIZE) {
            count++;
            i++;
        }
        putc(tmp, fd2);
        fprintf(fd2, "%d", count);
        
        if (i < SIZE) {
            tmp = buffer[i];
            count = 1;
            i++;
        }
    }

    fclose(fd1);
    fclose(fd2);
    return 0;
}
