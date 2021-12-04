#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

    int Par[10];
    int Impar[10];

int main(int argc, char *argv[]){
    
    pid_t pid1, pid2;//Creamos los dos procesos hijos
    int status1=0,status2=0;
    int my_pipe[2];
    int my_pipe2[2];


    if (pipe(my_pipe2)==-1){ 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 

    if (pipe(my_pipe)==-1){ 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    //En caso de que no se creen las pipes lanzamos el mensaje de error

    if((pid1=fork())==0){
        //Proceso hijo 1
        close(my_pipe[0]);//El indice 0 de la tuberia indica que es de tipo lectura
        printf("Child %d\n", getpid());//Imprimimos el PID del hijo
        int impar=1;
        for(int i=0;i<10;i++){
            Impar[i]=impar*impar;    
            impar+=2;
        }//Realizamos las operaciones que nos pedia el ejercicio

        write(my_pipe[1],&Impar,sizeof(Impar)+1);//Escribimos en el canal 1 del pipe el array con los resultados
        exit(EXIT_SUCCESS);
        
    }else{//Proceso padre
        if((pid2=fork())==0){
            //Proceso hijo 2
            close(my_pipe2[0]);//El indice 0 de la tuberia indica que es de tipo lectura
            printf("Child %d\n", getpid());//Imprimimos el PID del hijo
            int par=2;
            for(int i=0;i<10;i++){
                Par[i]=par*par;
                par+=2;
            } //Realizamos las operaciones que nos pedia el ejercicio
            write(my_pipe2[1],&Par,sizeof(Par)+1);//Escribimos en el canal 1 del pipe el array con los resultados
            
            
            exit(EXIT_SUCCESS);
            
        
        }else{
            printf("Father%d\n", getpid());//Imprimimos el PID del proceso padre

            waitpid(pid1,&status1,2);
            close(my_pipe[1]);

            waitpid(pid2,&status2,2);
            close(my_pipe2[1])
            
           
            int ParS[10];
            int ImparS[10];
            int Total[20];

            //Creamos los arrays que usaremos para leer los datos
            
            read(my_pipe[0],ImparS,sizeof(ImparS));
            read(my_pipe2[0],ParS,sizeof(ParS));

            int indexImpar=0;
            int indexPar=0;

            //Creamos unas variables auxiliares para ayudarnos a introducir los datos de los hijos en el Array Total

            for(int i = 0; i < 20;){
                Total[i]=ImparS[indexImpar];
                i++;
                indexImpar++;
                Total[i]=ParS[indexPar];
                i++;
                indexPar++;
            }//Recorremos el array total y vamos introduciendo los datos de los procesos hijos en el

            for(int i=0;i<20;i++) printf("%i ", Total[i]);//Imprimimos los resultados por pantalla
            
        }
    }
    return 0;
}
