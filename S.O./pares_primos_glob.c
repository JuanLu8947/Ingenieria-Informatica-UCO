//Librerías estándar de C
#include <stdio.h>
#include <stdlib.h>

//Para hilos y mutex
#include <pthread.h>

//semáforos generales
//#include <semaphore.h> //no hay 

//Para exit(EXIT_SUCCESS)
#include <string.h>

//Para el uso de rand()
#include <time.h>

//Para uso de booleans values
#include <stdbool.h>

//Libreria matemática
//#include <math.h> //no se usa

//pthread_create, pthread_join, pthread_mutex_lock, pthread_mutex_unlock sus IF son != 0

//Par-Impar
//existen varias versiones de par_impar
//calcular par-impar
struct param1{
	pthread_mutex_t *mtx_calc_pares;
	int *suma;
};

/*pthread_mutex_t mtx_calc_pares;*/

void * calc_pares(void * arg){
	struct param1 *p = (struct param1 *) arg;
	//int *suma;
	//if((suma = (int *)malloc(sizeof(int))) == NULL){}
    printf("\n[HILO PARES] Mi ID es %lu.\n", pthread_self());
    //int n = 2+5;
    int i = 2, n_pares = 0;
    //for(int i=2; i<n; i++){
    while(n_pares < 5){
        //if(pthread_mutex_lock(&mtx_calc_pares)){
		if(pthread_mutex_lock(p->mtx_calc_pares) != 0){
            fprintf(stderr, "Error en el lock\n");
            exit(EXIT_FAILURE);
        }
		//(*suma) += i;
        (*p->suma) += i;
        //if(pthread_mutex_unlock(&mtx_calc_pares)){
        if(pthread_mutex_unlock(p->mtx_calc_pares) != 0){
            fprintf(stderr, "Error en el unlock\n");
            exit(EXIT_FAILURE);
        }
        printf("[HILO PARES] Encontrado el número par %d.\n", i);
        n_pares++;
        i += 2;
    }
    pthread_exit((void*) NULL);
}

