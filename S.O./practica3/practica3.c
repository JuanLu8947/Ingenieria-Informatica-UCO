//Librerías estándar de C
#include <stdio.h>
#include <stdlib.h>

//Para hilos y mutex
#include <pthread.h>

//semáforos generales
#include <semaphore.h>

//Para exit(EXIT_SUCCESS)
#include <string.h>

//Para el uso de rand()
#include <time.h>

//Para uso de booleans values
#include <stdbool.h>

//Libreria matemática
#include <math.h>

//Para malloc
#include <malloc.h>

//pthread_create, pthread_join                  }
//pthread_mutex_lock, pthread_mutex_unlock      }
//pthread_mutex_init, pthread_mutex_destroy      } Sus IF son != 0
//sem_init, sem_destroy                         }
//sem_wait, sem_post                            }

//par-impar
struct param4{
    int *par, *impar;
    pthread_mutex_t *mutex_par, *mutex_impar;
    int indice;
};

/*pthread_mutex_t mutex_par, mutex_impar;
int par=0, impar=0;
*/

void * f_par_impar(void *parametro){
    struct param4 *p = (struct param4 *)parametro;
    /*int * indice = (int *)parametro;
    int *suma = (int *)malloc(sizeof(int*));
    *suma = 0;*/
    int suma = 0;
    for (int i = 0; i < 5; i++){
        int num = rand() % 10;
        //suma += num;
        //if(*indice % 2 != 0){
        if(p->indice % 2 != 0){
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

//lector-escritor
struct param3{
    sem_t *sem_escritor, *sem_lector;
    int *cuentaLect, *dato;
};

//compra-suministro
struct param2{
    pthread_mutex_t *mtx_compra_suministro;
    int *buffer_compra_suministro, M;
};

void * lector(void *arg){
    struct param3 *p = (struct param3 *) arg;
    int n = 5;
    for(int i=0; i<n; i++){
        //if(sem_wait(&sem_lector)){ //protegemos acceso a cuentaLect
        if(sem_wait(p->sem_lector) != 0){
            fprintf(stderr, "Error en el sem_wait de sem_lector\n");
            exit(EXIT_FAILURE);
        }
        (*p->cuentaLect)++;
        if(*p->cuentaLect == 1)
            //if(sem_wait(&sem_escritor)){ //el primer lector bloquea a escritor
            if(sem_wait(p->sem_escritor) != 0){
                fprintf(stderr, "Error en el sem_wait de sem_escritor\n");
                exit(EXIT_FAILURE);
            }
        //if(sem_post(&sem_lector)){
        if(sem_post(p->sem_lector) != 0){
            fprintf(stderr, "Error en el sem_post de sem_lector\n");
            exit(EXIT_FAILURE);
        }

        printf("Lector %lu, valor leido = %d\n", pthread_self(), *p->dato); 

        //if(sem_wait(&sem_lector)){
        if(sem_wait(p->sem_lector) != 0){
            fprintf(stderr, "Error en el sem_wait de sem_lector\n");
            exit(EXIT_FAILURE);
        }
        (*p->cuentaLect)--;
        if(*p->cuentaLect == 0)
            //if(sem_post(&sem_escritor)){
            if(sem_post(p->sem_escritor) != 0){
                fprintf(stderr, "Error en el sem_post de sem_escritor\n");
                exit(EXIT_FAILURE);
            }
        //if(sem_post(&sem_lector)){
        if(sem_post(p->sem_lector) != 0){
            fprintf(stderr, "Error en el sem_post de sem_lector\n");
            exit(EXIT_FAILURE);
        }
    }
    //
    pthread_exit((void *) NULL);
}

void * escritor(void *arg){ 
    struct param3 *p = (struct param3 *) arg;
    int n = 5;
    for(int i=0; i<n; i++){
        //if(sem_wait(&sem_escritor)){ //solo un escritor al mismo tiempo
        if(sem_wait(p->sem_escritor) != 0){
            fprintf(stderr, "Error en el sem_wait de sem_escritor\n");
            exit(EXIT_FAILURE);
        }

        (*p->dato) += 1;
        printf("Escritor %lu, incrementando a valor = %d\n", pthread_self(), *p->dato);

        //if(sem_post(&sem_escritor)){
        if(sem_post(p->sem_escritor) != 0){
            fprintf(stderr, "Error en el sem_post de sem_escritor\n");
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit((void *) NULL);
}

void * Compra(void * arg){
    //int *M = (int *) arg, n=10;
    struct param2 *p = (struct param2 *) arg;
    int n=10;
    int modelo=rand()%(p->M+1), cantidad=rand()%(n+1);
    printf("<-- Cliente %lu, compro %d unidades de la camiseta %d\n", pthread_self(), cantidad, modelo);
	//if(pthread_mutex_lock(&mtx_compra_suministro)){
    if(pthread_mutex_lock(p->mtx_compra_suministro) != 0){
		fprintf(stderr, "pthread_mutex_lock error\n");
		exit(EXIT_FAILURE);
	}

    //buffer_compra_suministro[modelo] -= cantidad;
    if(p->buffer_compra_suministro[modelo] < cantidad){
        printf("No hay suficiente stock de la camiseta %d\n", modelo);
        cantidad = p->buffer_compra_suministro[modelo];
        printf("Se procede a vender las siponibles...\n");
    }
    p->buffer_compra_suministro[modelo] -= cantidad;

	//if(pthread_mutex_unlock(&mtx_compra_suministro)){
    if(pthread_mutex_unlock(p->mtx_compra_suministro) != 0){
		fprintf(stderr, "pthread_mutex_unlock error\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void *) NULL);
}

void * Suministro(void * arg){
    //int *M = (int *) arg, n=10;
    struct param2 *p = (struct param2 *) arg;
    int n=10;
    int modelo=rand()%(p->M+1), cantidad=rand()%(n+1);
	printf("--> Proveedor %lu, suministro %d unidades de la camiseta %d\n", pthread_self(), cantidad, modelo);
    //if(pthread_mutex_lock(&mtx_compra_suministro)){
    if(pthread_mutex_lock(p->mtx_compra_suministro) != 0){
		fprintf(stderr, "pthread_mutex_lock error\n");
		exit(EXIT_FAILURE);
	}

    //buffer_compra_suministro[modelo] += cantidad;
    p->buffer_compra_suministro[modelo] += cantidad;

	//if(pthread_mutex_unlock(&mtx_compra_suministro)){
    if(pthread_mutex_unlock(p->mtx_compra_suministro) != 0){
		fprintf(stderr, "pthread_mutex_unlock error\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void *) NULL);
}

//prod-consum
struct param1{
    int tam_buffer_, n_elem, buffin_, buffout_;
    sem_t *sem_prod2, *sem_consum2, *sem_lleno2, *sem_vacio2;
    int *buffer_;
};

void * prod(void * arg){
	struct param1 *p = (struct param1 *) arg;
	int n = 10;
    //for(int i=0; i<elem; i++){
	for(int i=0; i<(p->n_elem); i++){
        //if(sem_wait(&sem_lleno)){
        if(sem_wait(p->sem_lleno2) != 0){
            fprintf(stderr, "sem_wait error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_wait(&sem_prod)){
        if(sem_wait(p->sem_prod2) != 0){
            fprintf(stderr, "sem_wait error\n");
            exit(EXIT_FAILURE);
        }

		int random = rand()%n+1;
		/*buffer[buffin] = random;
        printf("Produciendo un %d en la posición %d\n", buffer[buffin], buffin);
		buffin = (buffin+1)%TAM_BUFFER;*/
        p->buffer_[p->buffin_] = random;
        printf("Produciendo un %d en la posición %d\n", p->buffer_[p->buffin_], p->buffin_);
        p->buffin_ = (p->buffin_+1)%(p->tam_buffer_);

        //if(sem_post(&sem_consum)){
        if(sem_post(p->sem_consum2) != 0){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_post(&sem_vacio)){
        if(sem_post(p->sem_vacio2) != 0){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
	}
	pthread_exit((void *) NULL);
}

void * consum(void * arg){
	struct param1 *p = (struct param1 *) arg;
    //for(int i=0; i<elem; i++){
	for(int i=0; i<(p->n_elem); i++){
        //if(sem_wait(&sem_vacio)){
        if(sem_wait(p->sem_vacio2) != 0){
            fprintf(stderr, "sem_wait error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_wait(&sem_consum)){
        if(sem_wait(p->sem_consum2) != 0){
            fprintf(stderr, "sem_wait error\n");
            exit(EXIT_FAILURE);
        }

        /*printf("Consumiendo un %d en la posición %d\n", buffer[buffout], buffout);
		buffout = (buffout+1)%TAM_BUFFER;*/
        printf("Consumiendo un %d en la posición %d\n", p->buffer_[p->buffout_], p->buffout_);
        p->buffout_ = (p->buffout_+1)%(p->tam_buffer_);

        //if(sem_post(&sem_prod)){
        if(sem_post(p->sem_prod2) != 0){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_post(&sem_lleno)){
        if(sem_post(p->sem_lleno2) != 0){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
	}
	pthread_exit((void *) NULL);
}

int main(int argc, char **argv){
    if(argc != 6){
        fprintf(stderr, "Usage: n_par_impar n_lector_escritor N(cantidad) M(n_modelos) n_prod_consum\n");
        exit(EXIT_FAILURE);
    }

    //par-impar
    int par = 0, impar = 0;
    pthread_mutex_t mutex_par, mutex_impar;

    int n_par_impar = atoi(argv[1]);
    pthread_t thread_par_impar[n_par_impar];
    struct param4 p4[n_par_impar];
    srand(time(NULL));
    //int indice[N];

    printf("Main()... La variable par esta inicializada a %d\n", par);
    printf("Main()... La variable impar esta inicializada a %d\n", impar);

    if(pthread_mutex_init(&mutex_par, NULL) != 0){
        fprintf(stderr, "Error en la inicializacion del mutex_par.\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_init(&mutex_impar, NULL) != 0){
        fprintf(stderr, "Error en la inicializacion del mutex_impar.\n");
        exit(EXIT_FAILURE);
    }
    
    //lector-escritor
    int n = atoi(argv[2]), count = 0, data = 0;
    pthread_t thread_lector[n], thread_escritor[n];
    struct param3 p3[n];

    sem_t sem_escritor_, sem_lector_;

    //if(sem_init(&sem_escritor, 0, 1)){
    if(sem_init(&sem_escritor_, 0, 1) != 0){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_lector, 0, n)){
    if(sem_init(&sem_lector_, 0, n) != 0){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }

    //compra-suministro
    //M = n_modelos, N = cantidad
    int N = atoi(argv[3]), M = atoi(argv[4]);
    pthread_t thread_compra[N], thread_suministro[M];
    srand(time(NULL));

    pthread_mutex_t mtx_compra_suministro_;

    //if(pthread_mutex_init(&mtx_compra_suministro, NULL)){
    if(pthread_mutex_init(&mtx_compra_suministro_, NULL)){
        fprintf(stderr, "pthread_mutex_init error\n");
        exit(EXIT_FAILURE);
    }
    struct param2 p2;

    if((p2.buffer_compra_suministro = malloc(M * sizeof(int))) == NULL){
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }

    //prod-consum
    int n_prod_consum = atoi(argv[5]);
    pthread_t thread_prod[n_prod_consum], thread_consum[n_prod_consum];
    struct param1 p1;
    srand(time(NULL));

    p1.tam_buffer_ = 3; //cambiar valor
    p1.n_elem = 1; //cambiar valor
    p1.buffin_ = 0;
    p1.buffout_ = 0;

    int v[p1.tam_buffer_];
    p1.buffer_ = v;
    
    //semaforos prod-consum
    sem_t prod_, consum_, lleno_, vacio_;
    //if(sem_init(&sem_prod, 0, 1)){
    if(sem_init(&prod_, 0, 1) != 0){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_consum, 0, 1)){
    if(sem_init(&consum_, 0, 1) != 0){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_lleno, 0, TAM_BUFFER)){
    if(sem_init(&lleno_, 0, p1.tam_buffer_) != 0){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_vacio, 0, 0)){
    if(sem_init(&vacio_, 0, 0) != 0){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }

    //creación de hebras
    //par-impar
    for(int i = 0; i < n_par_impar; i++){
        p4[i].par = &par;
        p4[i].impar = &impar;
        p4[i].mutex_par = &mutex_par;
        p4[i].mutex_impar = &mutex_impar;
        p4[i].posicion = i + 1;
        //indice[i] = i + 1;
        //if(pthread_create(&hilos[i], NULL, (void *) &funcion, (void *) &indice[i]) != 0){
        if(pthread_create(&thread_par_impar[i], NULL, (void *) &f_par_impar, (void *)&p4[i]) != 0){
            fprintf(stderr, "Error en pthread_create().\n");
            exit(EXIT_FAILURE);
        }
    }

    //lector-escritor
    for(int i=0; i<n; i++){
        p3[i].sem_escritor = &sem_escritor_;
        p3[i].sem_lector = &sem_lector_;
        p3[i].cuentaLect = &count;
        p3[i].dato = &data;
        if(pthread_create(&thread_lector[i], NULL, (void *) &lector, (void *) &p3[i]) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<n; i++){
        p3[i].sem_escritor = &sem_escritor_;
        p3[i].sem_lector = &sem_lector_;
        p3[i].dato = &data;
        if(pthread_create(&thread_escritor[i], NULL, (void *) &escritor, (void *) &p3[i]) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    }

    //compra-suministro
    printf("Stock disponible de cada camiseta antes de abrir la tienda: \n");   
    for(int i=0; i<M; i++){
        /*buffer_compra_suministro[i] = rand()%100;
        printf("Camisetas modelo %d: %d\n", i+1, buffer_compra_suministro[i]);*/
        p2.buffer_compra_suministro[i] = rand()%100;
        printf("Camisetas modelo %d: %d\n", i+1, p2.buffer_compra_suministro[i]);
    }
    printf("\n");

    p2.mtx_compra_suministro = &mtx_compra_suministro_;
    p2.M = M;

    //como ya hay stock, empiezan los compradores
    for(int i=0; i<N; i++)
        if(pthread_create(&thread_compra[i], NULL, (void *) &Compra, (void *) &p2) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<M; i++)
        if(pthread_create(&thread_suministro[i], NULL, (void *) &Suministro, (void *) &p2) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }

    //prod-consum
    p1.sem_prod2 = &prod_;
    p1.sem_consum2 = &consum_;
    p1.sem_lleno2 = &lleno_;
    p1.sem_vacio2 = &vacio_;

    for(int i=0; i<n_prod_consum; i++)
        //if(pthread_create(&thread_prod[i], NULL, (void *) &prod, (void *) NULL)){
        if(pthread_create(&thread_prod[i], NULL, (void *) &prod, (void *) &p1) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    
    for(int i=0; i<n_prod_consum; i++)
        //if(pthread_create(&thread_consum[i], NULL, (void *) &consum, (void *) NULL)){
        if(pthread_create(&thread_consum[i], NULL, (void *) &consum, (void *) &p1) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
        
    //recogida de hebras
    //par-impar    
    for(int i = 0; i < n_par_impar; i++){
        if(pthread_join(thread_par_impar[i], (void **) NULL) != 0){
            fprintf(stderr, "Error en pthread_join().\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("Main()... La variable par al final contiene a %d\n", par);
    printf("Main()... La variable impar al final contiene a %d\n", impar);

    //lector-escritor
    for(int i=0; i<n; i++)
        if(pthread_join(thread_lector[i], (void **) NULL) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<n; i++)
        if(pthread_join(thread_escritor[i], (void **) NULL) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }

	//suministro-compra
	for(int i=0; i<N; i++)
        if(pthread_join(thread_compra[i], (void **) NULL) != 0){
            fprintf(stderr, "pthread_join error\n");
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<M; i++)
        if(pthread_join(thread_suministro[i], (void **) NULL) != 0){
            fprintf(stderr, "pthread_join error\n");
            exit(EXIT_FAILURE);
        }

    printf("\nStock disponible de cada camiseta al cerrar la tienda: \n");
    for(int i=0; i<M; i++)
        //printf("Camisetas modelo %d: %d\n", i+1, buffer_compra_suministro[i]);
        printf("Camisetas modelo %d: %d\n", i+1, p2.buffer_compra_suministro[i]);

    //prod-consum
	for(int i=0; i<n_prod_consum; i++)
		if(pthread_join(thread_prod[i], (void **) NULL) != 0){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
	for(int i=0; i<n_prod_consum; i++)
		if(pthread_join(thread_consum[i], (void **) NULL) != 0){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
    
    //destrucción de semáforos
    //par-impar
    if(pthread_mutex_destroy(&mutex_par) != 0){
        fprintf(stderr, "Error en la destruccion del mutex_par.\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_destroy(&mutex_impar) != 0){
        fprintf(stderr, "Error en la destruccion del mutex_impar.\n");
        exit(EXIT_FAILURE);
    }

    //lector-escritor
    //if(sem_destroy(&sem_lector)){
        if(sem_destroy(&sem_lector_) != 0){
            fprintf(stderr, "sem_destroy error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_destroy(&sem_escritor)){
        if(sem_destroy(&sem_escritor_) != 0){
            fprintf(stderr, "sem_destroy error\n");
            exit(EXIT_FAILURE);
        }

    //compra-suministro
    //if(pthread_mutex_destroy(&mtx_compra_suministro)){
    if(pthread_mutex_destroy(&mtx_compra_suministro_) != 0){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }

    //prod-consum
    //if(sem_destroy(&sem_prod)){
    if(sem_destroy(&prod_) != 0){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_destroy(&sem_consum)){
    if(sem_destroy(&consum_) != 0){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_destroy(&sem_lleno)){
    if(sem_destroy(&lleno_) != 0){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_destroy(&sem_vacio)){
    if(sem_destroy(&vacio_) != 0){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}