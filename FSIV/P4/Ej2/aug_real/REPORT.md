# Qué he hecho y qué no

## Partes Realizadas ✅

He completado **todas las funcionalidades** requeridas para el ejercicio de realidad aumentada:

### Funciones Principales Implementadas:
1. **`fsiv_generate_3d_calibration_points()`** ✅
   - Genera puntos 3D del tablero de calibración
   - Implementa correctamente el offset (1,1) para el primer punto interno

2. **`fsiv_fast_find_chessboard_corners()`** ✅
   - Detección optimizada con bandera `CALIB_CB_FAST_CHECK`
   - Sin refinamiento de esquinas para mejor rendimiento
   - Funciona con imágenes en color directamente

3. **`fsiv_compute_camera_pose()`** ✅
   - Implementa `cv::solvePnP` para estimación de pose
   - Calcula correctamente rvec y tvec
   - Maneja correspondencias 2D-3D de forma robusta

4. **`fsiv_draw_axes()`** ✅
   - Dibuja ejes coordenados 3D con colores correctos (X=azul, Y=verde, Z=rojo)
   - Usa `cv::projectPoints` para proyección precisa
   - Mantiene perspectiva geométricamente correcta

5. **`fsiv_draw_3d_model()`** ✅
   - Implementa cubo 3D wireframe animado
   - Usa `cv::polylines` para renderizado eficiente
   - Incluye animación con punto de referencia móvil

6. **`fsiv_project_image()`** ✅
   - Realidad aumentada completa con transformación perspectiva
   - Usa `cv::getPerspectiveTransform` y `cv::warpPerspective`
   - Combinación correcta con interpolación lineal y borde transparente

7. **`fsiv_load_calibration_parameters()`** ✅
   - Carga automática de parámetros desde archivo XML
   - Uso correcto de operadores de `cv::FileStorage`
   - Maneja todos los parámetros requeridos

- Mejoras realizadas:
   · Detección de esquinas bastante notoria


## Partes NO Realizadas ❌
**Ninguna** - Todas las funcionalidades han sido implementadas satisfactoriamente.

- Mejoras Faltantes:
   · Con la implementación actual, la pirámide se teletransporta en vez de moverse con fluidez

## Estado de los Tests
- ✅ **TestFSIVGenerate3DCalibrationPoints**: PASSED
- ✅ **TestFSIVFastFindChessboardCorners**: PASSED (después de descomprimir datos)
- ✅ **TestFSIVComputeCameraPose**: PASSED
- ✅ **TestFSIVDrawAxes**: PASSED (después de descomprimir datos)
- ✅ **TestFSIVLoadCalibrationParameters**: PASSED (después de descomprimir datos)
- ✅ **TestFSIVProjectImage**: PASSED (después de descomprimir datos)

**Nota**: Fue necesario descomprimir `logitech.zip` para acceder a las imágenes y archivo XML de calibración requeridos por los tests.

## Aspectos Técnicos Destacados
### Optimizaciones Implementadas:
- **Detección rápida**: Uso de `CALIB_CB_FAST_CHECK` para mejor rendimiento
- **Proyección eficiente**: Minimización de llamadas a `cv::projectPoints`
- **Renderizado optimizado**: Uso de `cv::polylines` para wireframes complejos

### Precisión Geométrica:
- **Correspondencias exactas**: Orden correcto entre puntos 3D y 2D detectados
- **Calibración precisa**: Carga completa de parámetros intrínsecos y de distorsión
- **Proyección correcta**: Mantenimiento de perspectiva en todos los objetos virtuales

# Enlace al vídeo describiendo la práctica
(https://youtu.be/gBUY89GPHy8)
