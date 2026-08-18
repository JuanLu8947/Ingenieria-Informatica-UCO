//Librerias estandar de C
#include <stdio.h>
#include <stdlib.h>

//Para exit(EXIT_FAILURE)
#include <string.h>

//Para hilos y mutex´
#include <pthread.h>

//Para rand
#include <time.h>

//Para semaforos generales
#include <semaphore.h>

/*int cuentaLect = 0, dato = 0;
sem_t sem_escritor, sem_lector;*/

struct param{
    sem_t *sem_escritor, *sem_lector;
    int *cuentaLect, *dato;
};

void * lector(void *arg){
    struct param *p = (struct param *) arg;
    int n = 5;
    for(int i=0; i<n; i++){
        //if(sem_wait(&sem_lector)){ //protegemos acceso a cuentaLect
        if(sem_wait(p->sem_lector)){
            fprintf(stderr, "Error en el sem_wait de sem_lector\n");
            exit(EXIT_FAILURE);
        }
        (*p->cuentaLect)++;
        if(*p->cuentaLect == 1)
            //if(sem_wait(&sem_escritor)){ //el primer lector bloquea a escritor
            if(sem_wait(p->sem_escritor)){
                fprintf(stderr, "Error en el sem_wait de sem_escritor\n");
                exit(EXIT_FAILURE);
            }
        //if(sem_post(&sem_lector)){
        if(sem_post(p->sem_lector)){
            fprintf(stderr, "Error en el sem_post de sem_lector\n");
            exit(EXIT_FAILURE);
        }

        printf("Lector %lu, valor leido = %d\n", pthread_self(), *p->dato); 

        //if(sem_wait(&sem_lector)){
        if(sem_wait(p->sem_lector)){
            fprintf(stderr, "Error en el sem_wait de sem_lector\n");
            exit(EXIT_FAILURE);
        }
        (*p->cuentaLect)--;
        if(*p->cuentaLect == 0)
            //if(sem_post(&sem_escritor)){
            if(sem_post(p->sem_escritor)){
                fprintf(stderr, "Error en el sem_post de sem_escritor\n");
                exit(EXIT_FAILURE);
            }
        //if(sem_post(&sem_lector)){
        if(sem_post(p->sem_lector)){
            fprintf(stderr, "Error en el sem_post de sem_lector\n");
            exit(EXIT_FAILURE);
        }
    }
    //
    pthread_exit((void *) NULL);
}
void * escritor(void *arg){ 
    struct param *p = (struct param *) arg;
    int n = 5;
    for(int i=0; i<n; i++){
        //if(sem_wait(&sem_escritor)){ //solo un escritor al mismo tiempo
        if(sem_wait(p->sem_escritor)){
            fprintf(stderr, "Error en el sem_wait de sem_escritor\n");
            exit(EXIT_FAILURE);
        }

        (*p->dato) += 1;
        printf("Escritor %lu, incrementando a valor = %d\n", pthread_self(), *p->dato);

        //if(sem_post(&sem_escritor)){
        if(sem_post(p->sem_escritor)){
            fprintf(stderr, "Error en el sem_post de sem_escritor\n");
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit((void *) NULL);
}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "arg error\n");
        exit(EXIT_FAILURE);
    }

    //
    int n = atoi(argv[1]), count = 0, data = 0;
    pthread_t thread_lector[n], thread_escritor[n];
    struct param p[n];

    sem_t sem_escritor_, sem_lector_;

    //
    //if(sem_init(&sem_escritor, 0, 1)){
    if(sem_init(&sem_escritor_, 0, 1)){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_lector, 0, n)){
    if(sem_init(&sem_lector_, 0, n)){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }

    //
    for(int i=0; i<n; i++){
        p[i].sem_escritor = &sem_escritor_;
        p[i].sem_lector = &sem_lector_;
        p[i].cuentaLect = &count;
        p[i].dato = &data;
        if(pthread_create(&thread_lector[i], NULL, (void *) &lector, (void *) &p[i])){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<n; i++){
        p[i].sem_escritor = &sem_escritor_;
        p[i].sem_lector = &sem_lector_;
        p[i].dato = &data;
        if(pthread_create(&thread_escritor[i], NULL, (void *) &escritor, (void *) &p[i])){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    }

    //
    for(int i=0; i<n; i++)
        if(pthread_join(thread_lector[i], (void **) NULL)){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<n; i++)
        if(pthread_join(thread_escritor[i], (void **) NULL)){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }

    //
    //if(sem_destroy(&sem_lector)){
    if(sem_destroy(&sem_lector_)){
        fprintf(stderr, "sem_destroy error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_destroy(&sem_escritor)){
    if(sem_destroy(&sem_escritor_)){
        fprintf(stderr, "sem_destroy error\n");
        exit(EXIT_FAILURE);
    }

    //
    exit(EXIT_SUCCESS);
}