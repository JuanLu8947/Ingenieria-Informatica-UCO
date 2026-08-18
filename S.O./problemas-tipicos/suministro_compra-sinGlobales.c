//Librerías estándar de C
#include <stdio.h>
#include <stdlib.h>

//Para hilos y mutex
#include <pthread.h>

//semáforos generales
//#include <semaphore.h> //aquí no hay

//Para exit(EXIT_SUCCESS)
#include <string.h>

//Para el uso de rand()
#include <time.h>

//Para uso de booleans values
//#include <stdbool.h> //no se usa

//Libreria matemática
//#include <math.h> //no se usa

//Para malloc (por si acaso)
#include <malloc.h>

//pthread_create, pthread_join, pthread_mutex_lock, pthread_mutex_unlock sus IF son != 0

/*pthread_mutex_t mtx_compra_suministro;
int *buffer_compra_suministro = NULL;*/

struct param{
    pthread_mutex_t *mtx_compra_suministro;
    int *buffer_compra_suministro, M;
};

void * Compra(void * arg){
    //int *M = (int *) arg, n=10;
    struct param *p = (struct param *) arg;
    int n=10;
    int modelo=rand()%(p->M+1), cantidad=rand()%(n+1);
    printf("<-- Cliente %lu, compro %d unidades de la camiseta %d\n", pthread_self(), cantidad, modelo);
	//if(pthread_mutex_lock(&mtx_compra_suministro)){
    if(pthread_mutex_lock(p->mtx_compra_suministro)){
		fprintf(stderr, "pthread_mutex_lock error\n");
		exit(EXIT_FAILURE);
	}

    //buffer_compra_suministro[modelo] -= cantidad;
    p->buffer_compra_suministro[modelo] -= cantidad;

	//if(pthread_mutex_unlock(&mtx_compra_suministro)){
    if(pthread_mutex_unlock(p->mtx_compra_suministro)){
		fprintf(stderr, "pthread_mutex_unlock error\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void *) NULL);
}

void * Suministro(void * arg){
    //int *M = (int *) arg, n=10;
    struct param *p = (struct param *) arg;
    int n=10;
    int modelo=rand()%(p->M+1), cantidad=rand()%(n+1);
	printf("--> Proveedor %lu, suministro %d unidades de la camiseta %d\n", pthread_self(), cantidad, modelo);
    //if(pthread_mutex_lock(&mtx_compra_suministro)){
    if(pthread_mutex_lock(p->mtx_compra_suministro)){
		fprintf(stderr, "pthread_mutex_lock error\n");
		exit(EXIT_FAILURE);
	}

    //buffer_compra_suministro[modelo] += cantidad;
    p->buffer_compra_suministro[modelo] += cantidad;

	//if(pthread_mutex_unlock(&mtx_compra_suministro)){
    if(pthread_mutex_unlock(p->mtx_compra_suministro)){
		fprintf(stderr, "pthread_mutex_unlock error\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void *) NULL);
}

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "Usage: N(cantidad) M(n_modelos)\n");
        exit(EXIT_FAILURE);
    }
    
    //M = n_modelos, N = cantidad
    int N = atoi(argv[1]), M = atoi(argv[2]);
    pthread_t thread_compra[N], thread_suministro[M];
    srand(time(NULL));

    pthread_mutex_t mtx_compra_suministro_;

    //if(pthread_mutex_init(&mtx_compra_suministro, NULL)){
    if(pthread_mutex_init(&mtx_compra_suministro_, NULL)){
        fprintf(stderr, "pthread_mutex_init error\n");
        exit(EXIT_FAILURE);
    }
    struct param p;

    if((p.buffer_compra_suministro = malloc(M * sizeof(int))) == NULL){
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }

    printf("Stock disponible de cada camiseta antes de abrir la tienda: \n");   
    for(int i=0; i<M; i++){
        /*buffer_compra_suministro[i] = rand()%100;
        printf("Camisetas modelo %d: %d\n", i+1, buffer_compra_suministro[i]);*/
        p.buffer_compra_suministro[i] = rand()%100;
        printf("Camisetas modelo %d: %d\n", i+1, p.buffer_compra_suministro[i]);
    }
    printf("\n");

    p.mtx_compra_suministro = &mtx_compra_suministro_;
    p.M = M;

    //como ya hay stock, empiezan los compradores
    for(int i=0; i<N; i++)
        if(pthread_create(&thread_compra[i], NULL, (void *) &Compra, (void *) &p)){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<M; i++)
        if(pthread_create(&thread_suministro[i], NULL, (void *) &Suministro, (void *) &p)){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
        
	//suministro-compra
	for(int i=0; i<N; i++)
		if(pthread_join(thread_compra[i], (void **) NULL)){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
	for(int i=0; i<M; i++)
		if(pthread_join(thread_suministro[i], (void **) NULL)){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}

	printf("\nStock disponible de cada camiseta al cerrar la tienda: \n");
	for(int i=0; i<M; i++)
		//printf("Camisetas modelo %d: %d\n", i+1, buffer_compra_suministro[i]);
        printf("Camisetas modelo %d: %d\n", i+1, p.buffer_compra_suministro[i]);

    //if(pthread_mutex_destroy(&mtx_compra_suministro)){
    if(pthread_mutex_destroy(&mtx_compra_suministro_)){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}