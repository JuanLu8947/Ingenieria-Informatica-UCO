//v.1: está realizado como se explicó el curso 23/24

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>

sem_t sem_prod, sem_consum; //declaracion sem general
sem_t sem; //SC

#define TAM_BUFFER 5
#define elem 10

int bufin=0;
int buffer[TAM_BUFFER];

int buffout=0;
int datoLeido=0;

void * productor(void *arg){
    for (int i=0; i<elem; i++){
        if(sem_wait(&sem_prod)!=0){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_wait(&sem)){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        //añadir();
        int aleatorioGenerado = rand()%10;
        buffer[bufin]=aleatorioGenerado;
        printf("Produciendo un %d en la posición %d\n", buffer[bufin], bufin);
        bufin=(bufin+1)%TAM_BUFFER; //recorre las pos de forma ciruclar
        //
        if(sem_post(&sem)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_post(&sem_consum)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit((void *) NULL);
}

void * consumidor(void *arg){
    for(int i=0; i<elem; i++){
        if(sem_wait(&sem_consum)){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_wait(&sem)){
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        //extraer();
        datoLeido=buffer[buffout];
        printf("Consumiendo un %d en la posición %d\n", datoLeido, buffout);
        buffout=(buffout+1)%TAM_BUFFER;
        //
        if(sem_post(&sem)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
        if(sem_post(&sem_prod)){
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit((void *) NULL);
}

int main(int argc, char *argv[]){
    /*if(argc < 2){
        printf("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }
    int n_prod = atoi(argv[1]), n_consum = atoi(argv[1]);*/
    pthread_t thread_prod/*[n_prod]*/, thread_consum/*[n_consum]*/;
    srand(time(NULL));
    //i0
    if(sem_init(&sem_prod, 0, TAM_BUFFER)){
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&sem_consum, 0, 0)){
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&sem, 0, 1)){
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }

    //for(int i=0; i<n_prod; i++)
        if(pthread_create(&thread_prod/*[i]*/, NULL, (void *) &productor, (void *) NULL) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }
    //for(int i=0; i<n_consum; i++)
        if(pthread_create(&thread_consum/*[i]*/, NULL, (void *) &consumidor, (void *) NULL) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }

    //for(int i=0; i<n_prod; i++)
        if(pthread_join(thread_prod/*[i]*/, (void **) NULL) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }    
    //for(int i=0; i<n_consum; i++)
        if(pthread_join(thread_consum/*[i]*/, (void **) NULL) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }  
    
    //fin
    if(sem_destroy(&sem_prod) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }  
    if(sem_destroy(&sem_consum) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }  
    if(sem_destroy(&sem) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }  
    exit(EXIT_SUCCESS); 
}