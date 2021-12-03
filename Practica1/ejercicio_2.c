#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> //Librería para operaciones matemáticas

int main(void) {
	
	pid_t childpid1, childpid2;
    int status1, status2;
    int pares[10], impares[10];
	
	if ((childpid1 = fork()) == 0) {
		for(int i = 0; i < 19; i = i + 2) {
            impares[i/2] = i * i;
        }	
		
	} else {
        if ((childpid2 = fork()) == 0) {
            for(int i = 1; i < 20; i = i + 2) {
                pares[i/2] = i * i;
            }
        }else {
            waitpid(childpid1, &status1, 0);
            waitpid(childpid2, &status2, 0);

            int complet[20];

            for(int i = 0; i < 20; i++) {
                if(i % 2 == 0) {
                    complet[i] = pares[i/2];
                } else {
                    complet[i] = impares[i/2];
                }
                printf("%d\n", complet[i]);
            }
        }
    }
	exit(0);
}