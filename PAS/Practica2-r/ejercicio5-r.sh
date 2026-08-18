#!/bin/bash

# Comprobación de argumentos
if [ "$#" -ne 1 ]; then
    echo "Argumentos incorrectos. Uso: ./ejercicio5.sh <texto.txt>"
    exit 1
fi

archivo="$1"

# Comprobación de si el archivo existe
if [ ! -f "$archivo" ]; then
    echo "Se esperaba un fichero del tipo texto.txt"
    exit 1
fi

# Extraer las palabras de las líneas que contienen números y contar su frecuencia
palabras=$(grep '[0-9]' "$archivo" | tr -d '[:punct:]' | tr '[:upper:]' '[:lower:]' | tr -d '[:digit:]' | tr -s '[:blank:]' '\n' | iconv -c -f utf-8 -t ascii//TRANSLIT | tr '[:upper:]' '[:lower:]' | sort -r | uniq -ic | sort -nr)

# grep '[0-9]' "$archivo": Utiliza el comando grep para buscar líneas que
 # contienen al menos un dígito numérico en el archivo especificado por la
 # variable $archivo.
# tr -d '[:punct:]': Esto elimina toda la puntuación de las líneas
 # seleccionadas, como puntos, comas, etc.
# tr '[:upper:]' '[:lower:]': Utiliza tr para convertir todos los
 # caracteres alfabéticos en minúsculas
# tr -d '[:digit:]': Esto elimina todos los dígitos numéricos de las líneas.
# tr -s '[:blank:]' '\n': Utiliza el comando tr para reemplazar secuencias
 # de espacios en blanco o tabulaciones por saltos de línea. La opción -s
 # indica que se deben eliminar las repeticiones de los caracteres
 # especificados en la primera cadena de caracteres de reemplazo.
# iconv -c -f utf-8 -t ascii//TRANSLIT: Esto convierte el texto de UTF-8 a
 # ASCII transliterado, lo que puede ser útil para tratar con caracteres
 # especiales.
# sort -r: Esto ordena las palabras de forma inversa, es decir, de la Z a la A.
# niq -ic: Esto cuenta las palabras únicas, ignorando las diferencias entre
 # mayúsculas y minúsculas.
# sort -nr: Esto ordena los resultados numéricamente de mayor a menor, según
 # la cantidad de ocurrencias de cada palabra.
# Mostrar las palabras ordenadas por orden alfabético inverso con su frecuencia y número de orden
echo "#        Count   Word"
nl -n ln <<< "$palabras"
# nl -n ln <<< "$palabras": Utiliza el comando nl para numerar las líneas de
 # la variable $palabras de forma ascendente, que contiene la lista de
 # palabras y sus recuentos de ocurrencias

exit 0

: ' 
 sed [-r] [-n] -e 'comando'[archivo]:
  -r: uso de EREs en lugar de BREs.
  -n: modo silencioso → para imprimir una línea tienes que
       indicarlo explícitamente mediante el comando p (print).
  -e 'comando': ejecutar el comando o comandos especificados.
  -d: borrar líneas direccionadas.
  -p: imprimir líneas direccionadas.
  -s: sustituir una expresión por otra sobre las líneas seleccionadas.
       Sintaxis: s/patron/reemplazo/[banderas]
        patron: expresión regular
        reemplazo: cadena con la cuál se reemplaza
        Bandera n, siendo n un número entero: reemplazar sólo la
         ocurrencia n-ésima.
        Bandera g: reemplazar todas las ocurrencias.
        Bandera p: forzar a imprimir la línea (solo tiene sentido si
         hemos utilizado -n).
 mas opciones en man sed
'