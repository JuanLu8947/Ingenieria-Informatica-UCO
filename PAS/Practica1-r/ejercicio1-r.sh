#!/bin/bash

# Comprobar si se proporcionó un argumento (directorio)
if [ $# -ne 1 ]; then   # $#: argc, $0: argv[0]
    echo "Uso: $0 <directorio>"
    exit
fi

# Obtener el directorio de los ficheros
directorio=$1 #directorio = argv[1]

# Comprobar si el directorio existe
if [ ! -d "$directorio" ]; then # -d: saber si es un directorio  # !: No
    echo "El directorio '$directorio' no existe."
    exit
fi

# Obtener la lista de ficheros de texto en el directorio
#ficheros=$(find "$directorio" -maxdepth 1 -type f -name "*")
ficheros=$(find "$directorio" -type f -name "*") 
# -name *.sh: busca archivos acabados en .sh
#type f: sirve para que sólo busqe archivos regulares es decir que no
    #sean directorios

# Comprobar si hay al menos un fichero en el directorio
if [ -z "$ficheros" ]; then #-z:0 compara que $ficheros no esté vacía
    echo "No se encontraron ficheros de texto en el directorio '$directorio'."
    exit
fi

# Obtener el número de líneas en el primer fichero para verificar que todos tienen el mismo número de líneas
num_lineas=$(wc -l < "$(echo "$ficheros" | head -n 1)")
# wc -l: muestra el nº de lineas de un fichero
# -n 1: sirve para que sólo se acepte 1 caracter de entrada
# head: muestra las primeras lineas de un fichero que son los nº
# |: sirve para evaluar dos valores a la vez
# <: sirve para redireccionar y para ver si algo es menor que

# Iterar sobre cada línea de los ficheros y sumar los valores correspondientes
for ((i = 1; i <= num_lineas; i++)); do
    suma=0
    while IFS= read -r fichero; do  # -r: revisa si se tiene permiso de lectura
        valor=$(sed -n "${i}p" "$fichero")
        suma=$((suma + valor))
    done <<< "$ficheros"
    echo "Asistentes a la sesión $i: $suma"
done
# sed: Es un comando en Unix/Linux utilizado para realizar transformaciones en texto.
# -n:  Es una opción de sed que suprime la salida de las líneas de entrada que sean especificadas
# ${i}p: Es una expresión que se utiliza para indicar a sed que imprima la línea especificada por la variable i. 
 # La variable i contiene un número entero que representa el número de línea que se desea extraer del archivo.
: '
Explicación de este último bucle:
el bucle for empieza desde la primera linea hasta la ultima
con lo que requiere que todos los ficheros tengan el mismo nº de lineas
el bucle while se va a encargar de leer cada linea i de cada fichero
haciendo que se obtenga la suma de personas asistentes a cada sesión
'
#a=$(cat eva head -n 5 | tail -n 1)
: '
 1
 $HOSTNAME: contiene el nombre de la maquina.
 $MACHTYPE: arquitectura.
 $PS1: cadena que codifica la secuencia de caracteres 
  mostrados antes del prompt
   \t: hora.
   \d: fecha.
   \w: directorio actual.
   \h: nombre de la maquina.
   \W: ultima parte del directorio actual.
   \u: nombre de usuario.
 $UID: contiene el id del usuario que no puede ser modificado.
 $SHLVL: contiene el nivel de anidamiento de la shell.
 $RANDOM: numero aleatorio.
 $SECONDS: numero de segundos que bash lleva en marcha.
 
 $#: numero de argumentos de la linea de comandos (argc).
  (Cuenta desde 0.)
 $n: n-esimo argumento de la linea de comandos (argv[n]),
  si n es mayor que 9 utilizar ${n}.
 $*: todos los argumentos de la linea de comandos (como
  una sola cadena).
 $@: todos los argumentos de la linea de comandos (como un
  array).
 $!: pid del ultimo proceso que se lanzo con &.
 $-: opciones suministradas a la shell.
 $?: valor de salida la ultima orden ejecutada (ver exit).
 !$: ultimo argumento del ultimo comando ejecutado.
 !:n: n-esimo argumento del ultimo comando ejecutado.
 
 read -s: no hace echo de la entrada.
 read -nN: solo acepta N caracteres de entrada.
 read -p "mensaje": muestra el mensaje mensaje al pedir
  la informacion al usuario.
 read -tT: acepta la entrada durante un tiempo maximo de
  T segundos.
 
'