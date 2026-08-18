#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void funcionManejadora(){
    printf("Padre: He recibido la señal SISGUR1(%d) de mi padre y la ignoro\n", SIGUSR1);
}

int main(int argc, char **argv){
    pid_t pid;
    
    pid=fork();
    switch(pid){
        case -1:
            printf("fork error");
            exit(EXIT_FAILURE);
        case 0:
            //signal(SIGUSR1, funcionManejadora);
            printf("HIJO: no hago nada\n");
            exit(EXIT_SUCCESS);
        default:
            signal(SIGUSR1, funcionManejadora);
            printf("Soy el padre %ld y la terminal es %ld\n", (long int)getpid(), (long int)getppid());
            while(1){
                pause();
            }
    }
	pid_t flag;
	int status;
	while((flag = wait(&status)) > 0){ //Para la espera se puede usar cualquiera de la demo while-wait-waitpid.c
		if(WIFEXITED(status))
			printf("Proceso padre %ld, el hijo %d ha finalizado correctamente con status=%d\n", (long int) getpid(), flag, WEXITSTATUS(status));
		if(WIFSIGNALED(status))
			printf("Proceso padre %ld, el hijo %d ha finalizado con la señal %d\n", (long int) getpid(), flag, WTERMSIG(status));
	}
	if(errno == ECHILD && flag == -1)
	    printf("Soy el padre con PID %ld, no hay más hijos a los que esperar. Valor de errno = %d definido como %s\n", (long int) getpid(), errno, strerror(errno));
	else{
        fprintf(stderr, "Error en la espera o en la invocacion de wait\n");
		exit(EXIT_SUCCESS);
	}
    exit(EXIT_SUCCESS);
}