#!/bin/bash

# Verifica si se proporcionó un argumento
if [ "$#" -ne 1 ]; then
    echo "Argumentos erróneos. Uso: $0 <fichero_peliculas>"
    exit 1
fi

# Verifica si el archivo pasado como argumento existe
if [ ! -f "$1" ]; then
    echo "Se esperaba un fichero del tipo peliculas.txt"
    exit 1
fi

# Elimina líneas vacías y subrayados, y formatea la salida utilizando sed
# sed -e '/^$/d' -e '/______/d' -e 's/____//g' -e 's/\([A-Z][a-z]*: \)/|\->\1/g' -e 's/\(^[A-Z][a-z]*\)/Titulo: \1/g' "$1" | tee películas_formateadas.txt
sed -e '/^$/d' \
    -e '/^=*$/d' \
    -e 's/^> \(.*\)$/Título: \1/' \
    -e 's/-[[:alpha:]]*-//g' \
    -e 's/Dirigida por \(.*\)$/| -> Director: \1/' \
    -e 's/Reparto: /| -> Reparto: /g' \
    -e 's/^[0-9]*hr [0-9]*min$/| -> Duracion: &/g' "$1" \
    | sed -r 's/^\(([^)]+)\).*/| -> Fecha de estreno: (\1)/' \
    | grep -vE '^ +' \
    | tee películas_formateadas.txt
# La opción -e en sed se utiliza para especificar múltiples expresiones de
 # edición en un solo comando sed
# sed -e '/^$/d': busca todas las líneas vacías en el archivo y las elimina 
 # ^$: Representa una línea vacía
# /^=*$/d: esto es una expresión regular que busca líneas que consisten
 # únicamente en signos de igualdad. Explicado detalladamente:
  # ^: indica el inicio de la línea.
  # =*: busca cualquier cantidad de signos de igualdad (=).
  # $: indica el final de la línea.
  # /d: indica a sed que elimine las líneas que coincidan con el patrón pedido.
# 's/^> \(.*\)$/Título: \1/': Busca líneas que comiencen con > seguido de un
 # espacio y captura el contenido después del espacio. Luego, reemplaza toda
 # la línea por "Título: " seguido del contenido capturado.
 # ^>: Coincide con líneas que comienzan con el símbolo >.
 # \(.*\)$: Captura cualquier contenido después del símbolo >, hasta el
  # final de la línea.
 # Cuando una línea coincide con ese patrón, se realiza la sustitución:
  # Título: \1: Reemplaza toda la línea por "Título: " seguido del contenido
   # capturado entre paréntesis en el patrón.
# 's/-[[:alpha:]]*-//g': Elimina cualquier cadena que comience con un
 # guión (-), tenga uno o más caracteres alfabéticos ([[:alpha:]]), y termine
 # con otro guión.
 # [[:alpha:]]*: Coincide con cero o más caracteres alfabéticos (letras).
# 's/Dirigida por \(.*\)$/| -> Director: \1/': Busca líneas que comiencen
 # con "Dirigida por " seguido de cualquier cosa, y captura el contenido
 # después de "Dirigida por". Luego, reemplaza toda la línea por
 # "| -> Director: " seguido del contenido capturado.
 # s: Indica que se realizará una sustitución.
 # Dirigida por: Es el patrón que se está buscando.
 # \(.*\)$: Este es un grupo de captura que coincide con cualquier cosa .* al
 # final de la línea $. Los paréntesis \(...\) se utilizan para capturar la
 # coincidencia para su posterior uso en la sustitución.
# s/^[0-9]*hr [0-9]*min$/| -> Duracion: &/g': Busca líneas que consisten en
 # un número seguido de "hr" y otro número seguido de "min", y las reemplaza
 # con "| -> Duracion: " seguido de la misma cadena encontrada.
 # ^[0-9]*hr [0-9]*min$: Este es el patrón de búsqueda que coincide con
 # líneas que contienen una cantidad arbitraria de dígitos seguida por "hr"
 # y otra cantidad de dígitos seguida por "min". El ^ indica el inicio de la
 # línea y $ indica el final de la línea.
# sed -r 's/^\(([^)]+)\).*/| -> Fecha de estreno: (\1)/' \:
 # \(: Inicia un grupo de captura.
 # [^)]+: Coincide con uno o más caracteres que no sean paréntesis derechos.
 # \) : Coincide con un paréntesis derecho.
 # .*: Coincide con cualquier carácter (excepto un salto de línea) cero o más
  # veces.
 # \1: Representa el contenido del primer grupo de captura.
# | grep -vE '^ +' \: grep está utilizando la opción -v para invertir la
 # coincidencia, es decir, muestra todas las líneas que no coinciden con el
 # patrón especificado. El patrón especificado es ^ +, que coincide con una
 # cadena que comienza con uno o más espacios en blanco al principio de la
 # línea.
# | tee películas_formateadas.txt: La salida de sed se redirige a tee, 
 # que a su vez escribe la salida tanto en la consola como en el archivo
 # películas_formateadas.txt.
#sed para cada linea
echo "Fichero peliculas_formateadas.txt creado con éxito."

: ' 
 2
 Carácter BRE ERE Significado
     \     ✓   ✓   Interpreta de forma literal el siguiente carácter
     .     ✓   ✓   Selecciona un carácter cualquiera
     *     ✓   ✓   Selecciona ninguna, una o varias veces lo anterior
     ^     ✓   ✓   Principio de línea
     $     ✓   ✓   Final de línea
   [...]   ✓   ✓   Cualquiera de los caracteres que hay entre corchetes
    \n     ✓   ✓   Utilizar la n-ésima selección almacenada
   {n,m}   X   ✓   Selecciona lo anterior entre n y m veces
     +     X   ✓   Selecciona una o varias veces lo anterior
     ?     X   ✓   Selecciona una o ninguna vez lo anterior
     |     X   ✓   Selecciona lo anterior o lo posterior
   (...)   X   ✓   Selecciona la secuencia que hay entre paréntesis2
  \{n,m\}  ✓   X   Selecciona lo anterior entre n y m veces
  \(...\)  ✓   X   Selecciona la secuencia que hay entre paréntesis2
    \|     ✓   X   Selecciona lo anterior o lo posterior

 Basic Regular Expression
 ERE: Extended Regular Expression 
'