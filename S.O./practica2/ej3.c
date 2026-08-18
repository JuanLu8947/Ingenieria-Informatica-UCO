#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//gcc -lpthread

struct Datos{
    int *vsize, inicio, final;
};

void *funcion(void *arg){
    struct Datos* Data = (struct Datos*) arg;
    int *suma = (int *)malloc(sizeof(int));
    for(int i=(Data->inicio); i<(Data->final); i++){
        *suma += Data->vsize[i];
    }
    printf("Soy el hilo %lu y la suma es %d\n", pthread_self(), *suma);
    pthread_exit((void*) suma);
}

int main(int argc, char **argv){
    if(argc != 2){
        perror("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }

    // 10/7=1 -> el septimo hace el resto 
    srand(time(NULL));
    int n = atoi(argv[1]);;
    struct Datos datos[n]; //n: para q no se modifiquen los valores del h1
    int n_elem_hebra = 10/n, v[10];
    for(int i=0; i<10; i++){
        v[i] = rand()%10;
        printf("v[%d] = %d\n", i, v[i]);
    }
    printf("\n\n");
    //datos.n_hebras = 10/n;
    pthread_t thread[n];
    for(int i=0; i<n; i++){
        datos[i].vsize = v;
        datos[i].inicio = i * n_elem_hebra;
        datos[i].final = (i+1) * n_elem_hebra;
        if(i == n-1){
            datos[i].final = 10;
        }
        if(pthread_create(&thread[i], NULL, (void *) &funcion, (void *) &datos[i]) != 0){
            perror("Error en la creacion del hilo\n");
            exit(EXIT_FAILURE);
        }
    }
    int suma_final = 0, *valorRecogido;
    for(int i=0; i<n; i++){
        if(pthread_join(thread[i], (void **) &valorRecogido) != 0){
            perror("Error en la espera del hilo\n");
            exit(EXIT_FAILURE);
        }
        suma_final += *valorRecogido;
    }
    printf("La suma total es %d\n", suma_final);
    free(valorRecogido);
    exit(EXIT_SUCCESS);
}