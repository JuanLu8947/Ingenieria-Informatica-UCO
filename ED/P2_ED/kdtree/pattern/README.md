# Pattern

_© F.J. Madrid Cuevas (fjmadrid@uco.es)_
_Estructura de Datos. Grado de Ingeniería Informática_
_Universidad de Córdoba. España_

# Objetivos

- Aprender a usar el tipo `std::valarray`.

# Descripción

Esta práctica modela el concepto "patrón" en el contexto del aprendizaje automático.

Para nosotros, un patrón representa un vector en $\mathcal{R}^n$ que puede tener asociada una etiqueta de clase, el cual será un número entero, normalmente positivo, dejando el valor $-1$ para indicar "sin etiqueta".

Un conjunto de patrones se denomina "_dataset_" y, cuando los patrones tienen etiquetas, tendremos un _dataset_ anotado.

Para representar un patrón usaremos el tipo `std::valarray` [1] y de esta forma nos podremos aprovechar de todas sus operaciones matemáticas vectorizadas que están altamente optimizadas.

Para representar un _dataset_ utilizaremos el tipo `std::vector` que permite una gestión cómoda de la memoria.

# Evaluación

| Test                                    | Puntos |
| :-------------------------------------- | :----: |
| test_pattern 01_tests_pattern           |   4    |
| test_pattern 02_tests_pattern_dataset   |   3    |
| test_pattern 03_tests_pattern_distances |   3    |

# Referencias

[1] `valarray`: [https://en.cppreference.com/w/cpp/numeric/valarray]
