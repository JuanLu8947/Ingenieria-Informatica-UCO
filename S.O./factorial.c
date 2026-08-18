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
    int n = atoi(argv[1]);
	printf("EL factorial de %d es: ", n);
    for(int i=n-1; i>=1; i--){
        n *= i;
    }
	printf("%d\n", n);
	exit(EXIT_SUCCESS);
}