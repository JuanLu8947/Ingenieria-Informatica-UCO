#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Error de argumentos\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]), fact = 1;
    for(int i=1; i<=n; i++)
        fact *= i;
    printf("El factorial de %d es %d\n", n, fact);
    exit(EXIT_SUCCESS);
}