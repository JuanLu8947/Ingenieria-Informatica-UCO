#!/bin/bash

# Comprobación de argumentos
if [ "$#" -ne 1 ]; then
    echo "Argumentos incorrectos. Uso: ./ejercicio6.sh </bin/bash>"
    exit 1
fi

shell="$1"

# Obtener usuarios con la shell especificada
usuarios=$(awk -F ':' -v shell="$shell" '$NF == shell {print $1}' /etc/passwd)
# awk usca usuarios cuyo tipo de shell coincida con el valor de la variable
 # $shell y devuelve sus nombres de usuario.
 # -F ':': Especifica que el delimitador de campos en el archivo es el
 # carácter ":".
 # v shell="$shell": Define una variable shell en awk con el valor de la
 # variable de shell de entrada $shell.
 # $NF == shell {print $1}': verifica si el último campo de la línea es
 # igual al valor de la variable shell. 

# Recorrer cada usuario y mostrar su información
for usuario in $usuarios; do
    uid=$(grep "^$usuario:" /etc/passwd | cut -d ':' -f3)
    gid=$(grep "^$usuario:" /etc/passwd | cut -d ':' -f4)
    grupo_primario=$(grep ":$gid:" /etc/group | cut -d ':' -f1)
    shell_por_defecto=$(grep "^$usuario:" /etc/passwd | cut -d ':' -f7)

    echo "========="
    echo "Logname: $usuario"
    echo "->UID: $uid"
    echo "->Grupo: $grupo_primario"
    echo "->GID: $gid"
    echo "->Shell por defecto: $shell_por_defecto"
done
# uid=$(grep "^$usuario:" /etc/passwd | cut -d ':' -f3): Busca en el archivo
 # /etc/passwd la línea que comienza con el nombre de usuario actual
 # ($usuario). Luego, utiliza cut para extraer el tercer campo (el UID) de
 # esa línea y lo almacena en la variable uid.
# gid=$(grep "^$usuario:" /etc/passwd | cut -d ':' -f4): extrae el cuarto
 # campo (el GID) de la línea correspondiente al usuario actual y lo almacena
 # en la variable gid.
# grupo_primario=$(grep ":$gid:" /etc/group | cut -d ':' -f1): Busca en el
 # archivo /etc/group la línea que contiene el GID del usuario actual. Luego,
 # utiliza cut para extraer el primer campo (el nombre del grupo) de esa
 # línea y lo almacena en la variable grupo_primario.
# shell_por_defecto=$(grep "^$usuario:" /etc/passwd | cut -d ':' -f7): extrae
 # el séptimo campo (el tipo de shell) de la línea correspondiente al usuario
 # actual y lo almacena en la variable shell_por_defecto.

exit 0
