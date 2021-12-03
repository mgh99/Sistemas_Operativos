#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int fd;
    char buffer[1000]; 
    size_t numBytes = 1000;
    int bytesRead;

    if((fd = open("./Practica5/test.txt", O_RDONLY, 444)) == -1) {
        perror("Error al abrir el archivo");
    } else {
        bytesRead = read(fd, buffer, numBytes);
    }

    for(int i = 99; i <= 108; i++) {
        printf("%c", buffer[i]);
    }

    close(fd);
    exit(0);
}