#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //LIbrería necesaria para lseek

int main(void) {
	
	int fd, bytes_escritos, bytes_leidos; //descriptor del fichero
	char buffer[100];
	mode_t modo = S_IRWXU; //modo de r, w y x para el propietario
	
	strcpy(buffer, "Esto es un ejemplo\n");
	if((fd = open ("ejemplo", O_RDWR | O_CREAT, modo)) == -1)
		//abre el fichero ejemplo en modo lectura/escritura o lo crea si no existe
		perror ("Error al abrir o crear el fichero");
		
	//muestra un mensaje de error si no puede abrir/crear el fichero
	else
		bytes_escritos = write(fd, buffer, strlen(buffer));
		//Colocamos un puntero en la posición 0  y lo leemos
		//Utilizamos lseek -> que srive para reposicionar un puntero de lectura/escritura de un fichero
		
		lseek(fd, 0, SEEK_SET);
		bytes_leidos = read(fd, buffer, strlen(buffer));
		
		printf("Mensaje: %s, Bytes escritos: %d, Bytes leidos: %d\n", buffer, bytes_escritos, bytes_leidos);
		
	exit(0);
}
