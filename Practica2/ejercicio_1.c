#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

pthread_t thread1, thread2, threadmain; //declaramos los threads
pthread_attr_t attr; //atributos de los threads

void *factorial(void *);

//Función que calcula el factorial utilizando los threads
void *factorial (void *args) {
    int* number = (int*) args; //Se lee el parametro del thread (num1/num2)
    int factorial = 1;

    printf("Factorial de: %d \n", *number);

    while(*number > 1) {
        factorial = factorial * (*number);
        *number = *number - 1;
    }

    printf("es: %d \n", factorial);
    pthread_exit(NULL); //Se termina la función del hilo (SIEMPRE HAY QUE PONERLO)
}

int main(void) {

    printf("CALCULO DEL FACTORIAL DE 2 NUMEROS DE MANERA CONCURRENTE\n");

    threadmain = pthread_self(); //Devuelve la identidad del thread que lo invoca
    pthread_attr_init(&attr); //Inicializa la identidad del thread que lo invoca

    int num1 = 3, num2 = 4;

    pthread_create(&thread1, &attr, factorial, (void *)&num1); //Crea un thread1 para ejecutar una funcion determinada
    pthread_create(&thread2, &attr, factorial, (void *)&num2); //Crea un thread2 para ejecutar una funcion determinada

    pthread_join(thread1, NULL); //Espera hasta que termine el thread que se ha invocado, en este caso el thread1
    pthread_join(thread2, NULL); //Espera hasta que termina el thread que se ha invocado, en este caso el thread2

    pthread_exit(NULL); //Fin del programa
}