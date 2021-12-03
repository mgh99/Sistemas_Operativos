#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static long recursive_search(char *dirname) {
    
    DIR *dir = opendir(dirname); 
    struct dirent *ent; //estructura que contiene los datos de un archivo
    struct stat st; 
    long size = 0;
    long total = 0;
    char path[1024];

    if(dir == 0) { //Si no se puede abrir el directorio
        exit(-1);
    }

    while((ent = readdir(dir)) != NULL) {
        if((strcmp(ent-> d_name, ".") == 0) || (strcmp(ent-> d_name, "..") == 0)) { //Si es un directorio padre o actual no se procesa o se suma al total
            continue;
        }

        printf(path, "%s/%s", dirname, ent-> d_name); //Se concatena el nombre del directorio con el nombre del archivo

        if(lstat(path, &st) != 0) { //Se obtiene la informacion del archivo o directorio
            continue;
        }

        size = st.st_size; //Se obtiene el tamaño del archivo o directorio

        if(S_ISDIR(st.st_mode)) {
            long dir_size = recursive_search(path) + size; //Se llama recursivamente a la funcion para obtener el tamaño del directorio
            printf("DIR\t");
            printf("SIZE: %ld\n", dir_size);
            total += dir_size;
        }else {
            total += size;
            printf("FILES\t");
            printf("SIZE: %ld\n", size);
        }
    }
    return total;
}

int main(int argc, char *argv[]) {
    
    if(argc != 2) { //Gestion de errores
        perror("Ninguno o mas de un argumento");
    }

    long size = recursive_search(argv[1]); //retorna el tamaño total del directorio
    printf("Total: size: %ld Bytes\n", size);
    return 0;
}
