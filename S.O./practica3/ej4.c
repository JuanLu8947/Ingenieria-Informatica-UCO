#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t semA, semB; //declaracion sem general

void escribirA(){
    for (int i=0; i<5; i++){
        if(sem_wait(&semB)){ //comprobar si B está bloqueado
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        printf("A");
        fflush(NULL);
        if(sem_post(&semA) != 0){   //como se ha terminado A, se indica
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}
void escribirB(){
    for (int i=0; i<5; i++){
        if(sem_wait(&semA)){ //comprobar si A está bloqueado
            printf("Error en sem_wait()\n");
            exit(EXIT_FAILURE);
        }
        printf("B");
        fflush(NULL);
        if(sem_post(&semB)){ //como se ha terminado B, se indica
            printf("Error en sem_post()\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t thread_A, thread_B;
    //i0
    if(sem_init(&semA, 0, 1)){ //variación del pthread_mutex_init
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&semB, 0, 0)){
        printf("Error en sem_init()\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&thread_A, NULL, (void *) &escribirA, (void *) NULL) != 0){
        printf("Error en la creación\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&thread_B, NULL, (void *) &escribirB, (void *) NULL) != 0){
        printf("Error en la creación\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_join(thread_A, (void **) NULL) != 0){
        printf("Error en la recogida\n");
        exit(EXIT_FAILURE);
    }        
    if(pthread_join(thread_B, (void **) NULL) != 0){
        printf("Error en la recogida\n");
        exit(EXIT_FAILURE);
    }
    //fin
    if(sem_destroy(&semA) != 0){ //como pthread_mutex_destroy
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }
    if(sem_destroy(&semB) != 0){
        printf("Error en sem_destroy()\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");
    exit(EXIT_SUCCESS);      
}