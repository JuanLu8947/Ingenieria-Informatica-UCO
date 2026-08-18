#!/bin/bash 

generar_indice_html() {
    local directorio="$1"
    local fichero_indice="$directorio/index.html"
    
    # Comprobar si el directorio existe
    if [ ! -d "$directorio" ]; then
        echo "El directorio $directorio no existe."
        return 1
    fi

    # Comprobar si el directorio está vacío
    if [ -z "$(ls -A "$directorio")" ]; then
        echo "El directorio $directorio está vacío."
        return 1
    fi

    # Crear el fichero de índice HTML
    echo "<!DOCTYPE html>" > "$fichero_indice"
    echo "<html>" >> "$fichero_indice"
    echo "<head>" >> "$fichero_indice"
    echo "<title>Indice de $directorio</title>" >> "$fichero_indice"
    echo "</head>" >> "$fichero_indice"
    echo "<body>" >> "$fichero_indice"
    echo "<h1>Indice de $directorio</h1>" >> "$fichero_indice"
    echo "<ul>" >> "$fichero_indice"
    # comando > salida.txt: la salida estandar de comando se escribira en 
     # salida.txt y no por pantalla. Sobreescribe el contenido del fichero.
    # comando » salida.txt: igual que >, pero añade el contenido al fichero
     # sin sobrescribir
    # h1: vulgarmente es la cabecera 1, pero formalmente es 
     # un encabezado de nivel 1 -> el encabezado principal del HTML
    # ul: sirve para indicar el inicio de una lista de elementos
    : '
    Se podría haber hecho con un sólo "echo"
    '


    # Recorrer los ficheros y directorios del directorio actual
    for elemento in "$directorio"/*; do
        local nombre_elemento=$(basename "$elemento")
        if [ -d "$elemento" ]; then
            # Si es un directorio, crear un enlace al índice de dicho directorio
            # basename: devuelve el nombre del arhivo sin extensión
             # y sin su carpeta
            echo "<li><a href=\"$nombre_elemento/index.html\">$nombre_elemento</a></li>" >> "$fichero_indice"
            # li: genera un elemento de lista que contiene un enlace (<a>)
             # hacia otro archivo HTML dentro del mismo directorio.
        else
            # Si es un fichero, añadirlo a la lista sin enlace
            echo "<li>$nombre_elemento</li>" >> "$fichero_indice"
        fi
    done
    echo "<li><a href=file:///C:/Users/Propietario/Desktop/JuanLu/UCO/2Carrera/ProgramacionAdministracionSistemas(PAS)/Practica1/FicherosComplementariosP1/FicherosEjercicio3/index.html>"inicio"</a></li>" >> "$fichero_indice"
    # esa ruta no se debe de usar yo la he usado para obtener más dinamismo
    echo "</ul>" >> "$fichero_indice"
    echo "</body>" >> "$fichero_indice"
    echo "</html>" >> "$fichero_indice"

    echo "Se ha creado el fichero $fichero_indice con el contenido del directorio $directorio."
}

# Ejemplo de uso de la función
directorio="$1"
for d in $(find $directorio -type d)
do
    generar_indice_html $d
done
# llama a la funcion pasandole el directorio
# realpath $1/index.html -> sirve para que se adapte a cualquer ordanador
