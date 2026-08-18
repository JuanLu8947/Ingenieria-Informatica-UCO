//Librerias estandar de C
#include <stdio.h>
#include <stdlib.h>

//Para control de errores
#include <string.h>

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "arg error\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]), a = 1, b = 0;

    /* cada término es la suma de los dos anteriores
    f0 = 0
    f1 = 1
    fn = fn-1 + fn-2
    */

    for(int i=0; i<n; i++){
        printf("Fibonacci de %d es %d, %d.", i+1, b, a);
        //printf("%d, ",b);
        //printf("%d, ",a);
        b = b + a;
        a = a + b;
        printf("\n");
    }

    exit(EXIT_SUCCESS);
}