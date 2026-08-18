#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//gcc -lpthread

int var = 0;
//pthread_mutex_t mutex_bin

void *funcion(){
    for(int i=0; i<100000; i++){
        /*if(pthread_mutex_lock(&mutex_bin) != 0){
            printf("Error en el bloqueo del mutex\n");
            exit(EXIT_FAILURE);
        }*/
        var++;
        /*if(pthread_mutex_unlock(&mutex_bin) != 0){
            printf("Error en el desbloqueo del mutex\n");
            exit(EXIT_FAILURE);
        }*/
    }
    printf("Soy el hilo %lu\n", pthread_self());
    pthread_exit((void*) NULL);
}

int main(int argc, char **argv){
    /*if(argc != 2){
        printf("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }
    */
   int n=2;
    pthread_t thread[n];

    //Inicialización del semáforo
    /*if(pthread_mutex_init(&mutex_bin, NULL) != 0){
        printf("Error en la inicializacion del mutex_bin\n");
        exit(EXIT_FAILURE);
    }*/

    for(int i=0; i<n; i++){
        if(pthread_create(&thread[i], NULL, (void *) &funcion, (void *) NULL) != 0){
            perror("Error en la creacion del hilo\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<n; i++){
        if(pthread_join(thread[i], (void **) NULL) != 0){
            perror("Error en la espera del hilo\n");
            exit(EXIT_FAILURE);
        }
    }

    //FIN del programa
    /*ifpthread_mutex_destroy(&mutex_bin) != 0){
        printf("Error en la destruccion del mutex_bin\n");
        exit(EXIT_FAILURE);
    }*/

    printf("var = %d\n", var);
    exit(EXIT_SUCCESS);
}