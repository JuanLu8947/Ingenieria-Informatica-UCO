#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h> //sem_t, sem_init, sem_wait, sem_post, sem_destroy
#include <sys/ipc.h> // ftok
#include <sys/shm.h> // shmget, shmat, shmdt, shmctl
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h> //ECHILD, errno, 
#include <pthread.h> //mutex_t, pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy

int main(int argc, char **argv){
    if(argc < 3){
        printf("Error en la linea de arg. usage: nºhijos nºincrementos\n");
        exit(EXIT_FAILURE);
    }

    //Creacion de clave
    key_t clave = ftok (".", 33); //key dinamica
    if (clave == -1){
       	perror("ftok error");
		printf("Valor de errno=%d, definido como %s\n", errno, strerror(errno));  
		exit(EXIT_FAILURE);
    }
    //Creacion de memoria compartida usando la clave
    int id_Memoria = shmget (clave, sizeof(int)*10, IPC_CREAT | SHM_R | SHM_W);
	if (id_Memoria == -1){
		printf("Main() de demo1... No consigo ID para la memoria compartida.\n");
		printf("Valor de errno=%d, definido como %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
    //Enlazamos la memoria compartida
    int * contador = NULL;
    contador = (int *)shmat(id_Memoria, NULL, 0); //se compr q devuelv el puntero
	if (contador == NULL){
		printf("Main() de demo1... No consigo enlace a la memoria compartida.\n");
		printf("Valor de errno=%d, definido como %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

    sem_t *sem = (sem_t *)shmat(shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0666), NULL, 0);
    if (sem == (sem_t *)-1) {
        perror("shmat");
        exit(EXIT_SUCCESS);
    }
    if(sem_init(sem, 1, 1) != 0){
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }

    //ejercicio
    pid_t pid;
    int n = atoi(argv[1]), N = atoi(argv[2]), status;
    *contador = 0;
    for(int i=0; i<n; i++){
        pid = fork();
        switch(pid){
            case -1:
                printf("Error en el fork\n");
                exit(EXIT_FAILURE);
            case 0://Hijo
                printf("Hijo %d con pid %lu y mi padre es %lu\n", i, (long int) getpid(), (long int) getppid());
                for(int j=0; j<N; j++){
                    if(sem_wait(sem) != 0){
                        printf("Error en sem_wait()\n");
                        exit(EXIT_FAILURE);
                    }
                    (*contador)++;
                    if(sem_post(sem) != 0){
                        printf("Error en sem_post()\n");
                        exit(EXIT_FAILURE);
                    }
                }
                exit(EXIT_SUCCESS);
            default://Padre
                printf("Padre %d con pid %lu y mi padre es %lu\n", i, (long int) getpid(), (long int) getppid());
        }
    }
    //Espera de los hijos
    while((pid = waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0){
        if(WIFEXITED(status)){
            printf("Proceso hijo con pid %lu finalizado con status %d\n", (long int) pid, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("Proceso hijo con pid %lu finalizado con la señal %d\n", (long int) pid, WTERMSIG(status));
        }
        else if(WIFSTOPPED(status)){
            printf("Proceso hijo con pid %lu parado con la señal %d\n", (long int) pid, WSTOPSIG(status));
        }
        else if(WIFCONTINUED(status)){
            printf("Proceso hijo con pid %lu reanudado\n", (long int) pid);
        }
    }
    if(errno == ECHILD && pid == (pid_t)-1)
        printf("No hay mas hijos que esperar\n");
    else
        printf("Error en la invocación de waitpid\n");

    //Se marca la memoria compartida para su eliminacion
    int value = shmctl (id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
	if (value == -1){
		printf("Error en shmctl...\n");
		printf("Valor de errno=%d, definido como %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
    printf("Valor final del contador: %d\n", *contador);
    //Se desvincula la memoria compartida
    value = shmdt ((char *) contador);
	if (value == -1){
		printf("Error en shmdt...\n");
		printf("Valor de errno=%d, definido como %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
    exit(EXIT_SUCCESS);
}