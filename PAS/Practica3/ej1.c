#include <stdio.h> //librería estándar de C
#include <stdlib.h> //EXIT_FAILURE & SUCCESS, stderr
#include <unistd.h> //librería estándar POSIX: getopt, optarg, opterr, optind, getuid
#include <getopt.h> //
#include <pwd.h> //struct passwd: getpwuid, getpwnam
/*
 char    *pw_name   User's login name. 
 uid_t    pw_uid    Numerical user ID. 
 gid_t    pw_gid    Numerical group ID. 
 char    *pw_dir    Initial working directory. 
 char    *pw_shell  Program to use as shell.
*/
#include <grp.h> //group structure: endgrent, getgrent, setgrent, getgrgid
/*
 char   *gr_name The name of the group. 
 gid_t   gr_gid  Numerical group ID.s
 char  **gr_mem  Pointer to a null-terminated array of character pointers to member names. 
*/
#include <string.h> //string operations
#include <stdbool.h> //booleanos en C
#include <ctype.h> //character types: isdigit

void print_help(){
    printf("Uso del programa: ej1 [Opciones]\n"
            "Opciones:\n"
            "-h, --help: Ayuda del programa\n"
            "-u, --user <uid o nombre de usuario>: Información sobre el usuario\n"
            "-a, --active: Información sobre el usuario activo actual\n"
            "-m, --maingroup: Además de infomación de usuario, imprime la información de su grupo principal\n"
            "-g, --group  <gid o nombre de grupo>: Información sobre el grupo\n"
            "-s, --allgroups: Muestra información de todos los grupos del sistema\n");
}

void print_user_info(struct passwd *pw, bool main_group) {
    printf("Usuario:\n");
    printf("Nombre: %s\n", pw->pw_gecos); 
    printf("Login: %s\n", pw->pw_name);
    printf("Password: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Home: %s\n", pw->pw_dir);
    printf("Shell: %s\n", pw->pw_shell);
    printf("Número de grupo principal: %d\n", pw->pw_gid);
    if(main_group == true){
        struct group *gr = getgrgid(pw->pw_gid); //def in .h
        //Se llama a getgrgid(pw->pw_gid) para obtener una estructura group 
         // que contiene información sobre el grupo principal del usuario.
        if (gr != NULL) {
            printf("Nombre del grupo principal: %s\n", gr->gr_name);
        }
    }
}
/*
 pw_gecos: nombre completo del usuario.
 pw_name: nombre de login del usuario.
 pw_passwd: contraseña del usuario (en sistemas modernos, esto suele ser un placeholder, ya que
                                     las contraseñas reales están en /etc/shadow).
 pw_uid: User ID (UID) del usuario.
 pw_dir: directorio home del usuario.
 pw_shell: shell de login del usuario.
 pw_gid: Group ID (GID) del grupo principal del usuario
*/

void print_group_info(struct group *gr) {
    printf("Grupo:\n");
    printf("Nombre del grupo: %s\n", gr->gr_name);
    printf("GID: %d\n", gr->gr_gid);
    printf("Miembros secundarios:\n");
    char **member = gr->gr_mem; //def in .h
    while (*member != NULL) {
        printf("%s\n", *member);
        member++;
    }
}
/*
 gr: es un puntero a la estructura group que contiene información sobre el grupo.
 gr_name: nombre del grupo.
 gr_gid: Group ID (GID) del grupo.
 char **member = gr->gr_mem; inicializa un puntero member que apunta a la lista de miembros del grupo.
 member++; avanza el puntero al siguiente miembro en la lista.
*/

void print_all_groups() {
    printf("Mostrando información de todos los grupos del sistema:\n");
    setgrent(); //Abre el archivo /etc/group, donde está la info de los grupos
    //Este tipo de llamada prepara al sistema para la lectura secuencial de este archivo
    struct group *gr; //puntero a estructura
    while ((gr = getgrent()) != NULL) {
        print_group_info(gr);
        printf("\n");
    }
    /*
     Mientras getgrent retorne un puntero no nulo. 
     La función getgrent lee la siguiente entrada del archivo /etc/group 
     y devuelve un puntero a una estructura group 
     que contiene la información del grupo
    */
    endgrent(); //Cierra el archivo /etc/group 
    //y limpia cualquier recurso asociado con la lectura del archivo.
}

