# Qué he hecho y qué no
He implementado las siguientes funcionalidades de forma completa:
- Generación de puntos 3D del tablero de ajedrez.
- Detección y refinamiento de esquinas del tablero en imágenes.
- Calibración de la cámara para obtener parámetros intrínsecos y coeficientes de distorsión.
- Almacenamiento y carga de parámetros de calibración en formato XML/YML.
- Corrección de distorsión en imágenes y vídeos.

No quedan funciones pendientes por implementar; todas las funcionalidades requeridas han sido completadas.

Problemas encontrados:
- Durante la calibración, fue necesario ajustar el manejo de punteros para los vectores de rotación y traslación.
- Hubo dificultades iniciales con la ruta de las imágenes de prueba, ya que los archivos estaban comprimidos en un archivo ZIP.
- La función `cv::calibrateCamera` requería un manejo cuidadoso de los tipos de datos para evitar errores de compilación.
- Abandoné la idea de usar una webcam o cámara externa.

# Enlace al vídeo describiendo la práctica
https://youtu.be/0F6OEEUf_Cs
