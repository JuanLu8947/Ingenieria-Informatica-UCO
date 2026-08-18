#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void funcionManejadora(){
    printf("HIJO: He recibido la señal SISGUR1(%d) de mi padre y la ignoro\n", SIGUSR1);
}

int main(){
    pid_t pid;
    pid = fork();
    switch(pid){
        case -1:
            fprintf(stderr, "fork error\n");
            exit(EXIT_FAILURE);
        case 0:
            signal(SIGUSR1, funcionManejadora);
            printf("Soy el hijo %ld y mi padre es %ld\n", (long int)getpid(), (long int)getppid());
            while(1){
                pause();
            }
            exit(EXIT_SUCCESS);
        default:
            printf("Soy el padre %ld\n", (long int)getpid());
            for(int i=0; i<4; i++){
                //kill(getpid(), SIGUSR1);
                sleep(1);
                kill(pid, SIGUSR1);
            }
            sleep(1);
            kill(pid, SIGKILL);
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