int main(int argc, char *argv[]) {
    int opt;
    bool active = false;
    bool main_group = false;
    char *user_arg = NULL;
    char *group_arg = NULL;
    /*
     bool name1 = false: bandera booleana que indica si la opción --name1, está activa
     char *name2 = NULL: puntero que almacena el argumento de la opción name2
    */

    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"user", required_argument, NULL, 'u'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"group", required_argument, NULL, 'g'},
        {"allgroups", no_argument, NULL, 's'},
        {0, 0, 0, 0}
    };
    /*
     esta estructura define una lista de opciones aceptadas por el programa
     en general, el formato que usa cada opción es: {"long_name", require_arg, flag, 'value'}
    */

    while((opt = getopt_long(argc, argv, "hu:amg:s", long_options, NULL)) != -1) {
        /*
         getopt_long: sirve para procesar los argumentos de línea de comandos "argv"
                       y además es un identificador de opciones
         hu:amg:s" es una cadena que especifica las opciones cortas aceptadas:
          h: help
          u: user
          a: active
          m: maingroup
          g: group
          s: allgroups
          Los ':' se utilizan después de un caracter para indicar que necesitan un argumento
         long_options: se indica para que getopt pueda usar las long_options
         NULL: indica que getopt_long no utiliza un índice variable.
        */
        switch(opt){
            case 'h': //formato con f(x)
                print_help();
                exit(EXIT_SUCCESS);
            case 'u': //formato char
                user_arg = optarg;
                active = true; //chapuza pero fufa,
                        //habría que hacer un else después del if(active)
                break;
            case 'a': //formato bool
                active = true;
                break;
            case 'm':
                main_group = true;
                break;
            case 'g':
                group_arg = optarg;
                break;
            case 's':
                print_all_groups();
                exit(EXIT_SUCCESS);
            default:
                print_help();
                exit(EXIT_FAILURE);
        }
    }

    if(optind < argc){ //def in .h
    /*
     optind es una variable externa utilizada por getopt y getopt_long. 
     Inicialmente, optind está establecido en 1 
     y se incrementa cada vez que se procesa una opción.
    */
        printf("Argumentos que no son opciones aceptadas por el programa: ");
        while(optind < argc){
            printf("%s ", argv[optind++]);
            /*
             Imprime el argumento actual apuntado por argv[optind] 
             y luego incrementa optind para apuntar al siguiente argumento.
            */
        }
        putchar('\n');
        /*
         Imprime un carácter de nueva línea para terminar la línea 
         de salida después de imprimir todos los argumentos.
        */
    }
    /*
     Este bloque de código permite al programa identificar 
     y mostrar cualquier argumento que no sea una opción 
     es decir, cualquier cosa que no esté precedide por un guión '-'
     Por ejemplo, si el programa se ejecuta con los siguientes argumentos:
     ./ej1 -u username -g groupname arg1 arg2
     Se imprimirá: Argumentos que no son opciones: arg1 arg2 
    */

    if(user_arg == NULL && group_arg == NULL){
        active = true;
        main_group = true;
    }

    if(active == true){
        struct passwd *pw; //puntero a struct def in .h
        if (user_arg == NULL) {
            pw = getpwuid(getuid()); 
            /*
             para obtener la estructura passwd del usuario 
             que ejecuta el programa (el usuario actual). getuid() 
             devuelve el UID del usuario actual.
            */
        }
        else {
            if (isdigit(user_arg[0])){ //comprueba si el 1º caracter un num
                //Si es un num, eso quiere decir que es un id
                pw = getpwuid(atoi(user_arg)); //def in .h
                /*
                 Convierte user_arg a un número entero usando atoi 
                 y llama a getpwuid con este número para obtener la 
                 estructura passwd correspondiente al UID proporcionado.
                */
            }
            else {
                pw = getpwnam(user_arg); //def in .h
                /*
                 Si user_arg no comienza con un dígito, 
                 asume que es un nombre de usuario 
                 y llama a getpwnam con user_arg para 
                 obtener la estructura passwd correspondiente
                 al nombre de usuario.
                */
            }
        }
        if (pw == NULL) {
            fprintf(stderr, "Usuario no encontrado\n"); //def in .h
            exit(EXIT_FAILURE);
        }
        print_user_info(pw, main_group);
    }
    else

    if(group_arg != NULL){
        struct group *gr;
        if (isdigit(group_arg[0])) {
            gr = getgrgid(atoi(group_arg)); //def in .h
        } else {
            gr = getgrnam(group_arg); //def
             //getgrnam sirve para obtener la estructura group correspondiente al nombre de grupo.
        }
        if (gr == NULL) {
            fprintf(stderr, "Grupo no encontrado\n");
            exit(EXIT_FAILURE);
        }
        print_group_info(gr);
    }

    exit(EXIT_SUCCESS);
}
