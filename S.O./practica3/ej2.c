#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

/*pthread_mutex_t mutex_par, mutex_impar;
int par=0, impar=0;

void * funcion(void * dato){
    int *indice = (int *) dato;
    int *suma = (int *) malloc(sizeof(int*)), v_num[5];
    if(*indice%2 == 0){
        if(pthread_mutex_lock(&mutex_par) != 0){
            printf("Error en el bloqueo de mutex_par\n");
            exit(EXIT_FAILURE);
        }
        for(int j=0; j<5; j++){
            v_num[j]=rand()%10;
            *suma+= v_num[j];
        }

        par += *suma;
        if(pthread_mutex_unlock(&mutex_par) != 0){
            printf("Error en el desbloqueo de mutex_par\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        if(pthread_mutex_lock(&mutex_impar) != 0){
            printf("Error en el bloqueo de mutex_impar\n");
            exit(EXIT_FAILURE);
        }
        for(int j=0; j<5; j++){
            v_num[j]=rand()%10;
            *suma+= v_num[j];
        }

        impar += *suma;
        if(pthread_mutex_unlock(&mutex_impar) != 0){
            printf("Error en el desbloqueo de mutex_impar\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit((void *) suma);
}*/

struct param{
    int *par, *impar;
    pthread_mutex_t *mutex_par, *mutex_impar;
    int posicion;
};

/*pthread_mutex_t mutex_par, mutex_impar;
int par=0, impar=0;
*/

void *funcionHilo(void *parametro){
    struct param *p = (struct param *)parametro;
    /*int * indice = (int *)parametro;
    int *suma = (int *)malloc(sizeof(int*));
    *suma = 0;*/
    int suma = 0;
    for (int i = 0; i < 5; i++){
        int num = rand() % 10;
        suma += num;
        //if(*indice % 2 != 0){
        if(p->posicion % 2 != 0){
            //if(pthread_mutex_lock(&mutex_impar) != 0){
            if(pthread_mutex_lock(p->mutex_impar) != 0){
                fprintf(stderr, "Error en el lock de semimpar\n");
                exit(EXIT_FAILURE);
            }
            //(*suma) += num;
            (*p->impar) += num;
            //if(pthread_mutex_unlock(&mutex_impar) != 0){
            if(pthread_mutex_unlock(p->mutex_impar) != 0){
                fprintf(stderr, "Error en el unlock de semimpar\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            //if(pthread_mutex_lock(&mutex_par) != 0){
            if(pthread_mutex_lock(p->mutex_par) != 0){
                fprintf(stderr, "Error en el lock de sempar\n");
                exit(EXIT_FAILURE);
            }
            //(*suma) += num;
            (*p->par) += num;
            //if(pthread_mutex_unlock(&mutex_par) != 0){
            if(pthread_mutex_unlock(p->mutex_par) != 0){
                fprintf(stderr, "Error en el unlock de sempar\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    //printf("Hilo... de posicion %d ha generado un total de %d valores\n", *indice, *suma);
    printf("Hilo... de posicion %d ha generado un total de %d valores\n", p->posicion, suma);
    //pthread_exit((void *) suma);
    pthread_exit((void *) NULL);
}

/*int main(int argc, char **argv){
    if(argc != 2){
        printf("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]), suma_par=0, suma_impar=0;
    pthread_t thread[n];
    srand(time(NULL));

    //i0
    if(pthread_mutex_init(&mutex_par, NULL) != 0){
        printf("Error en la inicializacion del mutex_sum\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_init(&mutex_impar, NULL) != 0){
        printf("Error en la inicializacion del mutex_resta\n");
        exit(EXIT_FAILURE);
    }
    int indice[n];
    for(int i=0; i<n; i++){
        indice[i]=i+1;
        if(pthread_create(&thread[i], NULL, (void *) &funcion, (void *) &indice[i]) != 0){
            printf("Error en la creación\n");
            exit(EXIT_FAILURE);
        }
    }

    int *dato;
    for(int i=0; i<n; i++){
        if(pthread_join(thread[i], (void **) &dato) != 0){
            printf("Error en la recogida\n");
            exit(EXIT_FAILURE);
        }        
        indice[i]=i+1;
        if(indice[i]%2 == 0)
            suma_par += *dato;
        else
            suma_impar += *dato;
        printf("Main: La hebra de orden de creacion %d devolvió el valor de suma: %d\n", i+1, *dato);
    }
    printf("\nMain: Valor de la variable compartida impar: %d\n", impar);
    printf("Main: Suma de los valores devueltos por las hebras de creación impares: %d\n", suma_impar);
    
    printf("\nMain: Valor de la variable compartida par: %d\n", par);
    printf("Main: Suma de los valores devueltos por las hebras de creación pares: %d\n", suma_par);

    //fin
    if(pthread_mutex_destroy(&mutex_par) != 0){
        printf("Error en la destruccion del mutex_par\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_destroy(&mutex_impar) != 0){
        printf("Error en la destruccion del mutex_impar\n");
        exit(EXIT_FAILURE);
    }
    free(dato);
    exit(EXIT_SUCCESS);
}*/

int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "Error en la linea de argumentos. \n");
        exit(EXIT_FAILURE);
    }

    // variables compartidas
    int par = 0, impar = 0;
    pthread_mutex_t mutex_par, mutex_impar;

    int N = atoi(argv[1]);
    pthread_t hilos[N];
    struct param p[N];
    srand(time(NULL));
    //int indice[N];

    printf("Main()... La variable par esta inicializada a %d\n", par);
    printf("Main()... La variable impar esta inicializada a %d\n", impar);

    // inicio semaforo
    if(pthread_mutex_init(&mutex_par, NULL) != 0){
        fprintf(stderr, "Error en la inicializacion del mutex_par.\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_init(&mutex_impar, NULL) != 0){
        fprintf(stderr, "Error en la inicializacion del mutex_impar.\n");
        exit(EXIT_FAILURE);
    }

    //CREATE
    for(int i = 0; i < N; i++){
        p[i].par = &par;
        p[i].impar = &impar;
        p[i].mutex_par = &mutex_par;
        p[i].mutex_impar = &mutex_impar;
        p[i].posicion = i + 1;
        //indice[i] = i + 1;
        //if(pthread_create(&hilos[i], NULL, (void *) &funcion, (void *) &indice[i]) != 0){
        if(pthread_create(&hilos[i], NULL, (void *) &funcionHilo, (void *)&p[i]) != 0){
            fprintf(stderr, "Error en pthread_create().\n");
            exit(EXIT_FAILURE);
        }
    }

    // JOIN
    for(int i = 0; i < N; i++){
        if(pthread_join(hilos[i], (void **) NULL) != 0){
            fprintf(stderr, "Error en pthread_join().\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Main()... La variable par al final contiene a %d\n", par);
    printf("Main()... La variable impar al final contiene a %d\n", impar);

    // destruyo semaforo
    if(pthread_mutex_destroy(&mutex_par) != 0){
        fprintf(stderr, "Error en la destruccion del mutex_par.\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_destroy(&mutex_impar) != 0){
        fprintf(stderr, "Error en la destruccion del mutex_impar.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}