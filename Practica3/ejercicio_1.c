#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define SIZE 512

int main(int argc, char **argv) {
    pid_t pid; //declaramos las tuberías
    int a[2], readbytes;
    char buffer[SIZE];

    pipe(a); 

    if((pid = fork()) == 0) { //fork() 
        //hijo
        close(a[1]); //cerramos el lado de escritura de la tuberia

        while((readbytes = read(a[0], buffer, SIZE)) > 0) { 
            write(1, buffer, readbytes); 
        }
        strcpy(buffer, "Soy el hijo hablando desde la otra tubería\n");
        close(a[1]); 
    }else {
        //padre
        close(a[0]); //cerramos la lectura de la tuberia
        strcpy(buffer, "Soy tu padre que te habla a través de la tubería\n");
        write(a[1], buffer, strlen(buffer));//funcion strlen: calcula el numero de caracteres hasta la cadena apuntada
        close(a[1]); 
    }
    waitpid(pid, NULL, 0); 
    return 0;
}