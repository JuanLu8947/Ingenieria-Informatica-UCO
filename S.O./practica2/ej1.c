#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//gcc -lpthread

struct param{
    float sum;
};

void * funcion(void *datoRecibido){
    struct param *p = (struct param *)datoRecibido;
    float num1 = (float)rand()/(float)(RAND_MAX/100);
    float num2 = (float)rand()/(float)(RAND_MAX/100);
    p->sum = num1 + num2;
    
    printf("Soy la hebra %lu, los numeros generados son %f y %f \ny la suma de estos numeros es: %f\n\n", pthread_self(), num1, num2, p->sum);
    
    float *valorRetorno = (float *)malloc(sizeof(float));
    (*valorRetorno) = p->sum;
    pthread_exit((void *) valorRetorno);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Error en la linea de argumentos\n");
        exit(EXIT_FAILURE);
    }

    int n=atoi(argv[1]);
    pthread_t thread[n];
    srand(time(NULL));
    struct param p;

    for(int i=0; i<n; i++){
        printf("Proceso principal: Se va a crear un hilo...\n");
        if(pthread_create(&thread[i], NULL, (void*) &funcion, (void*) &p) != 0){
            printf("Error en la creacion del hilo\n");
            exit(EXIT_FAILURE);
        }
        //pthread_create(pthread_t * thread, pthread_attr_t *attr, 
                        // void * (*start_routine) (void *), void *arg);
        //pthread_t * thread: puntero a la id de la hebra
        //pthread_attr_t *attr: atributos de la hebra
            //Si pasamos como parámetro NULL, la biblioteca le asignará al thread
             // los atributos por defecto.
        //void * (*start_routine) (void *):  dirección de memoria de la función que ejecutará la hebra
        //void *arg: argumentos que se le pasan a la función que ejecutará la hebra
        //En caso de que todo haya ido bien, la función devuelve un 0, o un valor distinto de 0 en caso de que hubiera algún error. 
    }
    float *valorRecogido, suma_final=0;
    for(int i=0; i<n; i++){        
        printf("Proceso principal: Hilo creado, esperando su finalizacion desde el main()...\n");
        if(pthread_join(thread[i], (void **) &valorRecogido) != 0){
            printf("Error en la espera de la hebra\n");
            exit(EXIT_FAILURE);
        }
        suma_final += *valorRecogido;
        //pthread_join (pthread_t th, void **thread_return)
        //pthread_t th: id de la hebra
        //void **thread_return: apunta al resultado devuelto por la hebra
        //Esta función devuelve 0 si todo está correcto, o valor diferente de 0 si hubo algún error
        //El join sirve para esperar a los hilos -> es como usar un wait
    }
    printf("La suma final es %f\n", suma_final);
    free(valorRecogido);
    exit(EXIT_SUCCESS);
}