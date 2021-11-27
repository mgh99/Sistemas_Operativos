#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int buffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
sem_t semaforo; //variable para asignar los semaforos

void *thread1 (void *arg) {
    int i;
    printf("\nEstoy llenando el buffer\n");

    for (i = 0; i < 10; i++) {
        sem_wait(&semaforo); //semaforo para que no se pueda acceder al buffer mientras se llena
        buffer[i] = i + 1; //llenamos el buffer
        printf("Productor: %d\n", buffer[i]); //Se produce información que se guarda en el buffer
        sem_post(&semaforo);
    }

    sleep(random() % 3); 
    pthread_exit(NULL);
}

void *thread2 (void *arg) { 
    int i;
    printf("\nLos valores del buffer\n");

    for (i = 0; i < 10; i++) { //Se imprime el contenido del buffer
        sem_wait(&semaforo);
        printf("%d ", buffer[i]); 
        buffer[i] = 0;
        sem_post(&semaforo);
    }

    sleep(random() % 3);
    printf("\n");

    for(i = 0; i < 10; i++) { 
        printf("%d", buffer[i]);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) { //PROBLEMA: NO PARA EL SEMAFORO, Y TAMPOCO PARA EL BUFFER
    pthread_t hilo1, hilo2;
    time_t t;
    srandom(time(&t));

    sem_init(&semaforo, 0, 10);

    while(1) { //Se crean los hilos
        pthread_create(&hilo1, NULL, *thread1, NULL);
        pthread_create(&hilo2, NULL, *thread2, NULL);
        
        if(buffer[0] == 0) { //Si el buffer está vacío se cierra el programa
            pthread_join(hilo1, NULL);
        } else {
            pthread_join(hilo2, NULL);
        }
    }
    sem_destroy(&semaforo);
    return 0;
}