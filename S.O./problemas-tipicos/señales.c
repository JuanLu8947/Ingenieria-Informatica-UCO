//Librerías estándar de C
#include <stdio.h>
#include <stdlib.h>

//Para exit(EXIT_SUCCESS)
#include <string.h>

//Para pid_t
#include <sys/types.h>

//Para fork
#include <unistd.h>

//Para la espera de los hijos
#include <sys/wait.h>

//Para errno y strerror
#include <errno.h>

//Para el uso de rand
#include <time.h>

//Para señales
#include <signal.h>

//libreria matematica
//#include <math.h>  //no se usa

//Para el uso de booleans values
#include <stdbool.h>

void funcionManejadoraHijo(int sig){
    printf("HIJO --> Soy %ld y he recibido la señal SIGINT(%d) y la ignoro...\n", (long int)getpid(), sig);
    kill(getppid(), SIGUSR1);
}

void funcionManejadoraPadre(int sig){
    printf("PADRE --> Soy %ld y he recibido la señal SIGUSR1(%d) y la ignoro...\n", (long int)getpid(), sig);
}

int main(int argc, char **argv){
    if(argc < 3){
        fprintf(stderr, "arg error\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    int n = 3;
    bool padre = true;
    for(int i=0; i<n; i++){
        pid = fork();
        switch(pid){
            case -1:
                fprintf(stderr, "fork error\n");
                exit(EXIT_FAILURE);
            case 0: //hijo
                printf("Soy el hijo %d con PID %ld y mi padre es %ld\n\n", i, (long int)getpid(), (long int)getppid());
                if(i==0){
                    if(execlp(argv[1], argv[1], NULL) == -1){
                        fprintf(stderr,"execlp error\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if(i==1){
                    if(execvp(argv[2], &(argv)[2]) == -1){
                        fprintf(stderr, "execvp error\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if(i==2){
                    //
                }
            //exit(EXIT_SUCCESS); //normalmente el hijo se sale
            default: //padre
                if(padre==true){
                    printf("Soy el padre con PID %ld, y la terminal es %ld\n", (long int) getpid(), (long int) getppid());
                    padre = false;
                }
        }
    }
    pid_t flag;
    int status;
    while((flag = wait(&status)) > 0){
        if(WIFEXITED(status))
            printf("Soy el padre con PID %ld y el hijo %d ha finalizado correctamente con status=%d\n", (long int) getpid(), flag, WEXITSTATUS(status));
        if(WIFSIGNALED(status))
            printf("Soy el padre con PID %ld y el hijo %d ha finalizado con la señal %d\n", (long int) getpid(), flag, WTERMSIG(status));
    }
    if(errno == ECHILD && flag == -1)
        printf("Soy el padre con PID %ld, no hay más hijos a los que esperar. Valor de errno = %d definido como %s\n", (long int) getpid(), errno, strerror(errno));
    else{
        fprintf(stderr, "Error en la espera o en la invocacion de wait\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}