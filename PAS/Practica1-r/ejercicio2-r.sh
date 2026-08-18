#!/bin/bash

# Comprobar el número de argumentos
if [ "$#" -ne 4 ]; then
    echo "Uso: $0 directorio_origen directorio_destino comprimir(0|1) sobreescribir(0|1)"
    exit 1
fi
# 1: comprimir; 1: sobreescribir

# Comprobar si el directorio de origen existe
directorio_origen="$1"
if [ ! -d "$directorio_origen" ]; then
    echo "El directorio de origen '$directorio_origen' no existe."
    exit 1
fi

# Obtener el directorio de destino
directorio_destino="$2"
if [ ! -d "$directorio_destino" ]; then
    mkdir -p "$directorio_destino"
fi

# Comprobar el valor para comprimir
comprimir="$3"
if [ "$comprimir" -ne 0 ] && [ "$comprimir" -ne 1 ]; then
    echo "El valor para comprimir debe ser 0 o 1."
    exit 1
fi

# Comprobar el valor para sobreescribir
sobreescribir="$4"
if [ "$sobreescribir" -ne 0 ] && [ "$sobreescribir" -ne 1 ]; then
    echo "El valor para sobreescribir debe ser 0 o 1."
    exit 1
fi
# -ne: not equal

# Obtener el nombre del directorio original
nombre_directorio=$(basename "$directorio_origen")
# basename: devuelve el nombre de un fichero sin
 # decir a qué directorio pertenece y sin su extensión

# Obtener el nombre del usuario
usuario=$(whoami)

# Obtener la fecha actual en el formato especificado
fecha=$(date +"%Y%m%d")
# Y: year; m: month; d: day

# Construir el nombre del archivo de copia
nombre_archivo="${nombre_directorio}_${usuario}_${fecha}"
if [ "$comprimir" -eq 1 ]; then
    nombre_archivo="${nombre_archivo}.tar.gz"
else
    nombre_archivo="${nombre_archivo}.tar"
fi
# -eq: equal

# Comprobar si ya existe un archivo con el mismo nombre
ruta_archivo_destino="${directorio_destino}/${nombre_archivo}"
if [ -e "$ruta_archivo_destino" ] && [ "$sobreescribir" -eq 0 ]; then
    echo "El archivo de copia '$nombre_archivo' ya existe en el directorio de destino."
    exit 1
fi
# -e: existe fichero

# Crear la copia de seguridad
if [ "$comprimir" -eq 1 ]; then
    tar -czf "$ruta_archivo_destino" -C "$directorio_origen" .
else
    tar -cf "$ruta_archivo_destino" -C "$directorio_origen" .
fi

echo "La copia de seguridad se ha creado correctamente en '$ruta_archivo_destino'."
# tar: es una utilidad de Unix para archivar y comprimir archivos.
# -c: para crear un nuevo archivo de copia
# -f: para especificar el nombre del archivo de salida
# Cuando comprimir es igual a 1, 
 # se usa la opción -z para comprimir el archivo de salida con gzip
: '
 2
 Operador Significado
    ** Exponenciacion
 
 Operador         Significado
   -n s           Longitud mayor que cero
   -z s           Longitud igual a cero
 [[ s1 == s2* ]]: true si s1 empieza por s2, sino false.
 
 Operador   Significado
 n1 -lt n2 (Less Than) Menor que
 n1 -gt n2 (Greater Than) Mayor que
 n1 -le n2 (Less or Equal) Menor o igual que
 n1 -ge n2 (Greater or Equal) Mayor o igual que
 n1 -eq n2 (Equal) Igual
 n1 -ne n2 (Not Equal) Distinto
 
 Operador Significado
 -e f1    ¿Existe el fichero f1?
 -s f1    ¿f1 tiene tamaño mayor que cero?
 -f f1    ¿Es f1 un fichero normal?
 -d f1    ¿Es f1 un directorio?
 -l f1    ¿Es f1 un enlace simbolico?
 -r f1    ¿Tienes permiso de lectura sobre f1?
 -w f1    ¿Tienes permiso de escritura sobre f1?
 -x f1    ¿Tienes permiso de ejecucion sobre f1?
'