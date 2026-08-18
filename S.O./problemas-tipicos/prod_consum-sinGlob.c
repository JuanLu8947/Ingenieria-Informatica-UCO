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

//pthread_create, pthread_join, pthread_mutex_lock, pthread_mutex_unlock sus IF son != 0

/*sem_t sem_prod, sem_consum;
sem_t sem_vacio, sem_lleno;

#define TAM_BUFFER 3
#define elem 1

int buffin = 0;
int buffer[TAM_BUFFER];
int buffout = 0;*/

struct param{
    int tam_buffer_, n_elem, buffin_, buffout_;
    sem_t *sem_prod2, *sem_consum2, *sem_lleno2, *sem_vacio2;
    int *buffer_;
};

void * prod(void * arg){
	struct param *p = (struct param *) arg;
	int n = 10;
    //for(int i=0; i<elem; i++){
	for(int i=0; i<(p->n_elem); i++){
        //if(sem_wait(&sem_lleno)){
        if(sem_wait(p->sem_lleno2)){
            fprintf(stderr, "sem_wait error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_wait(&sem_prod)){
        if(sem_wait(p->sem_prod2)){
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
        if(sem_post(p->sem_consum2)){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_post(&sem_vacio)){
        if(sem_post(p->sem_vacio2)){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
	}
	pthread_exit((void *) NULL);
}

void * consum(void * arg){
	struct param *p = (struct param *) arg;
    //for(int i=0; i<elem; i++){
	for(int i=0; i<(p->n_elem); i++){
        //if(sem_wait(&sem_vacio)){
        if(sem_wait(p->sem_vacio2)){
            fprintf(stderr, "sem_wait error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_wait(&sem_consum)){
        if(sem_wait(p->sem_consum2)){
            fprintf(stderr, "sem_wait error\n");
            exit(EXIT_FAILURE);
        }

        /*printf("Consumiendo un %d en la posición %d\n", buffer[buffout], buffout);
		buffout = (buffout+1)%TAM_BUFFER;*/
        printf("Consumiendo un %d en la posición %d\n", p->buffer_[p->buffout_], p->buffout_);
        p->buffout_ = (p->buffout_+1)%(p->tam_buffer_);

        //if(sem_post(&sem_prod)){
        if(sem_post(p->sem_prod2)){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
        //if(sem_post(&sem_lleno)){
        if(sem_post(p->sem_lleno2)){
            fprintf(stderr, "sem_post error\n");
            exit(EXIT_FAILURE);
        }
	}
	pthread_exit((void *) NULL);
}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Usage: prod_consum\n");
        exit(EXIT_FAILURE);
    }
    
    //initialization of variables
    int n_prod_consum = atoi(argv[1]);
    pthread_t thread_prod[n_prod_consum], thread_consum[n_prod_consum];
    struct param p;
    srand(time(NULL));

    p.tam_buffer_ = 3;
    p.n_elem = 1;
    p.buffin_ = 0;
    p.buffout_ = 0;

    int v[p.tam_buffer_];
    p.buffer_ = v;
    
    sem_t prod_, consum_, lleno_, vacio_;
    //if(sem_init(&sem_prod, 0, 1)){
    if(sem_init(&prod_, 0, 1)){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_consum, 0, 1)){
    if(sem_init(&consum_, 0, 1)){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_lleno, 0, TAM_BUFFER)){
    if(sem_init(&lleno_, 0, p.tam_buffer_)){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_init(&sem_vacio, 0, 0)){
    if(sem_init(&vacio_, 0, 0)){
        fprintf(stderr, "sem_init error\n");
        exit(EXIT_FAILURE);
    }

    p.sem_prod2 = &prod_;
    p.sem_consum2 = &consum_;
    p.sem_lleno2 = &lleno_;
    p.sem_vacio2 = &vacio_;

    for(int i=0; i<n_prod_consum; i++)
        //if(pthread_create(&thread_prod[i], NULL, (void *) &prod, (void *) NULL)){
        if(pthread_create(&thread_prod[i], NULL, (void *) &prod, (void *) &p)){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    
    for(int i=0; i<n_prod_consum; i++)
        //if(pthread_create(&thread_consum[i], NULL, (void *) &consum, (void *) NULL)){
        if(pthread_create(&thread_consum[i], NULL, (void *) &consum, (void *) &p)){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }

	for(int i=0; i<n_prod_consum; i++)
		if(pthread_join(thread_prod[i], (void **) NULL)){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
	for(int i=0; i<n_prod_consum; i++)
		if(pthread_join(thread_consum[i], (void **) NULL)){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
    
    //destrucción de semáforos
    //if(sem_destroy(&sem_prod)){
    if(sem_destroy(&prod_)){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_destroy(&sem_consum)){
    if(sem_destroy(&consum_)){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_destroy(&sem_lleno)){
    if(sem_destroy(&lleno_)){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }
    //if(sem_destroy(&sem_vacio)){
    if(sem_destroy(&vacio_)){
        fprintf(stderr, "pthread_mutex_destroy error\n");
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}