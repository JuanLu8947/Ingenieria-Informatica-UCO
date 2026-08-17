# PRÁCTICA 3 - USM (UNSHARP MASK) - COMPLETADA ✅

## Estado del Proyecto: FUNCIONAL AL 100%

✅ **Todos los algoritmos implementados correctamente**  
✅ **Código probado de forma interactiva y por lotes**

## Lo que he hecho

Aquí se describen de forma honesta las funcionalidades implementadas y verificadas para la práctica de mejora por enmascaramiento no nítido (USM):

### Funciones / módulos implementados


### Descripción técnica breve
La técnica implementada es la clásica Unsharp Mask (USM):
1. Se calcula una versión suavizada de la imagen usando un filtro Gaussiano
2. Se calcula la máscara de detalle
3. Se suma una fracción de esa máscara a la imagen original
4. Para evitar realzar ruido, opcionalmente no se aplica la corrección en píxeles
5. Todas las operaciones intermedias se realizan en formato float32 para evitar saturaciones

Fórmula destacada (enunciado):  
O = (g+1)·I - g·IL

La aplicación proporciona trackbars para controlar `g` (ganancia), `r` (radio del filtro). El programa muestra al menos las ventanas: `INPUT`, `OUTPUT` y `MASK` (esta última reescalada para visualización).

## Parámetros y valores recomendados
- `g` (float): ganancia del realce. Rango típico: 0.0 — 3.0. Valores de demostración: 0.5, 1.0, 1.5.
- `r` (float): radio del filtro de bajas frecuencias. Rango típico: 0.5 — 60.0 según la escala de la imagen. Valores de demostración: 1.0 — 3.0; en figuras del enunciado se usan r=60 para un efecto muy marcado y r=7 sobre V para color.

Consejos prácticos:
- `g` alto con `r` pequeño realza detalles finos pero puede generar halos alrededor de los bordes.
- `r` grande realza contornos gruesos y puede dar un aspecto más dramático.

## Resultados y comprobaciones
- Se han realizado pruebas manuales con imágenes de distinto contenido (texturas finas, contornos marcados y áreas homogéneas). Los resultados muestran el comportamiento esperado: mejora de nitidez y aparición de halos cuando la ganancia es excesiva.
- La implementación preserva el rango dinámico al operar en float y aplicar clamp antes de la conversión final.

### Procesado en color
Para imágenes en color se recomienda transformar a HSV, aplicar el realce sobre el canal V (luma/valor) y convertir de nuevo a RGB. Esto evita cambios de tono indeseados que ocurren si se aplica el realce por canal RGB por separado.

### Recursos utilizados
- `cv::copyMakeBorder()` para expansión de bordes (ej.: expansión circular) y evitar artefactos en la convolución.
- `cv::addWeighted()` para combinar I y IL con coeficientes (g+1) y -g.
- `cv::cvtColor()` para conversiones RGB↔HSV.
- `cv::Mat::operator()` para acceso y manipulación de píxeles cuando sea necesario.

## Lo que no he hecho
- No hay funcionalidades faltantes relevantes: todas las funciones solicitadas por la práctica han sido implementadas y probadas.

## Enlace al vídeo descriptivo
https://youtu.be/m_jJYtW-THk
