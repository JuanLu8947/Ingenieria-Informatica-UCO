#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
//gcc -lpthread

void * leeLineasFich(void * arg){
    FILE *f;
    char *nombre = (char *)arg, linea[MAX];
    int *cont = (int *)malloc(sizeof(int));
    if((f = fopen(nombre, "r")) == NULL){
        perror("Error en la apertura del fichero\n");
        exit(EXIT_FAILURE);
    }
    //uso de fgets o fscanf -> mejor fgets
    //fgets: lee caracteres de la posición actual de ruta hasta el primer carácter de nueva línea (\n)
    //Valor de retorno: 
     //La función fgets retorna cadena si es realizada con éxito.
     //Tiene en cuenta el final de ficher EOF.
     //Es decir:
      //Cada una de estas funciones devuelve str.
      //Se devuelve NULL para indicar una condición de error o de final de archivo.
    //char *fgets(char *str, int n, FILE *stream)
     //str: Puntero a la ubicación de almacenamiento de los datos.
     //n: Número máximo de caracteres que se van a leer.
     //stream: Puntero a la estructura FILE.

    while(fgets(linea, sizeof(linea), f) != NULL){
        (*cont)++;
    }
    
    printf("Soy el hilo %lu y el nº de lineas del %s es %d\n", pthread_self(), nombre, *cont);
    fclose(f);
    pthread_exit((void *) cont);
}

int main(int argc, char **argv){
    if(argc != 2){
        perror("Error en la linea de arg\n");
        exit(EXIT_FAILURE);
    }
    int n = argc-1;
    pthread_t thread[n];

    for(int i=1; i<=n; i++){
        if((pthread_create(&thread[i], NULL, (void *) &leeLineasFich, (void *) argv[i])) != 0 ){
            perror("Error en la creacion de la hebra\n");
            exit(EXIT_FAILURE);
        }
    }

    int *valorRecogido, cont=0;
    for(int i=1; i<=n; i++){
        if((pthread_join(thread[i], (void **) &valorRecogido)) != 0 ){
            perror("Error en la espera de la hebra\n");
            exit(EXIT_FAILURE);
        }
        cont += *valorRecogido;
    }
    printf("El nº total de lineas es %d\n", cont);
    exit(EXIT_SUCCESS);
}