//Librerias estandar de C
#include <stdlib.h>
#include <stdio.h>

//Para poder usar pid_t
#include <sys/types.h>

//Para poder usar fork()
#include <unistd.h>

//Para la espera de los hijos
#include <sys/wait.h>

//Para usar exit(EXIT_SUCCESS)
#include <string.h>

//Para errno == ECHILD
#include <errno.h>

//Para señales
#include <signal.h>

//Si nos pidiesen generar números aleatorios
#include <time.h>

//Si quisiesemos usar booleans values
//#include <stdbool.h> //no se usa

//Si quisieramos usar las funciones matemáticas
//#include <math.h> //no se usa

//exec, sus IF son == -1

void funcionManejadoraHijo(int s){
	printf("Soy el hijo %ld he recibido la señal %d y la ignoro\n", (long int) getpid(), s);
	kill(getppid(), SIGUSR1); //envía señal para avisar al padre
}
void funcionManejadoraPadre(int s){
}


int main(int argc, char **argv){
	if(argc < 2){ 
		fprintf(stderr, "arg error\n");
		exit(EXIT_FAILURE);
	}
	pid_t pid1;
	int n = 1;
	
	for(int i=0; i<=n; i++){
		pid1 = fork();
		switch(pid1){
			case -1: //fork error
				fprintf(stderr, "fork error\n");
				exit(EXIT_SUCCESS);
			case 0: //hijo
				printf("Soy el hijo %d con PID %ld y mi padre es %ld\n", i, (long int) getpid(), (long int) getppid());
				if(i==0){ //h0
					printf("Soy el hijo que abre cosas\n");
					if(execvp(argv[1], &(argv)[1]) == -1){
						fprintf(stderr, "execvp error\n");
						exit(EXIT_FAILURE);
					}
					/*
					if(execlp(argv[1], argv[1], NULL){
						fprintf(stderr, "execlp error\n");
						exit(EXIT_FAILURE);
					}
					if(execlp("ls", "ls", "-l", NULL){
						fprintf(stderr, "execlp error\n");
						exit(EXIT_FAILURE);
					}
					*/
				}
				if(i==1){ //h1
					signal(SIGUSR1, &funcionManejadoraPadre);
					printf("Soy el hijo que que crea un hijo y me envío señales con él\n");
					pid_t pid2;
					int m = 2;
					for(int j=0; j<m; j++){
						pid2 = fork();
						switch(pid2){
							case -1: //fork error
								fprintf(stderr, "fork error\n");
								exit(EXIT_FAILURE);
							case 0: //h1.1, hijo de h1
								signal(SIGUSR1, &funcionManejadoraHijo);
								printf("Soy el hijo que espera y envía señales a su padre\n");
								kill(getppid(), SIGUSR1);
								while(1)
									pause();
							default: //h1 que ahora es padre
								pause();
								for(int k=0; k<m; k++){
									kill(pid2, SIGUSR1);
									pause();
								}
								kill(pid2, SIGKILL);
						}
					}
				}
			default: //padre
				printf("Soy el proceso padre %ld y la terminal es %ld\n", (long int) getpid(), (long int) getppid());
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
		fprintf(stderr, "Error en la invocación de waitpid\n");
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}

