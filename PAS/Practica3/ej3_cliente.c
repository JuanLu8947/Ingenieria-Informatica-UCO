//COMPILAR: gcc ej3_cliente.c -o client -lrt
/*
Cliente que envia por una cola abierta para escritura una cadena de caract
recogida por teclado, mientras que el valor de esa cadena sea distinto a la palabra exit
*/

#include "ej3_common.h" //MAX & MSG_SIZE, SERVER & CLIENT_QUEUE, MSG_STOP
#include <errno.h> //macros para errores
#include <mqueue.h> //colas mensajes POSIX: mq_close, open, unlink, send, mqd_t
#include <stdio.h> //f(x) salida y entrada: sprintf,
#include <stdlib.h> //gestión de memoria y control de procesos: getenv()
#include <string.h> //manipulación de cadenas: strlen, strncmp
#include <sys/stat.h> //
#include <sys/types.h> //
#include <time.h> //time_t, localtime, strftime
#include <signal.h> //manejar señales

FILE *fileLog = NULL;

mqd_t mq_server; //Cola del servidor
mqd_t mq_client; //Cola del cliente

void funcionLog(char *); //el prototipo de f(x) debe de estar aquí

void handle_signal(int signal){
	char mensaje[MAX_MSG];
	printf("He recibido la señal %d\n", signal);
	sprintf(mensaje, "He recibido la señal %d\n", signal);
    //sprintf en vez de mostrar el mensaje por consola,
     //lo guarda en mensaje y lo manda a la siguiente f(x)
	funcionLog(mensaje);
    /*
    Imprime el número de señal recibido, almacena el mensaje
     en el buffer mensaje y llama a funcionLog para registrar
      el mensaje.
    */

    /*int mq_send(mqd_t , const char *, size_t , unsigned int );
     mqd_t: Es el descriptor de la cola de mensajes. Se obtiene al abrir o crear una cola de mensajes mediante mq_open
     const char *: Es un puntero al buffer que contiene el mensaje que se va a enviar.
     size_t: longitud del msg en bits
     unsigned int: Es la prioridad del mensaje. Las colas de mensajes de POSIX permiten especificar prioridades para los mensajes, donde un número mayor indica una mayor prioridad.
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
		perror("Error al enviar el numero de caract del mensaje");
		funcionLog("Error al enviar el numero de caract del mensaje");
        exit(-1);
	}
    /*
    Envia un mensaje de parada MSG_STOP a la cola del
     cliente mq_client. Si ocurre un error, imprime un mensaje
      de error, registra el error con funcionLog y termina el
       programa con exit(-1).
    */

	printf("Enviado mensaje de parada al servidor");
	funcionLog("Enviado mensaje de parada al servidor"); //mq-close

	if(mq_close(mq_server) == (mqd_t)-1){ 
        //(mqd_t)-1 asegura que el tipo de -1 coincide con el tipo mqd_t
        perror("Error al cerrar la cola del servidor");
        exit(-1);
    }
    /*
    Intenta cerrar la cola de mensajes del servidor mq_server.
     Si ocurre un error, imprime un mensaje de error y termina
      el programa con exit(-1)
    */

	if(mq_close(mq_client) == (mqd_t)-1){
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

int main(int argc, char **argv){
	signal(SIGTERM, &handle_signal); //kill
	signal(SIGINT, &handle_signal); //Crtl + c
    /*
    Se configuran las señales SIGTERM y SIGINT para que, cuando
     el programa las reciba, se llame a la función handle_signal.
    */

    char buffer[MAX_SIZE]; //Buffer para intercambiar mensajes
	char caract[MAX_SIZE]; //
	char mensaje[MAX_MSG]; //Buffer para almacenar el mensaje
    char serverQueue[100]; //Nombre para la cola del servidor
    char clientQueue[100]; //Nombre para la cola del cliente
	int byte_stop = 0; //

    // Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    //getenv(""): nos da el usuario actual //def in .h
    /*int sprintf(char *, const char *, ...): def in .h
     char *: es el buffer donde se alamacenará const char *
     const char *: es una cadena que indica el formato
     Y los siguientes argumentos son los valores que se insertan en la cadena
    */
    printf("[Cliente]: El nombre de la cola de servidor es: %s\n", serverQueue);

    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola de cliente es: %s\n", clientQueue);
    /*
    Se construyen los nombres de las colas del servidor 
     y del cliente, incorporando el nombre de usuario
      para que sean únicas.
    */

    mq_server = mq_open(serverQueue, O_WRONLY);
    /*mqd_t mq_open(const char *, int );
     const char *: nombre de la cola de mensajes
     int: Especifica el modo de apertura de la cola. 
      O_RDONLY para lectura, 
      O_WRONLY para escritura,
      O_RDWR para ambos.
    */
    if(mq_server == (mqd_t)-1){
        perror("Error al abrir la cola del servidor");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola de servidor es: %d\n", (int)mq_server);
    //en este printf, mq_server pasa de ser de tipo mqd_t a ser int

	mq_client = mq_open(clientQueue, O_RDONLY);
    if(mq_client == (mqd_t)-1){
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
    //MSG_STOP = "exit"
    do{
        printf("> ");

        /*fgets lee de la siguiente manera:
        Lee hasta los n-1 caract, hasta que lea la siguiente línea,
        o hasta que llegue al final de un archivo.
        Además, automáticamente fgets inserta el fin de cadena '\0'
        En este caso: se utiliza para leer una línea de texto desde un flujo de entrada que es stdin (la entrada estándar)
        */
        fgets(buffer, MAX_SIZE, stdin);

        // Enviar y comprobar si el mensaje se manda
        if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0){
            perror("Error al enviar el mensaje");
            exit(-1);
        }

        //strncmp: se utiliza para comparar el contenido del
         // buffer con el valor de MSG_STOP, hasta 'MSG_STOP' caract
		if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0){
            byte_stop = 1;
		}
		else{
			ssize_t n_bytes;
            //n_bytes se declara como una variable de tipo
             // ssize_t para almacenar el número de n_bytes leídos
              // por la función mq_receive.
			n_bytes = mq_receive(mq_client, caract, MAX_SIZE, NULL);
			if(n_bytes < 0){
				perror("Error al recibir el mensaje");
				exit(-1);
			}
            /*
            La función mq_receive se usa para recibir un mensaje de
             la cola de mensajes referenciada por mq_client.
             Los parámetros son:
             ·mq_client: Descriptor de la cola de mensajes
               desde la cual se va a recibir el mensaje.
             ·caract: Buffer donde se almacenará el
               mensaje recibido.
             ·MAX_SIZE: Tamaño máximo del mensaje que se
               espera recibir.
             ·NULL: Prioridad del mensaje (si no se
               requiere información de prioridad, se pasa NULL).
             ·mq_receive devuelve el número de n_bytes leídos,
               o -1 en caso de error.
            */
			printf("Recibido el mensaje: %s\n", caract);
			sprintf(mensaje, "Recibido el mensaje: %s\n", caract);
			funcionLog(mensaje);
		}
        // Iterar hasta escribir el código de salida
    } while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));
    /*
    El programa solicita al usuario que ingrese mensajes.
     Cada mensaje se envía al servidor usando mq_send.
      Si el mensaje es el comando de parada (MSG_STOP),
       se establece byte_stop en 1 y se sale del bucle.
        De lo contrario, el programa espera un mensaje de
         respuesta del servidor con mq_receive, lo imprime 
          y lo registra en el log.
    */

    // Cerrar la cola del servidor
    if(mq_close(mq_server) == (mqd_t)-1){
        perror("Error al cerrar la cola del servidor");
        exit(-1);
    }
	if(mq_close(mq_client) == (mqd_t)-1){
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

// Función escritura de log.
void funcionLog(char *mensaje){
    int resultado;
    char nombreFich[100], mensaje_A_Escribir[300];
    time_t t; //def in .h

    // Abrir el fichero
    sprintf(nombreFich, "log-cliente.txt");
    //en lugar de imprimir por consola, almacena el texto en una cadena de caract.
    if(fileLog == NULL){
        //fileLog = fopen(nombreFich, "at"); //at: adición de fopen
        if((fileLog = fopen(nombreFich, "at")) == NULL){
            perror("Error abriendo el fichero de log");
            exit(1);
        }
    }
    /*
    El nombre del archivo de log se establece como
     "log-cliente.txt". Si el archivo fileLog no está abierto
      (fileLog == NULL), se intenta abrir el archivo en modo de
       adición ("at"). Si la apertura falla, se imprime un
        mensaje de error y el programa termina con exit(1).
    */

    t = time(NULL); //devuelve el tiempo actual en segundos 
    struct tm *p = localtime(&t); //def in .h
    /*
     localtime(&t): convierte el valor de time_t apuntado por t en una estructura tm que representa el tiempo local.
     struct tm es una estructura que contiene campos como el año, mes, día, hora, minuto y segundo
     p es un puntero a la estructura tm que contiene la fecha y hora local que se va a formatear.
    */
    strftime(mensaje_A_Escribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p); //def in .h
    /*
    La hora actual se obtiene usando time(NULL), y se convierte
     en una estructura tm con localtime. Luego, se formatea la
      hora y la fecha en el buffer mensaje_A_Escribir con
       strftime, en el formato [YYYY-MM-DD, HH:MM:SS].
    //size_t strftime(char *, size_t , const char *, const struct tm *);
     char *: Un puntero al buffer donde se almacenará la cadena resultante.
     size_t: El tamaño máximo del buffer, para evitar desbordamientos.
     const char *: define cómo se debe formatear la fecha y la hora.
     const struct tm *: Un puntero a una estructura tm que contiene los componentes de la fecha y hora a formatear.
    */

    // Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensaje_A_Escribir + strlen(mensaje_A_Escribir), " ==> %s\n", mensaje);
    /*
    Se añade el mensaje recibido como argumento a
     mensaje_A_Escribir, después de la marca de tiempo. 
      Esto incluye el mensaje en el formato:
       [YYYY-MM-DD, HH:MM:SS] ==> mensaje\n.
    //int sprintf(char *str, const char *format, ...);
     char *str = mensaje_A_Escribir + strlen(mensaje_A_Escribir)
     const char *format = " ==> %s\n"
     ... : Los argumentos que se van a formatear según la cadena de formato.
    */

    // Escribir finalmente en el fichero
    resultado = fputs(mensaje_A_Escribir, fileLog);
    /*int fputs(const char *, FILE *);
     const char *: puntero a la cadena de caracteres que se va a escribir
     FILE *: puntero al archivo donde se escribirá la cadena.
    */
    if(resultado < 0)
        perror("Error escribiendo en el fichero de log");
    /*
    El mensaje formateado se escribe en el archivo de log
     usando fputs. Si la escritura falla 
     (es decir, resultado < 0), se imprime un mensaje de error.
    */

    fclose(fileLog);
    fileLog = NULL;
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
