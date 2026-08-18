//Librerias estandar de C
#include <stdio.h>
#include <stdlib.h>

//Para hilos
#include <pthread.h>

//Para exit(EXIT_FAILURE)
#include <string.h>

//Para rand()
#include <time.h>

//Para el uso de booleans en C
#include <stdbool.h>

//Libreria matemática
#include <math.h>

//pthread_create, pthread_join -> sus IF son != 0

struct param{ //mismo valor para cada hilo
	float suma;
};

struct datos{ //usado para datos cambiantes
	int *v, inicio, final;
};

void * funcion1(void * arg){
	struct param *p = (struct param *) arg;

	float x = (float)rand()/(float)(RAND_MAX/(100)); //RAND_MAX está en time.h
	float y = x;					//[0,100]

	p->suma = x + y;
	printf("Soy el hilo %lu, la suma de %f y %f es %f\n", pthread_self(), x, y, p->suma);

	float * datoDevuelto = (float *)malloc(sizeof(float));
	(*datoDevuelto) = p->suma;
	pthread_exit((void *) datoDevuelto);
}

void * funcion2(void * arg){
	struct datos *data = (struct datos *) arg;

	int * datoDevuelto = (int *)malloc(sizeof(int));

	for(int i=(data->inicio); i<(data->final); i++)
		*datoDevuelto += data->v[i];

	printf("Soy el hilo %lu, la suma es %d\n", pthread_self(), *datoDevuelto);
	pthread_exit((void *) datoDevuelto);
}

int main(int argc, char **argv){
	if(argc < 3){
		fprintf(stderr, "arg error. Usage: n_hilos m_tam-vector\n");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL)); //usado para los 2 tipos de hilos

	//Primero toda la creación

	printf("Main... Creando hilos suma flotantes\n");

	int n=atoi(argv[1]);
	pthread_t thread1[n];
	struct param p;

	for(int i=0; i<n; i++)
		if(pthread_create(&thread1[i], NULL, (void *) &funcion1, (void *) &p)){
			fprintf(stderr, "pthread_create error\n");
			exit(EXIT_FAILURE);
		}


	printf("Main... Creando hilos2\n");

	int m = atoi(argv[2]);
	pthread_t thread2[n];
	struct datos d[m];
    int v1[m];
	//hay q inicializar el vector con valores
    for(int i=0; i<m; i++){
    	v1[i] = rand()%m;
    	printf("v[%d] = %d\n", i, v1[i]);
    }

	for(int i=0; i<n; i++){
		d[i].v = v1;
		d[i].inicio = i * m/n; //iteración * número de elementos del vector / número de hilos
		d[i].final = (i+1) * m/n;
		if(i == n-1)
			d[i].final = m;
		if(pthread_create(&thread2[i], NULL, (void *) &funcion2, (void *) &d[i]) != 0){
			fprintf(stderr, "pthread_create error\n");
			exit(EXIT_FAILURE);
		}
	}

	//Segundo toda la recogida
	printf("Main... Recogiendo hilos suma flotantes\n");
	float *datoRecogido1, suma_final1=0.0;
	for(int i=0; i<n; i++){
		if(pthread_join(thread1[i], (void **) &datoRecogido1) != 0){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
		suma_final1 += *datoRecogido1;
	}
	printf("Main... La suma final es: %f\n", suma_final1);
	free(datoRecogido1);

	printf("Main... Recogiendo hilos2\n");
	int *datoRecogido2, suma_final2=0;
	for(int i=0; i<n; i++){
		if(pthread_join(thread2[i], (void **) &datoRecogido2) != 0){
			fprintf(stderr, "pthread_join error\n");
			exit(EXIT_FAILURE);
		}
		suma_final2 += *datoRecogido2;
	}
	printf("Main... La suma final es: %d\n", suma_final2);
	free(datoRecogido2);

	exit(EXIT_SUCCESS);
}