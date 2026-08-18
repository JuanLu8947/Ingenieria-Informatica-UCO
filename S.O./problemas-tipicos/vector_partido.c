//Libreria estandar de C
#include <stdio.h>
#include <stdlib.h>

//para exit(EXIT_SUCCESS)
#include <string.h>

//Para hilos
#include <pthread.h>

//Para rand()
#include <time.h>

//Para malloc (por si acaso)
#include <malloc.h>

struct param{
    int *v, inicio, final;
};

void * funcion(void * arg){
    struct param *p = (struct param *) arg;

    int *dato = (int*)malloc(sizeof(int));
    for(int i=(p->inicio); i<(p->final); i++)
        (*dato) += p->v[i];

    printf("Soy el hilo %lu, la suma es %d\n", pthread_self(), *dato);

    pthread_exit((void *) dato);
}

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "arg error\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    pthread_t thread[n];
    struct param p[n];
    //m = tamaño del vector y n = nº_hilos

    int m = atoi(argv[2]);
    int v_[m];
    srand(time(NULL));
    for(int i=0; i<m; i++){
        v_[i] = rand()%(m+1);
        printf("v[%d] = %d\n", i, v_[i]);
    }

    for(int i=0; i<n; i++){
        p[i].v = v_;
        p[i].inicio = i * m/n;
        p[i].final = (i+1) * m/n;
        if(i == n-1) //lo que quede lo hace el último hilo
            p[i].final = m;
        if(pthread_create(&thread[i], NULL, (void *) &funcion, (void *) &p[i])){
            fprintf(stderr, "pthread_create error\n");
            exit(EXIT_FAILURE);
        }
    }
    int *dato, suma_final=0;
    for(int i=0; i<n; i++){
        if(pthread_join(thread[i], (void **) &dato)){
            fprintf(stderr, "pthread_join error\n");
            exit(EXIT_FAILURE);
        }
        suma_final += *dato;
    }
    printf("La suma total es %d\n", suma_final);

    exit(EXIT_SUCCESS);
}