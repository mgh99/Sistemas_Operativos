#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


pthread_t thread1, thread2, threadmain;
pthread_attr_t attr;
int globalvar=0;

void *incrementBy2(void *);
void *incrementBy1(void *);

void *incrementBy2(void *args){
    pthread_mutex_t* mutex = args; //guardo el parametro mutex pasado.
    pthread_mutex_lock(mutex);

    printf("Empieza el hilo 1 -> ");
    for(int i=0; i < 4; i++){
        globalvar += 2;
        printf("%d, ", globalvar);
    }
    printf("-> Thread 1 terminado.\n");

    pthread_mutex_unlock(mutex);
    pthread_exit(NULL); // termino la función del hilo (IMPRESCINDIBLE)
}

void *incrementBy1(void *args){
    pthread_mutex_t* mutex = args; //guardo el parametro mutex pasado.
    pthread_mutex_lock(mutex);

    printf("Empieza el hilo 2 -> ");
    for(int i=0; i < 4; i++){
        globalvar++;
        printf("%d, ", globalvar);
    }
    printf("-> Thread 2 terminado.\n");

    pthread_mutex_unlock(mutex);
    pthread_exit(NULL); // termino la función del hilo (IMPRESCINDIBLE)
}

int main(void){

    threadmain = pthread_self(); // thread actual
    pthread_attr_init(&attr);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, &attr, incrementBy1, &mutex); // threadmain crea thread 1 y le pasa el parametro num1
    pthread_create(&thread2, &attr, incrementBy2, &mutex); // threadmain crea thread 2 y le pasa el parametro num2

    pthread_join(thread1, NULL); //espera a que termine el thread1
    pthread_join(thread2, NULL); //espera a que termine el thread2

    printf("Programa terminado.");
    

     exit(0);
}