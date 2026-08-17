# Qué he hecho y qué no

He implementado completamente las siguientes funcionalidades:

- Creación de filtros Laplacianos de 4 y 8 vecinos.
- Creación del filtro DoG (Difference of Gaussians) con expansión adecuada del filtro pequeño.
- Creación del filtro de realce (sharpening) combinando el negativo del filtro Laplaciano/DoG y el impulso central.
- Expansión de imágenes tanto con relleno a ceros como circular, usando las funciones de OpenCV.
- Aplicación del filtro de realce mediante convolución (cv::filter2D) y recorte del resultado al tamaño original.


Todas las funciones principales de procesamiento de imágenes requeridas en la práctica han sido implementadas y probadas a nivel de código.

Además, se ha ejecutado los tests automáticos proporcionados y todos han pasado correctamente, lo que confirma el correcto funcionamiento de la práctica.


No he tenido problemas significativos durante la implementación, ya que he seguido las indicaciones y sugerencias del enunciado y la documentación de OpenCV.

# Enlace al vídeo describiendo la práctica
https://youtu.be/C2TgZpehbIs