//Indice hebra
int par=0, impar=0;
pthread_mutex_t mtx_indices_par_impar;
void * f_par_impar(void * arg){
	printf("\nINDICES PAR IMPAR\n");
    int *indice = (int *) arg, n=5, m=10;
    int *suma = (int *)malloc(sizeof(int)), v[n];
	*suma = 0;
	if(pthread_mutex_lock(&mtx_indices_par_impar)){
		fprintf(stderr, "pthread_mutex_lock error\n");
		exit(EXIT_FAILURE);
	}

    for(int i=0; i<n; i++){
        v[i] = rand()%(m+1);
        printf("HILO %d: v[%d] = %d\n", *indice, i, v[i]);
        *suma += v[i];
        printf("HILO %d: suma = %d\n", *indice, *suma);
    }

    if(*indice%2 == 0)
        par += *suma;
    else
        impar += *suma;

	if(pthread_mutex_unlock(&mtx_indices_par_impar)){
		fprintf(stderr, "pthread_mutex_unlock error\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void *) suma);
}

//Primos
//existen varias versiones de primos
//calcular primos
struct param2{
    pthread_mutex_t *mtx_calc_primos;
    int *suma; //int *var_compartida;
};

//saber si un nº es primo
bool es_primo(int n){
	if(n < 2)
		return false;
	for(int i=2; i<n; i++)
		if(n%i == 0)
			return false;
	return true;
}

//pthread_mutex_t mtx_calc_primos;

void * calc_primos(void * arg){
    struct param2 *p = (struct param2 *) arg;
	//int *suma;
	//if((suma = (int *)malloc(sizeof(int))) == NULL){}
    printf("\n[HILO PRIMOS] Mi ID es %lu.\n", pthread_self());
    //int n = 12;
    //2, 3, 5, 7, 11
    //int n = 11;
    //suma: 2, 2+3, 5+5, 7+10, 11+7
    int i = 2, n_primos = 0;
    //for(int i=2; i<n; i++){
    while(n_primos < 5){
        if(es_primo(i)){
			//if(pthread_mutex_lock(mtx_calc_primos) != 0){
            if(pthread_mutex_lock(p->mtx_calc_primos) != 0){
                fprintf(stderr, "Error en el lock\n");
                exit(EXIT_FAILURE);
            }
			//(*suma) += i;
            (*p->suma) += i;
			//if(pthread_mutex_unlock(mtx_calc_primos) != 0){
            if(pthread_mutex_unlock(p->mtx_calc_primos) != 0){
                fprintf(stderr, "Error en el unlock\n");
                exit(EXIT_FAILURE);
            }
            printf("[HILO PRIMOS] Encontrado el número primo %d.\n", i);
            n_primos++;
        }
        i++;
    }
	//pthread_exit((void *) suma);
    pthread_exit((void*) NULL);
}

//indice hebras primos
int primo=0, no_primo=0;
pthread_mutex_t mtx_indices_primos;

/*
struct param2{
	pthread_mutex_t *mtx_calc_primos;
	int *suma; //int *var_compartida;
};
*/

void * f_primos(void * arg){
	printf("\nINDICES PRIMOS\n");
    int *indices_primos = (int *) arg, n=5, m=10;
    int *suma = (int *)malloc(sizeof(int)), v[n];
	*suma = 0;
	//struct param2 *p = (struct param2 *) arg;
	if(pthread_mutex_lock(&mtx_indices_primos)){
		fprintf(stderr, "pthread_mutex_lock error\n");
		exit(EXIT_FAILURE);
	}
	
    for(int i=0; i<n; i++){
        v[i] = rand()%(m+1);
        printf("HILO %d: v[%d] = %d\n", *indices_primos, i, v[i]);
        *suma += v[i];
        printf("HILO %d: suma = %d\n", *indices_primos, *suma);
    }
	
    if(es_primo(*indices_primos))
		primo += *suma;
    else
		no_primo += *suma;
	if(pthread_mutex_unlock(&mtx_indices_primos)){
	//if(pthread_mutex_unlock(p->mtx_indices_primos)){
		fprintf(stderr, "pthread_mutex_unlock error\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void *) suma);
}

//Sin_Globales
struct glob{
	pthread_mutex_t *mtx_glob;
	int *var_compartida, n;
};

void * f_glob(void * arg){
	struct glob *g = (struct glob *) arg;
    printf("Hilo GLOB %lu, incremento %d\n", pthread_self(), (g->n));
	for(int i=0; i<(g->n); i++){
		if(pthread_mutex_lock(g->mtx_glob)){
			fprintf(stderr, "pthread_mutex_lock error\n");
			exit(EXIT_FAILURE);
		}

		(*g->var_compartida)++;

		if(pthread_mutex_unlock(g->mtx_glob)){
			fprintf(stderr, "pthread_mutex_unlock error\n");
			exit(EXIT_FAILURE);
		}
	}
	pthread_exit((void *) NULL);
}

//MAIN
int main(int argc, char **argv){
    if(argc != 5){
        fprintf(stderr, "Usage: n_pares_calc n_indices_par_impar n_primos_calc n_indices_primos\n");
        exit(EXIT_FAILURE);
    }

	srand(time(NULL));

	//par-impar
	//calc_pares
	int n_pares = atoi(argv[1]);
	pthread_t thread_calc_pares[n_pares];

    int * suma1;
    pthread_mutex_t * mtx_calc_pares_;
    struct param1 p1;

	if ((suma1 = (int*)malloc(sizeof(int))) == NULL){
        fprintf(stderr, "[MAIN] Error al reservar memoria para la suma.\n");
        exit(EXIT_FAILURE);
    }
    *suma1 = 0;

    if ((mtx_calc_pares_ = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))) == NULL){
        fprintf(stderr, "[MAIN] Error al reservar memoria para el mutex.\n");
        exit(EXIT_FAILURE);
    }

	if(pthread_mutex_init(mtx_calc_pares_, NULL)){
		fprintf(stderr, "pthread_mutex_init error\n");
		exit(EXIT_FAILURE);
	}

	//indice_par_impar
	int n_indices_par_impar = atoi(argv[2]);
	pthread_t thread_indices_par_impar[n_indices_par_impar];
    int indice[n_indices_par_impar];

	if(pthread_mutex_init(&mtx_indices_par_impar, NULL)){
		fprintf(stderr, "pthread_mutex_init error\n");
		exit(EXIT_FAILURE);
	}	

	//primos
	//calc_primos
	int n_primos = atoi(argv[3]);
	pthread_t thread_calc_primos[n_primos];

    int * suma2;
    pthread_mutex_t * mtx_calc_primos_;
    struct param2 p2;

	if ((suma2 = (int*)malloc(sizeof(int))) == NULL){
        fprintf(stderr, "[MAIN] Error al reservar memoria para la suma.\n");
        exit(EXIT_FAILURE);
    }
    *suma2 = 0;

    if ((mtx_calc_primos_ = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))) == NULL){
        fprintf(stderr, "[MAIN] Error al reservar memoria para el mutex.\n");
        exit(EXIT_FAILURE);
    }

	if(pthread_mutex_init(mtx_calc_primos_, NULL)){
		fprintf(stderr, "pthread_mutex_init error\n");
		exit(EXIT_FAILURE);
	}

	//indices_primos
	int n_indices_primos = atoi(argv[4]);
	pthread_t thread_indices_primos[n_indices_primos];
    int indices_primos[n_indices_primos];

	if(pthread_mutex_init(&mtx_indices_primos, NULL)){
		fprintf(stderr, "pthread_mutex_init error\n");
		exit(EXIT_FAILURE);
	}

	//creación de hebras
	//calc_pares
    p1.mtx_calc_pares = mtx_calc_pares_;
    p1.suma = suma1;
	for(int i=0; i<n_pares; i++)
		if(pthread_create(&thread_calc_pares[i], NULL, (void *) &calc_pares, (void *) &p1)){
			fprintf(stderr, "pthread_create error\n");
			exit(EXIT_FAILURE);
		}
	printf("\n");

	//indices_par_impar
	for(int i=0; i<n_indices_par_impar; i++){
        indice[i] = i+1;
		if(pthread_create(&thread_indices_par_impar[i], NULL, (void *) &f_par_impar, (void *) &indice[i])){
			fprintf(stderr, "pthread_create error\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("\n");
	//primos
	//calc_primos
    p2.mtx_calc_primos = mtx_calc_primos_;
    p2.suma = suma2;
	for(int i=0; i<n_primos; i++)
		if(pthread_create(&thread_calc_primos[i], NULL, (void *) &calc_primos, (void *) &p2)){
			fprintf(stderr, "pthread_create error\n");
			exit(EXIT_FAILURE);
		}
	
	//indices_primos
	for(int i=0; i<n_indices_primos; i++){
        indices_primos[i] = i+1;
		if(pthread_create(&thread_indices_primos[i], NULL, (void *) &f_primos, (void *) &indices_primos[i])){
			fprintf(stderr, "pthread_create error\n");
			exit(EXIT_FAILURE);
		}
	}

	//sin_globales
	int n_glob = argc-1, suma_compartida = 0;;
	pthread_t thread_glob[n_glob];
	struct glob g[n_glob];
	
	pthread_mutex_t mtx_glob_;
	if(pthread_mutex_init(&mtx_glob_, NULL)){
		fprintf(stderr, "pthread_mutex_init error\n");
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<n_glob; i++){
		g[i].mtx_glob = &mtx_glob_;
		g[i].var_compartida = &suma_compartida;
		g[i].n = atoi(argv[i+1]);
		if(pthread_create(&thread_glob[i], NULL, (void *) &f_glob, (void *) &g[i])){
			fprintf(stderr, "pthread_create error\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("\n");
	//recogida de hebras
	//calc_pares
	for(int i=0; i<n_pares; i++)
		if(pthread_join(thread_calc_pares[i], (void **) NULL)){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
	printf("PARES: El valor de la suma tras ejecutar los hilos es %d.\n", *suma1);

	printf("\n");
	//indices_par_impar
	int *dato, suma_par=0, suma_impar=0;
    for(int i=0; i<n_indices_par_impar; i++){
        if(pthread_join(thread_indices_par_impar[i], (void **) &dato)){
			fprintf(stderr, "pthread_join error\n");
            exit(EXIT_FAILURE);
        }        
        indice[i]=i+1;
        if(indice[i]%2 == 0)
            suma_par += *dato;
        else
            suma_impar += *dato;
        printf("PAR-IMPAR: La hebra de orden de creacion %d devolvió el valor de suma: %d\n", i+1, *dato);
    }
    printf("\nPAR-IMPAR: Valor de la variable compartida impar: %d\n", impar);
    printf("PAR-IMPAR: Suma de los valores devueltos por las hebras de creación impares: %d\n", suma_impar);
    
    printf("\nPAR-IMPAR: Valor de la variable compartida par: %d\n", par);
    printf("PAR-IMPAR: Suma de los valores devueltos por las hebras de creación pares: %d\n", suma_par);

	printf("\n");
	//primos
	//calc_primos
	for(int i=0; i<n_primos; i++)
		if(pthread_join(thread_calc_primos[i], (void **) NULL)){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
	printf("PRIMOS: El valor de la suma tras ejecutar los hilos es %d.\n", *suma2);

	//indices_primos
	int *dato2, suma_primos=0, suma_no_primos=0;
    for(int i=0; i<n_indices_primos; i++){
        if(pthread_join(thread_indices_primos[i], (void **) &dato2)){
			fprintf(stderr, "pthread_join error\n");
            exit(EXIT_FAILURE);
        }
        indices_primos[i]=i+1;
        if(es_primo(indices_primos[i]))
			suma_primos += *dato2;
        else
            suma_no_primos += *dato2;
        printf("PRIMOS-NO_PRIMOS: La hebra de orden de creacion %d devolvió el valor de suma: %d\n", i+1, *dato2);
    }
    printf("\nPRIMOS-NO_PRIMOS: Valor de la variable compartida primo: %d\n", primo);
    printf("PRIMOS-NO_PRIMOS: Suma de los valores devueltos por las hebras de creación primo: %d\n", suma_primos);

    printf("\nPRIMOS-NO_PRIMOS: Valor de la variable compartida no_primo: %d\n", no_primo);
    printf("PRIMOS-NO_PRIMOS: Suma de los valores devueltos por las hebras de creación no_primo: %d\n", suma_no_primos);
    
	printf("\n");

	//sin_globales
	for(int i=0; i<n_glob; i++)
		if(pthread_join(thread_glob[i], (void **) NULL)){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
	printf("GLOB: Suma compartida: %d\n", *g->var_compartida);

	//destrucción de semáforos
	//calc_pares
	if(pthread_mutex_destroy(mtx_calc_pares_)){
		fprintf(stderr, "pthread_mutex_destroy error\n");
		exit(EXIT_FAILURE);
	}

	//indices_par_impar
	if(pthread_mutex_destroy(&mtx_indices_par_impar)){
		fprintf(stderr, "pthread_mutex_destroy error\n");
		exit(EXIT_FAILURE);
	}

	//primos
	//calc_primos
	if(pthread_mutex_destroy(mtx_calc_primos_)){
		fprintf(stderr, "pthread_mutex_destroy error\n");
		exit(EXIT_FAILURE);
	}

	//indices_primos
	if(pthread_mutex_destroy(&mtx_indices_primos)){
		fprintf(stderr, "pthread_mutex_destroy error\n");
		exit(EXIT_FAILURE);
	}

	//sin_globales
	if(pthread_mutex_destroy(&mtx_glob_)){
		fprintf(stderr, "pthread_mutex_destroy error\n");
		exit(EXIT_FAILURE);
	}

    free(dato);
    free(dato2);
	exit(EXIT_SUCCESS);
}