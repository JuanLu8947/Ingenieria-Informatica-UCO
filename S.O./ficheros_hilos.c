//Librerias estandar de C
#include <stdio.h>
#include <stdlib.h>

//Para hilos
#include <pthread.h>

//Para manejo de errores
#include <string.h>

void * funcion(void *arg) {
    FILE *f;
    char *nombre = (char *)arg, linea[256];
    int *cont = (int *)malloc(sizeof(int));  // Contador dinámico
    *cont = 0;

    if ((f = fopen(nombre, "r")) == NULL) {
        fprintf(stderr, "Error al abrir el fichero %s\n", nombre);
        pthread_exit(NULL);
    }

    // Leer líneas del archivo
    //fgets(char s[restrict .size], int size, FILE *restrict stream);
    while (fgets(linea, sizeof(linea), f) != NULL) {
        (*cont)++;
    }

    printf("Soy el hilo %lu y el número de líneas de %s es %d\n", pthread_self(), nombre, *cont);
    pthread_exit((void *)cont);  // Retornar el contador
}

int main(int argc, char **argv){
    if(argc < 2){
        perror("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }

    //
    int n = argc-1;
    pthread_t thread[n];
    
    //
    for(int i=1; i<=n; i++)
    if (pthread_create(&thread[i], NULL, (void *) &funcion, (void *) argv[i]) != 0) {
            fprintf(stderr, "Error en la creacion de la hebra\n");
            exit(EXIT_FAILURE);
        }

    //
    int *valorRecogido, cont=0;
    for(int i=1; i<=n; i++){
        if((pthread_join(thread[i], (void **) &valorRecogido)) != 0 ){
            fprintf(stderr, "Error en la recogida de la hebra\n");
            exit(EXIT_FAILURE);
        }
        cont += *valorRecogido;
    }
    printf("El número total de líneas es %d\n", cont);

    //
    exit(EXIT_SUCCESS);
}