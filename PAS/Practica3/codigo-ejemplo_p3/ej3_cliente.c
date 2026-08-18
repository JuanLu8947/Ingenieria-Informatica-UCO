/*
Cliente que envia por una cola abierta para escritura una cadena de caracteres
recogida por teclado, mientras que el valor de esa cadena sea distinto a la palabra exit
*/

#include "ej3_common.h"
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>

// Prototipo de funcion
void funcionLog(char *);
// Apuntador al fichero de log. No se usa en este ejemplo, pero le servira en ejercicio resumen
FILE *fLog = NULL;

mqd_t mq_server;	// Cola del servidor
mqd_t mq_client;	// Cola del cliente

void funcionSennal(int signal){
	char mensaje[MAX_msg];
	printf("He recibido la señal %d\n", signal);
	sprintf(mensaje, "He recibido la señal %d\n", signal);
	funcionLog(mensaje);
    /*
    Imprime el número de señal recibido, almacena el mensaje
     en el buffer mensaje y llama a funcionLog para registrar
      el mensaje.
    */

	if(mq_send(mq_server, MSG_STOP, MAX_SIZE, 0) != 0){
		perror("Error al enviar el mensaje");
		funcionLog("Error al enviar el mensaje");
        exit(-1);
	}
    /*
    Envia un mensaje de parada MSG_STOP a la cola del
     servidor mq_server. Si ocurre un error, imprime un mensaje
      de error, registra el error con funcionLog y termina el
       programa con exit(-1).
    */

	if(mq_send(mq_client, MSG_STOP, MAX_SIZE, 0) != 0){
		perror("Error al enviar el numero de caracteres del mensaje");
		funcionLog("Error al enviar el numero de caracteres del mensaje");
        exit(-1);
	}
    /*
    Envia un mensaje de parada MSG_STOP a la cola del
     cliente mq_client. Si ocurre un error, imprime un mensaje
      de error, registra el error con funcionLog y termina el
       programa con exit(-1).
    */

	printf("Enviado mensaje de parada al servidor");
	funcionLog("Enviado mensaje de parada al servidor");

	if (mq_close(mq_server) == (mqd_t)-1) {
        perror("Error al cerrar la cola del servidor");
        exit(-1);
    }
    /*
    Intenta cerrar la cola de mensajes del servidor mq_server.
     Si ocurre un error, imprime un mensaje de error y termina
      el programa con exit(-1)
    */

	if (mq_close(mq_client) == (mqd_t)-1) {
        perror("Error al cerrar la cola del cliente");
        exit(-1);
    }
    /*
    Intenta cerrar la cola de mensajes del cliente mq_client.
     Si ocurre un error, imprime un mensaje de error y termina
      el programa con exit(-1)
    */

	printf("Cola cerrada");
	funcionLog("Cola cerrada");
}
/*
Esta función maneja una señal específica al recibirla.
·Imprime y registra el número de señal recibida.
·Envía un mensaje de parada a las colas de mensajes del servidor y del cliente.
·Registra el envío de los mensajes de parada.
·Cierra las colas de mensajes del servidor y del cliente.
·Registra el cierre de las colas.
*/

