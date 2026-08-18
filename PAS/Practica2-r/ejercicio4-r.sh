#!/bin/bash

# 1. Listar todos los ficheros ocultos de la carpeta personal del usuario ordenados de menor a mayor número de caracteres.
echo "1) Ficheros ocultos de $HOME ordenados de menor a mayor número de caracteres:"
find "$HOME" -maxdepth 1 -name ".*" -type f | awk -F/ '{print length($NF), $NF}' | sort -n | awk '{print $2}'
# awk -F/ '{print $NF}': Utiliza awk para imprimir solo el nombre del
 # archivo de la ruta completa de cada archivo encontrado. El delimitador de
 # campo (-F/) se establece en "/" para separar la ruta en componentes
 # y $NF se refiere al último campo, que es el nombre del archivo.
# sort -n -k1: Utiliza el comando sort para ordenar los nombres de archivos
 # encontrados numéricamente (-n) en función del primer campo (-k1),
 # es decir, en función del número de caracteres en el nombre del archivo.
echo "----"

# 2. Listar por pantalla todos los procesos que el usuario del sistema está ejecutando en ese momento.
echo "2) Listado de los procesos ejecutados por el usuario $(whoami)"
ps -u $(whoami) -o pid,lstart,cmd --no-headers | sed -r 's/^ *([^ ]+) +([^ ]+ +[^ ]+ +[^ ]+) +([^ ]+) +([^ ]+) +(.+)$/PID: "\1" Hora: "\3" Ejecutable: "\5"/'
# ps -u $(whoami) -o pid,lstart,cmd --no-headers: Utiliza el comando ps para
 # listar los procesos ejecutados por el usuario actual ($(whoami))
 # Los campos incluidos son: pid (identificador del proceso), 
 # lstart (fecha y hora de inicio del proceso) y cmd (comando ejecutado).
 # La opción --no-headers indica que no se incluirá la fila de encabezados
 # en la salida.
 # ps -u $(whoami): Esto muestra los procesos que están siendo ejecutados por
  # el usuario actual.
 # -o pid,lstart,cmd: Esto especifica las columnas que queremos mostrar en la
  # salida. En este caso, estamos mostrando el PID (identificador de proceso),
  # la hora de inicio del proceso y el comando que está siendo ejecutado.
  # --no-headers: Esto evita que se muestren las cabeceras de las columnas en
  # la salida.
 # sed -r: Esto indica que vamos a utilizar expresiones regulares extendidas.
 # 's/^ *([^ ]+) +([^ ]+ +[^ ]+ +[^ ]+) +([^ ]+) +([^ ]+) +(.+)$/PID: "\1"
  # Hora: "\3" Ejecutable: "\5"/': Esta expresión regular busca coincidencias
  # en cada línea de salida de ps. Aquí está lo que hace cada parte:
  # ^ *([^ ]+): Coincide con los espacios al principio de la línea, seguidos
   # por uno o más caracteres que no son espacios. Esto captura el PID del
   # proceso.
  # +([^ ]+ +[^ ]+ +[^ ]+): Coincide con uno o más caracteres que no son
   # espacios, seguidos por dos espacios, tres veces. Esto captura la hora de
   # inicio del proceso.
  # +([^ ]+): Coincide con uno o más caracteres que no son espacios. Esto
   # captura el nombre del ejecutable del proceso.
  # +(.+): Coincide con uno o más caracteres, capturando el comando completo
   # del proceso.
exit 0
: ' 
 4
 grep:
  -i: hace que considere igual mayúsculas y minúsculas.
  -o: en lugar de imprimir las líneas completas que cumplen el
       patrón, solo muestra el emparejamiento del patrón.
  -v: mostrar las líneas que no cumplen el patrón.
  -e: Nos permite especificar varios patrones de búsqueda
 mas opciones en man grep

 Encontrar todos los números con signo 
  (con o sin decimales): [-+][0-9]+(\.[0-9]+)?
 5 cifras decimales o más (sin signo): [0-9]+\.[0-9]{5,}
'