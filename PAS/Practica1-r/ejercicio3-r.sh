#!/bin/bash

#probar ejjs en uco

# Ruta al directorio con los usuarios
ruta_usuarios="$1"  # argv[1]

# Comprobación de argumentos
if [ $# -ne 1 ]; then   # $#: argc  # -ne: not equal
    echo "Uso: $0 <ruta_usuarios>"
    exit 1
fi

# Bucle para recorrer todos los usuarios
# usuario: es una variable
for usuario in $(ls "$ruta_usuarios"); do
    clave_ssh="$ruta_usuarios/$usuario/.ssh/id_rsa"

    # Comprobar si el fichero de clave SSH existe
    if [ -f "$clave_ssh" ]; then
    # -f: sirve para saber si es un fichero
        # Comprobar permisos del directorio .ssh y el home del usuario
        permisos_ssh=$(stat -c %a "$ruta_usuarios/$usuario/.ssh" | cut -c 2-4)
        permisos_home=$(stat -c %a "$ruta_usuarios/$usuario" | cut -c 2-4)
        # stat: para consultar los permisos de un fichero o directorio
        # stat fichero: muestra propiedades sobre un determinado fichero
        # stat -c %a fichero: permite personalizar la salida y obtener
            # diferentes propiedades sobre un fichero

        # Comprobar permisos de la clave privada
        permisos_clave=$(stat -c %a "$clave_ssh" | cut -c 2-4)

        # Verificar si los permisos no son seguros
        if [ "$permisos_ssh" != "00" ] && [ "$permisos_home" != "00" ] && [ "$permisos_clave" != "00" ]; then
            echo "El usuario $usuario tiene una clave privada de SSH en $clave_ssh que no está protegida."
            echo "La clave debe ser accesible únicamente por el propietario."
            echo

            # Crear archivo de advertencia en el escritorio del usuario
            echo "Por favor, asegúrate de que los permisos de tu clave privada SSH estén configurados correctamente." > "$ruta_usuarios/$usuario/Desktop/AVISO_CLAVE_SSH.txt"
        fi
    fi
done
# r w x
# 4 2 1
# 0 0 0
# 700 -> r w x; x: .exe

: ' 
Cambios realizados al fichero:
Se ha eliminado el primer componente de las permisos ya que no nos importa
debido a que el primer nº es para usuario que se ha eliminado con cut -c 2-4
que es un comando que nos deja con los permisos del 2º y el 3º, el segundo nº
es para grupo y el tercero para otros
'

:'
Nota importante: este ejercicio no funciona en windows, tienes que probarlo
en linux/ubuntu o conectandote por ssh a los servidores de la uco
Para pasarte los archivos de las practicas recomiendo es uso de WinSCP
'

: ' 
 3 
 comando 1> salida.txt: la salida estandar de comando se
  escribira en salida.txt y no por pantalla. Sobreescribe el
  contenido del fichero.
 comando 1» salida.txt: igual que >, pero añade el
  contenido al fichero sin sobrescribir.
 comando 2> error.txt: la salida de error de comando se
  escribira en error.txt y no por pantalla. Sobreescribe el
  contenido del fichero.
 comando 2» error.txt: igual que 2>, pero añade el
  contenido al fichero sin sobrescribir.
 
 comando 2>&1: redirecciona la salida de error de comando a
  la salida estandar.
 comando 1>&2: redirecciona la salida estandar de comando
  a la salida de error.
 comando &> todo.txt: redirecciona tanto la salida
  estandar como la de error hacia el fichero todo.txt,
  sobreescribiendo su contenido, y no se muestra por pantalla.
 comando &» todo.txt: redirecciona tanto la salida
  estandar como la de error, lo añade al contenido de
  todo.txt y no se muestra por pantalla.
 
 Es posible redireccionar la entrada estandar (stdin):
  comando < ficheroConDatos.txt.
'