int main(int argc, char **argv) {
	signal(SIGTERM, &funcionSennal); //kill
	signal(SIGINT, &funcionSennal); //Crtl + c
    /*
    Se configuran las señales SIGTERM y SIGINT para que, cuando
     el programa las reciba, se llame a la función funcionSennal.
    */

    char buffer[MAX_SIZE];	// Buffer para intercambiar mensajes
	char caracteres[MAX_SIZE];
	char mensaje[MAX_msg];
    char serverQueue[100];	// Nombre para la cola del servidor
    char clientQueue[100];	// Nombre para la cola del cliente
	int must_stop = 0;

    // Abrir la cola del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen.
    // No es necesario crearla si se lanza primero el servidor, sino el programa no funciona.


    // Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola de servidor es: %s\n", serverQueue);

    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola de cliente es: %s\n", clientQueue);
    /*
    Se construyen los nombres de las colas del servidor 
     y del cliente, incorporando el nombre de usuario
      para que sean únicas.
    */

    mq_server = mq_open(serverQueue, O_WRONLY);
    // mq_server = mq_open(SERVER_QUEUE, O_WRONLY);
    if (mq_server == (mqd_t)-1) {
        perror("Error al abrir la cola del servidor");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola de servidor es: %d\n", (int)mq_server);

	mq_client = mq_open(clientQueue, O_RDONLY);
    if (mq_client == (mqd_t)-1) {
        perror("Error al abrir la cola del cliente");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola de cliente es: %d\n", (int)mq_client);
    /*
    Se abren las colas del servidor y del cliente.
     La cola del servidor se abre para escritura 
      y la cola del cliente para lectura. 
       Si ocurre un error al abrir cualquiera de las colas, 
        se imprime un mensaje de error y el programa termina.
    */

    printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
    do {
        printf("> ");

        /* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
        It stops when either (n-1) characters are read, the newline character is read,
        or the end-of-file is reached, whichever comes first.
        Automáticamente fgets inserta el fin de cadena '\0'
        */
        fgets(buffer, MAX_SIZE, stdin);

        // Enviar y comprobar si el mensaje se manda
        if (mq_send(mq_server, buffer, MAX_SIZE, 0) != 0) {
            perror("Error al enviar el mensaje");
            exit(-1);
        }

        //strncmp: se utiliza para comparar el contenido del
         // buffer con el valor de MSG_STOP
		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0){
            must_stop = 1;
		}
		else{
			ssize_t bytes_read;
            //bytes_read se declara como una variable de tipo
             // ssize_t para almacenar el número de bytes leídos
              // por la función mq_receive.
			bytes_read = mq_receive(mq_client, caracteres, MAX_SIZE, NULL);
			if (bytes_read < 0) {
				perror("Error al recibir el mensaje");
				exit(-1);
			}
            /*
            La función mq_receive se usa para recibir un mensaje de
             la cola de mensajes referenciada por mq_client.
             Los parámetros son:
             ·mq_client: Descriptor de la cola de mensajes
               desde la cual se va a recibir el mensaje.
             ·caracteres: Buffer donde se almacenará el
               mensaje recibido.
             ·MAX_SIZE: Tamaño máximo del mensaje que se
               espera recibir.
             ·NULL: Prioridad del mensaje (si no se
               requiere información de prioridad, se pasa NULL).
             ·mq_receive devuelve el número de bytes leídos,
               o -1 en caso de error.
            */
			printf("Recibido el mensaje: %s\n", caracteres);
			sprintf(mensaje, "Recibido el mensaje: %s\n", caracteres);
			funcionLog(mensaje);
		}
        // Iterar hasta escribir el código de salida
    } while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));
    /*
    El programa solicita al usuario que ingrese mensajes.
     Cada mensaje se envía al servidor usando mq_send.
      Si el mensaje es el comando de parada (MSG_STOP),
       se establece must_stop en 1 y se sale del bucle.
        De lo contrario, el programa espera un mensaje de
         respuesta del servidor con mq_receive, lo imprime 
          y lo registra en el log.
    */

    // Cerrar la cola del servidor
    if (mq_close(mq_server) == (mqd_t)-1) {
        perror("Error al cerrar la cola del servidor");
        exit(-1);
    }
	if (mq_close(mq_client) == (mqd_t)-1) {
        perror("Error al cerrar la cola del cliente");
        exit(-1);
    }
    return 0;
}
/*
Este programa cliente realiza las siguientes acciones:
·Configura el manejo de señales para SIGTERM y SIGINT.
·Define buffers y construye nombres únicos para las colas de
 mensajes del servidor y del cliente.
·Abre las colas de mensajes del servidor y del cliente.
·Permite al usuario enviar mensajes al servidor y recibir
 respuestas, registrando los mensajes en un archivo de log.
·Cierra las colas de mensajes al finalizar.
Este diseño permite una comunicación síncrona entre un cliente
 y un servidor mediante colas de mensajes, con manejo de
  errores y registro de actividades en un log.
*/

/* Función auxiliar, escritura de un log.
No se usa en este ejemplo, pero le puede servir para algun
ejercicio resumen */
void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-cliente.txt");
    if (fLog == NULL) {
        fLog = fopen(nombreFichero, "at");
        if (fLog == NULL) {
            perror("Error abriendo el fichero de log");
            exit(1);
        }
    }
    /*
    El nombre del archivo de log se establece como
     "log-cliente.txt". Si el archivo fLog no está abierto
      (fLog == NULL), se intenta abrir el archivo en modo de
       adición ("at"). Si la apertura falla, se imprime un
        mensaje de error y el programa termina con exit(1).
    */

    // Obtener la hora actual
    t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);
    /*
    La hora actual se obtiene usando time(NULL), y se convierte
     en una estructura tm con localtime. Luego, se formatea la
      hora y la fecha en el buffer mensajeAEscribir con
       strftime, en el formato [YYYY-MM-DD, HH:MM:SS].
    */

    // Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensajeAEscribir + strlen(mensajeAEscribir), " ==> %s\n", mensaje);
    /*
    Se añade el mensaje recibido como argumento a
     mensajeAEscribir, después de la marca de tiempo. 
      Esto incluye el mensaje en el formato:
       [YYYY-MM-DD, HH:MM:SS] ==> mensaje\n.
    */

    // Escribir finalmente en el fichero
    resultado = fputs(mensajeAEscribir, fLog);
    if (resultado < 0)
        perror("Error escribiendo en el fichero de log");
    /*
    El mensaje formateado se escribe en el archivo de log
     usando fputs. Si la escritura falla 
     (es decir, resultado < 0), se imprime un mensaje de error.
    */

    fclose(fLog);
    fLog = NULL;
}
/*
La función funcionLog realiza las siguientes acciones:
·Abre el archivo de log log-cliente.txt en modo de adición.
·Obtiene la hora y la fecha actuales y las formatea.
·Incluye el mensaje recibido junto con la marca de tiempo en el mensaje formateado.
·Escribe el mensaje formateado en el archivo de log.
·Cierra el archivo de log.
·Si ocurre cualquier error durante la apertura o la escritura
 en el archivo, la función imprime un mensaje de error y
  termina el programa.
*/