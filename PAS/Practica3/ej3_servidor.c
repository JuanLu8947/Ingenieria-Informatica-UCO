//COMPLIAR CON: gcc ej3_servidor.c -o server -lrt
/*
Servidor que lee de una cola abierta para lectura una cadena de caracteres y la
imprime por pantalla.
Lo hace mientras que el valor de esa cadena sea distinto a la palabra exit.

//La mayoría de cosas están eexplicdas en cliente

*/

#include "ej3_common.h" //MAX & MSG_SIZE, SERVER & CLIENT_QUEUE, MSG_STOP
#include <errno.h> //macros para errores
#include <mqueue.h> //colas mensajes POSIX: mqd_t, mq_attr, close, unlink, receive
/*
 struct mq_attr {
    long mq_flags;    //Flags: 0 o O_NONBLOCK
    long mq_maxmsg;   //Número máximo de mensajes en la cola
    long mq_msgsize;  //Tamaño máximo de cada mensaje
    long mq_curmsgs;  //Número actual de mensajes en la cola
 };
*/
#include <stdio.h> //f(x) salida y entrada: 
#include <stdlib.h> //gestión de memoria y control de procesos getenv()
#include <string.h> //manipulación de cadenas: 
#include <sys/stat.h> //
#include <sys/types.h> //ssize_t
#include <time.h> //

//El prototipo de esta f(x) debe ser la 1º ya que se llama en las de después
void funcionLog(char *);
//Apuntador al fichero de log.  No se usa en este ejemplo, pero le servira en ejercicio resumen
FILE *fileLog = NULL;

mqd_t mq_server; //Cola del servidor
mqd_t mq_client; //Cola del cliente
char serverQueue[100]; //Nombre para la cola del servidor
char clientQueue[100]; //Nombre para la cola del cliente

/* void handle_signal(int signal){ //en server no se usa
	printf("He recibido la señal %d, procedo a cerrar y eliminar la cola\n", signal);

	if(mq_close(mq_server) == (mqd_t)-1){ //cierre de la cola server
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}
	if(mq_close(mq_client) == (mqd_t)-1){ //-1 pasa de int a tipo mqd_t
		perror("Error al cerrar la cola del cliente");
		exit(-1);
	}

	if(mq_unlink(serverQueue) == (mqd_t)-1){ //desvinculación con el servidor
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}
    /*
    Elimina la cola de mensajes del servidor especificada
     por serverQueue.
    Si ocurre un error al eliminar la cola, imprime un mensaje
     de error usando perror y finaliza el programa con exit(-1).
    */ /*
	if(mq_unlink(clientQueue) == (mqd_t)-1){
		perror("Error al eliminar la cola del cliente");
		exit(-1);
	}
    /*
    Elimina la cola de mensajes del cliente especificada
     por clientQueue.
    Si ocurre un error al eliminar la cola, imprime un mensaje
     de error usando perror y finaliza el programa con exit(-1).
    
}*/
/*
La función handle_signal está diseñada para:
·Imprimir un mensaje cuando se recibe una señal.
·Cerrar las colas de mensajes del servidor y del cliente.
·Eliminar (desvincular) las colas de mensajes del servidor
  y del cliente.
·Manejar errores en cada paso, imprimiendo mensajes de error
  y terminando el programa si ocurre algún problema.
Esta función asegura que los recursos de las colas de mensajes
 se liberen adecuadamente cuando el proceso recibe una señal
  (como SIGTERM o SIGINT), evitando así posibles fugas de
   recursos o problemas con colas de mensajes sin eliminar.
*/

