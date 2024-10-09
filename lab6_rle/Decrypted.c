#include <stdio.h>
#include <stdlib.h>

#define size 1024

int main(){
    FILE* fd1 = fopen("decompres.txt","r+");  // The compressed file
    FILE* fd2 = fopen("decrypted.txt","w+");  // The file to write the original content
    
    if (fd1 == NULL || fd2 == NULL) {
        perror("Error opening file");
        return 1;
    }

    char character;
    unsigned char count;
    
   
    while(fread(&character, sizeof(char), 1, fd1) && fread(&count, sizeof(char), 1, fd1)) {
        
        for (int i = 0; i < count; i++) {

            fputc(character, fd2);
        }
    }

    fclose(fd1);
    fclose(fd2);
    
    return 0;
}
