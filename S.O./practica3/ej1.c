#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex; 
int *buffer=NULL;
void * compra(void * arg){
    int *M = (int *) arg, n=10;
    int modelo=rand()%*M+1, cantidad=rand()%n+1;
    printf("<-- Cliente %lu, compro %d unidades de la camiseta %d\n", pthread_self(), cantidad, modelo);
    if(pthread_mutex_lock(&mutex) != 0){
        printf("Error en el bloqueo de mutex\n");
        exit(EXIT_FAILURE);
    }
    buffer[modelo] -= cantidad;
    if(pthread_mutex_unlock(&mutex) != 0){
        printf("Error en el desbloqueo de mutex\n");
        exit(EXIT_FAILURE);
    }
    pthread_exit((void*) NULL);
}
void * suministro(void * arg){
    int *M = (int *) arg, n=10;
    int modelo=rand()%*M+1, cantidad=rand()%n+1;
    printf("--> Proveedor %lu, suministro %d unidades de la camiseta %d\n", pthread_self(), cantidad, modelo);
    if(pthread_mutex_lock(&mutex) != 0){
        printf("Error en el bloqueo de mutex\n");
        exit(EXIT_FAILURE);
    }
    buffer[modelo] += cantidad;
    if(pthread_mutex_unlock(&mutex) != 0){
        printf("Error en el desbloqueo de mutex\n");
        exit(EXIT_FAILURE);
    }
    pthread_exit((void*) NULL);
}

int main(int argc, char **argv){
    if(argc != 3){
        printf("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }
    int N=atoi(argv[1]), M=atoi(argv[2]);
    pthread_t hebra_client[N], hebra_vendedor[M];
    srand(time(NULL)); 
    //i0
    if(pthread_mutex_init(&mutex, NULL) != 0){
        printf("Error en la inicializacion del mutex\n");
        exit(EXIT_FAILURE);
    }
    if((buffer = malloc(sizeof(int))) == NULL){
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }
    printf("Stock disponible de cada camiseta antes de abrir la tienda: \n");           //Mostramos con el bucle por pantalla el numero de camisetas de cada tipo antes de aplicar las ventas y los suministros
    for(int i=0; i<M; i++){
        buffer[i] = rand()%100;
        printf("Camisetas modelo %d: %d\n", i+1, buffer[i]);
    }
    for(int i=0; i<N; i++){
        if(pthread_create(&hebra_client[i], NULL, (void *) &compra, (void *) &M) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<M; i++){
        if(pthread_create(&hebra_vendedor[i], NULL, (void *) &suministro, (void *) &M) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<N; i++){
        if(pthread_join(hebra_client[i], (void **) NULL) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<M; i++){
        if(pthread_join(hebra_vendedor[i], (void **) NULL) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Stock disponible de cada camiseta al cerrar la tienda: \n");
    for(int i=0; i<M; i++){
        printf("Camisetas modelo %d: %d\n", i+1, buffer[i]);
    }

    //fin
    if(pthread_mutex_destroy(&mutex) != 0){
        printf("Error en la destruccion del mutex\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}