int main(int argc, char **argv){
	struct mq_attr attr; //Atributos de la cola
    char buffer[MAX_SIZE]; //Buffer para intercambiar mensajes
	char caracteres[MAX_SIZE]; //Buffer para almacenar los carateres del mensaje
	int longitud; //
	char mensaje[MAX_MSG]; //Buffer para almacenar el mensaje
    int byte_stop = 0; //flag que indica cuando hay que parar. (se escribe palabra exit)
    /*
    Se declaran variables para almacenar atributos de la cola,
     buffers para mensajes, y una bandera (byte_stop) para
      indicar cuándo detener el bucle principal.
    */

    //Inicializamos los atributos de la cola //def in .h
    attr.mq_maxmsg = 10; //Maximo número de mensajes
    attr.mq_msgsize = MAX_SIZE; //Maximo tamaño de un mensaje
    /*
    Se configuran los atributos de la cola: máximo número de
     mensajes y tamaño máximo de cada mensaje.
    */

    //Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER")); //client
    printf("[Servidor]: El nombre de la cola de servidor es: %s\n", serverQueue);

	sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Servidor]: El nombre de la cola de cliente es: %s\n", clientQueue);
    /*
    Se crean nombres únicos para las colas del servidor y del
     cliente usando el login del usuario.
    */

    //Crear la cola de mensajes del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
    mq_server = mq_open(serverQueue, O_CREAT | O_RDONLY, 0644, &attr);
    /*
     O_CREAT | O_RDONLY: son flags de apertura. 
      O_CREAT se utiliza para crear la cola de mensajes si no existe.
      O_RDONLY se utiliza para abrir la cola de mensajes en modo de sólo lectura.
     0644: Es el modo de acceso de los permisos para la cola de mensajes creada. En este caso, se especifica en formato octal.
     &attr: Es un puntero a una estructura mq_attr que contiene atributos de configuración para la cola de mensajes.
    //mqd_t mq_open(const char *, int , mode_t , struct mq_attr *);
     const char *: nombre de la cola de mensajes.
     int: Es una combinación de los flags de apertura, como O_CREAT, O_RDONLY, O_WRONLY, O_RDWR, etc.
     mode_t: Especifica los permisos para la cola de mensajes si se crea (O_CREAT). Debe estar en formato octal.
     struct mq_attr *: Es un puntero a una estructura mq_attr que contiene atributos de configuración para la cola de mensajes, como el tamaño máximo de los mensajes y el número máximo de mensajes en la cola.
    */
	if(mq_server == (mqd_t)-1){
        perror("Error al abrir la cola del servidor");
        exit(-1);
    }
	printf("[Servidor]: El descriptor de la cola de servidor es: %d\n", (int)mq_server); //pasa de mqd_t a int

	//Crear la cola de número de caracteres de mensajes
	mq_client = mq_open(clientQueue, O_CREAT | O_WRONLY, 0644, &attr); //same as client
	if(mq_client == (mqd_t)-1){
        perror("Error al abrir la cola del cliente");
        exit(-1);
    }

    printf("[Servidor]: El descriptor de la cola de cliente es: %d\n", (int)mq_client);
    /*
    Se crean y abren las colas de mensajes para el servidor
     y el cliente. Si hay errores, se imprime un mensaje
      de error y se finaliza el programa.
    */    
    
    do {
        //Número de bytes leidos
        ssize_t bytes_read; //.h

        //Recibir el mensaje
        bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);
        /*ssize_t mq_receive(mqd_t , char *, size_t , unsigned *);
         mqd_t: Descriptor de la cola de mensajes desde la cual se va a recibir el mensaje.
         char *: Es un puntero al buffer donde se almacenará el mensaje recibido.
         size_t: Es el tamaño máximo del mensaje que se espera recibir.
         unsigned *: Es un puntero a una variable de tipo unsigned int donde se almacenará la prioridad del mensaje recibido. Si no se requiere información sobre la prioridad del mensaje, se puede pasar NULL.
        */
        
        //Comprar que la recepción es correcta (bytes leidos no son negativos)
        if(bytes_read < 0){
            perror("Error al recibir el mensaje");
            exit(-1);
        }
        /*
        En cada iteración del bucle do-while, se declara una
         variable bytes_read de tipo ssize_t para almacenar el
          número de bytes leídos al recibir el mensaje.
        Se utiliza mq_receive para recibir un mensaje de la cola
         mq_server y almacenarlo en el buffer buffer de tamaño
          máximo MAX_SIZE.
        Se verifica si la recepción del mensaje fue exitosa. 
         Si bytes_read es menor que 0, indica un error al recibir
          el mensaje y se muestra un mensaje de error usando perror antes de salir del programa con exit(-1).
        */
        //Cerrar la cadena
        //buffer[bytes_read] = '\0';

        //Comprobar el fin del bucle
        if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0){ //client
            byte_stop = 1;
		}
        /*
        Después de recibir el mensaje correctamente, se compara
         el contenido de buffer con MSG_STOP usando strncmp para
          determinar si se debe detener el bucle.
        Si el mensaje recibido es igual a MSG_STOP, se establece
         la variable byte_stop a 1, indicando que el bucle debe
          finalizar.
        */
        else{
            printf("Recibido el mensaje: %s", buffer);
            sprintf(mensaje, "Recibido el mensaje: %s\n", buffer);
            /*
             mensaje: Es la cadena de caracteres donde se almacenará el mensaje formateado.
             buffer: Es el contenido del mensaje recibido que se insertará en la cadena de formateo.
            */
			funcionLog(mensaje);

			longitud = strlen(buffer)-1; //strlen devuelve el tamaño de buffer
			sprintf(caracteres, "Número de caracteres recibidos: %d", longitud);
			if(mq_send(mq_client, caracteres, MAX_SIZE, 0) != 0){ //client
            	perror("Error al enviar el mensaje");
            	exit(-1);
        	}
			printf("Enviado al cliente el mensaje: %s\n", caracteres);
		}
        /*
        Si el mensaje recibido no es igual a MSG_STOP, significa
         que se trata de un mensaje normal.
        Se imprime el mensaje recibido en la consola
         usando printf.
        Se genera un nuevo mensaje mensaje utilizando sprintf
         para incluir el contenido del mensaje recibido.
          Este mensaje se pasa a la función funcionLog para
           registrar el mensaje en un archivo de registro.
        Se calcula la longitud del mensaje recibido (longitud)
         restando 1 (para excluir el carácter de nueva línea).
        Se crea un nuevo mensaje caracteres que contiene la
         longitud del mensaje recibido.
        Se utiliza mq_send para enviar este nuevo mensaje
         (caracteres) a la cola mq_client.
        Si hay un error al enviar el mensaje, se muestra un
         mensaje de error usando perror antes de salir del
          programa con exit(-1).
        Finalmente, se imprime en la consola un mensaje
         indicando que el mensaje ha sido enviado al cliente.
        */
    } while (!byte_stop); //Iterar hasta que llegue el código de salida, es decir, la palabra exit
    /*
    En el bucle, el servidor recibe mensajes de la cola del
     servidor (mq_server).
    Si el mensaje recibido es el código de parada (MSG_STOP),
     se establece la bandera byte_stop para detener el bucle.
    Si no, se imprime el mensaje recibido, se registra en un
     log, y se calcula la longitud del mensaje (sin el carácter
      de nueva línea).
    Luego, se envía la longitud del mensaje al cliente usando la
     cola del cliente (mq_client).
    */

    //Cerrar la cola del servidor
    if(mq_close(mq_server) == (mqd_t)-1){
        perror("Error al cerrar la cola del servidor");
        exit(-1);
    }

    //Eliminar la cola del servidor
    if(mq_unlink(serverQueue) == (mqd_t)-1){
        perror("Error al eliminar la cola del servidor");
        exit(-1);
    }

    //Cerrar la cola del cliente
    if(mq_close(mq_client) == (mqd_t)-1){
        perror("Error al cerrar la cola del cliente");
        exit(-1);
    }

    //Eliminar la cola del cliente
    if(mq_unlink(clientQueue) == (mqd_t)-1){
        perror("Error al eliminar la cola del cliente");
        exit(-1);
    }

    return 0;
}
/*
 Este main usa colas de mensajes POSIX para recibir mensajes de un
  cliente, registra estos mensajes en un log, y responde al
   cliente con la longitud del mensaje recibido. Maneja la
    creación, apertura, cierre y eliminación de las colas de
     mensajes, asegurándose de limpiar adecuadamente los
      recursos cuando se recibe una señal de terminación o 
       se detecta una condición de parada.
*/

void funcionLog(char *mensaje){ //igual q client
    int resultado;
    char nombreFich[100], mensaje_A_Escribir[300];
    time_t t;

    //Abrir el fichero
    sprintf(nombreFich, "log-servidor.txt");
    if(fileLog == NULL){
        fileLog = fopen(nombreFich, "at");
        if(fileLog == NULL){
            perror("Error abriendo el fichero de log");
            exit(1);
        }
    }

    //Obtener la hora actual
    t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(mensaje_A_Escribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

    //Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensaje_A_Escribir + strlen(mensaje_A_Escribir), " ==> %s\n", mensaje);

    //Escribir finalmente en el fichero
    resultado = fputs(mensaje_A_Escribir, fileLog);
    if(resultado < 0)
        perror("Error escribiendo en el fichero de log");

    fclose(fileLog);
    fileLog = NULL;
}
