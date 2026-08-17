# Qué he hecho y qué no

## ✅ Funcionalidades Completadas (100%)

**He implementado todas las funciones requeridas cumpliendo los 3 objetivos de aprendizaje:**

### 🎯 Objetivo 1: Calcular flujo óptico entre pares de frames
#### 1. `fsiv_compute_dense_optical_flow` - ✅ IMPLEMENTADA
- Creación del algoritmo FarnebackOpticalFlow usando `cv::FarnebackOpticalFlow::create()`
- Configuración correcta de flags para usar estimación inicial cuando flow no está vacío
- Cálculo del flujo óptico denso entre frames consecutivos

### 🎯 Objetivo 2: Usar flujo óptico para separar primer plano del segundo plano
#### 2. `fsiv_compute_optical_flow_magnitude` - ✅ YA IMPLEMENTADA
- Separación de componentes X e Y del flujo óptico usando `cv::split()`
- Cálculo de magnitud vectorial usando `cv::magnitude()`

#### 4. `fsiv_compute_of_foreground_mask` - ✅ IMPLEMENTADA
- Cálculo del flujo óptico entre frames
- Cálculo de la magnitud del flujo
- Umbralización binaria para detectar zonas con movimiento aparente
- Dilatación morfológica para cerrar huecos y extender zona detectada
- **Running average** con fórmula: `m = α*m_old + (1-α)*m_new`

### 🎯 Objetivo 3: Implementar "running average" como técnica de memoria
- Implementación correcta usando `cv::addWeighted()` con factor alpha
- Control del factor de memoria del sistema (0.0 = sin memoria, 1.0 = memoria completa)
- Estabilización temporal de la máscara de primer plano

### 🔧 Funciones Auxiliares
#### 3. `fsiv_create_structuring_element` - ✅ YA IMPLEMENTADA
- Soporte para elementos estructurales: rectangular (0), cruz (1) y elipse (2)
- Configuración correcta de tamaño y punto de anclaje para dilatación morfológica

#### 5. `fsiv_blur_background` - ✅ IMPLEMENTADA
- Soporte para suavizado normal (`cv::blur`) y Gaussiano (`cv::GaussianBlur`)
- Configuración automática del kernel basado en radio
- Fusión correcta de primer plano (nítido) y fondo (suavizado) usando máscara invertida

## ❌ Funcionalidades No Realizadas
**Ninguna** - Todas las funciones requeridas han sido implementadas correctamente sin problemas.

## Observaciones Técnicas
La implementación **recrea exitosamente el efecto de suavizado del fondo** como en aplicaciones comerciales (Zoom, Skype) mediante:
- **Hipótesis fundamental**: El fondo es estático, solo la persona (primer plano) se mueve
- **Detección de movimiento**: Usando magnitud del flujo óptico como característica
- **Separación foreground/background**: Máscara binaria basada en umbralización
- **Memoria del sistema**: Running average para estabilidad temporal
- **Suavizado selectivo**: Solo aplicado al fondo, manteniendo primer plano nítido

# Enlace al vídeo describiendo la práctica
https://youtu.be/aE8i3_Mtnvk
