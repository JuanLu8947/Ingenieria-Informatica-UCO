#!/bin/bash

# Verificar que se proporciona un argumento
if [ "$#" -ne 1 ]; then
    echo "Argumentos incorrectos. Uso: $0 <fichero_peliculas>"
    exit 1
fi

# Verificar que el archivo proporcionado existe
if [ ! -f "$1" ]; then
    echo "Se esperaba un fichero del tipo peliculas.txt"
    exit 1
fi

echo "1) Titulo de las películas que tengan una longitud de 4 palabras:"
grep "^> [^ ]\+ [^ ]\+ [^ ]\+ [^ ]\+$" "$1"
# grep: busca patrones en archivos de texto.
# ^: Representa el comienzo de una linea
# >: Busca el símbolo > al principio de la línea, indicando el inicio de un
 # título de película.
# [^ ]\+: asegura que cada palabra del título tenga al menos un carácter.
# [ ]\+: Busca uno o más espacios en blanco entre las palabras del título.
# {4}: Indica que la expresión anterior (una secuencia de caracteres que no
 # son espacios en blanco seguida de uno o más espacios en blanco) debe
 # repetirse exactamente 4 veces, lo que significa que la línea debe contener
 # exactamente 4 palabras.

echo
echo "2) Duraciones superiores a 1h 45min"
grep -E "1hr [5-9][0-9]min|2hr [0-9][0-9]min" "$1"
# grep -E busca líneas que contengan una duración de tiempo superior al 
 # tiempo introducido
# 1hr [5-9][0-9]min": Este patrón coincide con las líneas que contienen la
 # cadena "1hr" seguida de un espacio, luego un número del 5 al 9
 # (representando el primer dígito de los minutos), seguido de cualquier
 # número del 0 al 9 (representando el segundo dígito de los minutos) y,
 # finalmente, la cadena "min". Esto representa cualquier duración entre
 # 1 hora y 45 minutos y 1 hora y 59 minutos.
# En resumen, este comando busca y muestra las líneas que contienen
 # duraciones de tiempo superiores a 1 hora y 45 minutos en el archivo
 # especificado como argumento.

echo
echo "3) Numero de peliculas por pais"
grep -o "\-[^-]\+\-" "$1" | sort | uniq -c
# grep -o: para imprimir solo las partes de las líneas que coinciden con el
 # patrón especificado.
# sort y uniq: para contar las ocurrencias únicas de cada país.
 # sort se utiliza para ordenar alfabéticamente las coincidencias, 
 # y uniq -c se utiliza para contar el número de ocurrencias de cada país.
# En resumen, este comando busca y cuenta el número de películas por país 
 # en el archivo especificado como argumento
# en este caso se usan guiones en las expresiones regulares porque los
 # paises aparecen entre guiones

echo
echo "4) Lineas que contengan d, l o t , una vocal , y misma letra"
grep -Eo "[^ ]*([dlt])[aeiou]\1[^ ]*" "$1"
# Tiene la función de buscar líneas en un archivo que contengan las letras
 # 'd', 'l' o 't', seguidas de una vocal y luego la misma letra nuevamente.
# grep -E: para activar el uso de expresiones regulares extendidas.
# \b: Representa un límite de palabra, asegurando que la coincidencia esté
 # delimitada por espacios, signos de puntuación o el principio/fin de la línea.

echo
echo "5) Lineas que acaben con 3 puntos y no empiecen por espacios"
grep -E "^[^ ]*[^ ]\.\.\.$" "$1"
# [^ ]*: Coincide con cero o más caracteres que no son espacios. 
 # Esto garantiza que la línea no comience con un espacio.
# [^ ]: Coincide con un carácter que no es un espacio.
# \.\.\.$: comprueba si coincide con tres puntos ('...') al final de la línea.
# En resumen, este comando buscará en el archivo todas las líneas que
 # terminen con tres puntos ('...') y que no comiencen con un espacio,
 # y mostrará esas líneas por la salida estándar.

: ' 
 1
 “[...]”: sirve para indicar una lista caracteres posibles
 “[^...]”: sirve para negar la ocurrencia de uno o más caracteres
 “ ^ ”: empareja con el principio de una línea
 “$”: empareja con el final de una línea
 “*”: empareja con cero, una o más ocurrencias del carácter anterior
 
 Los paréntesis () (o \(\)) permiten agrupar caracteres a la
  hora de aplicar los metacaracteres
'