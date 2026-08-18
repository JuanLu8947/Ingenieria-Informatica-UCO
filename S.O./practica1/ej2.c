#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "arg error\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    int n = atoi(argv[1]), status;
    for(int i=0; i<n; i++){
        pid = fork();
        switch(pid){
            case -1:
                fprintf(stderr, "fork error\n");
                exit(EXIT_FAILURE);

            case 0:
                printf("Soy el hijo %d con PID %ld y mi padre es %ld\n\n", i+1, (long int)getpid(), (long int)getppid());
                break;

            default:
                printf("Soy el padre con PID %ld y mi padre es es %ld\n\n", (long int)getpid(), (long int)getppid());
                while((pid = wait(&status)) > 0){ //Para la espera se puede usar cualquiera de la demo while-wait-waitpid.c
                    if(WIFEXITED(status))
                        printf("Soy el padre con PID %ld y el hijo con pid %d ha finalizado con status %d\n", (long int)getpid(), pid, WEXITSTATUS(status));
                    if(WIFSIGNALED(status))
                        printf("Soy el padre con PID %ld y el hijo con pid %d ha finalizado con la señal %d\n", (long int)getpid(), pid, WTERMSIG(status));
                }
                if(errno == ECHILD && pid == -1)
                    printf("Soy el padre con PID %ld, no hay más hijos a los que esperar. Valor de errno = %d definido como %s\n", (long int) getpid(), errno, strerror(errno));
                else{
                    fprintf(stderr, "Error en la espera o en la invocacion de wait\n");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            
        }
    }
    
    exit(EXIT_SUCCESS);
}