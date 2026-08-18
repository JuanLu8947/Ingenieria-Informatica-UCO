#!/bin/bash

# Verifica si se proporcionaron los argumentos correctos
if [ "$#" -ne 2 ]; then
    echo "Argumentos erróneos. Uso: $0 <archivo_con_IPs> <timeout>"
    exit 1
fi

# Verifica si el archivo proporcionado existe
if [ ! -f "$1" ]; then
    echo "Se esperaba un fichero del tipo ips.txt"
    exit 1
fi

# Lee el archivo de IPs y guarda las IPs en un array
mapfile -t ips < "$1"
# mapfile: se utiliza para leer líneas de entrada y almacenarlas en un array.
 # lee el argv[1] y lo almacena en ips
 # -t: indica que se debe eliminar cualquier carácter de nueva línea del
 # final de cada línea leída, lo que significa que cada elemento del array
 # ips contendrá una línea del archivo sin el carácter de nueva línea al final.

# Loop a través de cada IP en el array
for ip in "${ips[@]}"; do
    ip=$(echo "$ip" | tr -d '\r\n')  # Elimina el salto de línea del final de la IP
    echo "Realizando traceroute a $ip..."

    # Ejecuta traceroute y obtiene el tiempo medio de respuesta en el primer salto
    tiempo=$(traceroute -m 1 -w "$2" "$ip" | awk '{print $NF}' | tail -n 1 | sed 's/,/\./g' | sed 's/ms//g')
    # Verifica si no se recibió respuesta en el tiempo establecido
    if [ "$tiempo" == '*' ]; then
        echo "Error: No se recibió respuesta para $ip en $2 segundos"
    else
        echo "IP $ip ha tardado $tiempo ms en el primer salto"
    fi
done | sort -nrk5
# for ip in "${ips[@]}"; do: Este bucle for itera sobre cada elemento del
 # array ips. La variable ip toma el valor de cada elemento del array en
 # cada iteración.
# ip=$(echo "$ip" | tr -d '\r\n'): Se elimina cualquier carácter de nueva
 # línea (\r\n) de la dirección IP actual. 
#  tiempo=$(traceroute -m 1 -w "$2" "$ip" | awk '{print $NF}' | tail -n 1 
# | sed 's/,/\./g' | sed 's/ms//g')
 # traceroute -m 1 -w "$2" "$ip": Ejecuta el comando traceroute para
  # realizar un rastreo de la ruta de los paquetes hacia la dirección IP
  # especificada ($ip). La opción -m 1 establece el número máximo de saltos
  # a 1 y la opción -w "$2" especifica el tiempo de espera en segundos para
  # recibir una respuesta en cada salto, donde "$2" es un parámetro pasado
  # al script. El resultado de este comando es una lista de los saltos y los
  # tiempos de respuesta.
 # awk '{print $NF}': Utiliza awk para imprimir la última columna de la
  # salida generada por traceroute. En este contexto, la última columna
  # corresponde a los tiempos de respuesta.
 # tail -n 1: Utiliza tail para seleccionar la última línea de la salida
  # generada por traceroute. Esta línea contiene el tiempo de respuesta del
  # último salto.
 # sed 's/,/\./g': Utiliza sed para reemplazar todas las comas (,) por
  # puntos (.) en el resultado obtenido anteriormente. Esto es necesario para
  # convertir el formato numérico del tiempo de respuesta de milisegundos (ms)
  # a un formato compatible con números decimales.
 # sed 's/ms//g': Utiliza sed nuevamente para eliminar todas las apariciones
  # de "ms" en el resultado obtenido anteriormente. Esto elimina la unidad
  # de medida de milisegundos (ms) del tiempo de respuesta.
 # En resumen, esta línea ejecuta traceroute para obtener el tiempo de
  # respuesta del último salto hacia la dirección IP especificada, luego
  # procesa y formatea este tiempo de respuesta para su posterior uso en el
  # script.
 # Para que funcione traceroute: sudo apt install traceroute
#emparejado: grep -Eo '[^ ]+ +[^ ]+ +[^ ]+ +$'
#sacar cada tiempo: echo timpo | grep -Eo '^[^]+'
# echo tiempo | tr ' ' '\n'
# echo tiempo | sed -r 's/^([^ ]+) +([^ ]+) +([^ ]+)$/\1/'
exit 0

: ' 
 3
 [aeiou]: empareja con las letras a, e,i,o y u.
 [1-9] es equivalente a [123456789].
 [a-e] es equivalente a [abcde].
 [1-9a-e] es equivalente a [123456789abcde].
 Los rangos típicos se pueden especificar de la siguiente forma:
  [[:alpha:]]→ [a-zA-Z].
  [[:alnum:]]→ [a-zA-Z0-9].
  [[:lower:]]→ [a-z].
  [[:upper:]]→ [A-Z].
  [R[:lower:]]→ [Ra-z]
'