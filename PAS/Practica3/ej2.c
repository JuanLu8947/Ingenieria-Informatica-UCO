#include <stdio.h> //librería estándar de C
#include <stdlib.h> //EXIT_FAILURE & SUCCESS, rand
#include <unistd.h> //POSIX: fork, pipe, read()
#include <sys/wait.h>
#include <time.h> //srand(time(NULL))
#include <errno.h>

int main(){
    // Para realizar el fork:
    pid_t pid;
    int status;

    //Controlar los valores devueltos por las funciones (control de errores):
    int resultado;
    
    //Variables que se van leer y escribir de la tubería:
    float numerosAleatorios[2], suma;

    // Descriptor de los dos extremos de la tubería:
    int descript_read_write_pipe[2]; 
    //descript_read_write_pipe[0]: Descriptor de lectura.
    //descript_read_write_pipe[1]: Descriptor de escritura.
    //Ambos descriptores comienzan abiertos
    
    // Creamos la tubería
    resultado = pipe(descript_read_write_pipe);
    if(resultado == -1){
        perror("Error al crear la tubería");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    switch(pid){
        case -1: //Proceso error. Hay un error en la llamada a fork() y
            //sale del proceso y envia el tipo de error
            printf("No se ha podido crear el proceso hijo\n");
            perror("fork error");
            printf("errno %i\n",errno);
            exit(EXIT_FAILURE);
        case 0: // Proceso hijo
            printf("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());
            //ppid es el pid del padre

            close(descript_read_write_pipe[1]); // Cerramos el descriptor de escritura, ya que solo vamos a leer

            // Leemos los dos números aleatorios enviados por el padre
            resultado = read(descript_read_write_pipe[0], numerosAleatorios, sizeof(numerosAleatorios));
            /*
             lee datos del descriptor de lectura de la tubería 
             (descript_read_write_pipe[0]) y los almacena en 
             el arreglo numerosAleatorios.
             //read(int , void *, size_t );
              int: El descriptor de archivo desde el cual se desea leer. 
               En el contexto de tuberías (pipes), este descriptor 
               corresponde al extremo de lectura de la tubería.
              void *: un puntero a buffer donde de se almacenan los datos leídos
               en este caso el buffer es un array de floats
              size_t: nº max de bits q se pueden leer
            */
            if(resultado != sizeof(numerosAleatorios)){
                perror("Error al leer de la tubería");
                exit(EXIT_FAILURE);
            }

            // Calculamos la suma de los dos números
            suma = numerosAleatorios[0] + numerosAleatorios[1];

            printf("[HIJO]: La suma de los números aleatorios es %f\n", suma);

            close(descript_read_write_pipe[0]); // Cerramos el descriptor de lectura
            break;
        default: // Proceso padre
            printf("[PADRE]: Mi PID es %d y el PID de mi hijo es %d\n", getpid(), pid);

            close(descript_read_write_pipe[0]); // Cerramos el descriptor de lectura, ya que solo vamos a escribir

            srand(time(NULL)); // Semilla de los números aleatorios establecida a la hora actual

            // Generamos dos números aleatorios
            numerosAleatorios[0] =(float)rand()/RAND_MAX * 100.0;
            numerosAleatorios[1] =(float)rand()/RAND_MAX * 100.0;
            //RAND_MAX def in .h
            //Genera un nº, lo divide¡ entre RAND_MAX y lo mult por 100

            printf("[PADRE]: Escribo los números aleatorios %.2f y %.2f en la tubería...\n", numerosAleatorios[0], numerosAleatorios[1]);

            // Escribimos los dos números aleatorios en la tubería
            resultado = write(descript_read_write_pipe[1], numerosAleatorios, sizeof(numerosAleatorios));
            /*
              escribe los números aleatorios en el descriptor de 
              escritura de la tubería (descript_read_write_pipe[1]).
            */
            if(resultado != sizeof(numerosAleatorios)){
                perror("Error al escribir en la tubería");
                exit(EXIT_FAILURE);
            }

            close(descript_read_write_pipe[1]); // Cerramos el descriptor de escritura

            // Esperamos al hijo
            wait(&status);

            if(WIFEXITED(status)){
                printf("[PADRE]: Hijo finalizado con estado %d\n", WEXITSTATUS(status));
            } else if(WIFSIGNALED(status)){
                printf("[PADRE]: Hijo finalizado debido a una señal %d\n", WTERMSIG(status));
            }
    }
    exit(EXIT_SUCCESS);
}
