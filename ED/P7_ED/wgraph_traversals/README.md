# Árbol Abarcador de un Grafo

_© F.J. Madrid Cuevas (fjmadrid@uco.es)
Estructuras de Datos. Grado de Ingeniería Informática. Universidad de Córdoba. España_

## Objetivo

- Aprender a implementar el TAD Grafo.
- Implementar los algoritmos para obtener el árbol abarcador en profundidad y en anchura de un grafo.
- Implementar un algoritmo para realizar la ordenación topológico de un grafo dirigido acíclico.
- Implementar el algoritmo de Prim para obtener el árbol abarcador de coste mínimo.
- Implementar el algoritmo de Kruskal para obtener el árbol abarcador de coste mínimo.
- Conocer y aprender a utilizar el TAD Disjoint-Set.
- Implementar una función de comparación personaliza para el algoritmo std::sort.

## Descripción

En esta práctica vamos a obtener árboles abarcadores de un grafo. Un árbol abarcador de un grafo, es un subgrafo conexo sin ciclos. Si el grafo no es conexo, obtendremos varios árboles abarcadores, uno para cada componente conexa del grafo.

### Árboles abarcadores en profundidad o en amplitud

De forma genérica podemos procesar un grafo siguiendo un esquema de “primero en profundidad” o “primero en amplitud”.
En el procesado en profundidad, usaremos un esquema recursivo con procesado prefijo de los vértices.
En el procesado en amplitud, usaremos un esquema iterativo usando una cola para realizar un procesado prefijo de los vértices.

### Ordenación topológica de un grafo dirigido acíclico

Es una especialización de árbol abarcador en profundidad aplicado a un grafo dirigido acíclico donde el lado dirigido “u->v” significa: “u” es un prerrequisito para “v”.
En este caso el procesado de los vértices es postfijo y el resultado es una lista de vértices donde si “u” es un prerrequisito para “v”, el vértice “u” aparecerá antes que “v” en la lista.

### Árbol abarcador de coste mínimo

Se aplican en grafos ponderados y es, de todos los posibles árboles abarcadores, aquel cuya suma de pesos de los lados seleccionados sea la mínima posible (pueden existir varias soluciones todas con el mismo coste mínimo).
Para obtener el árbol abarcador de coste mínimo vamos a implementar los algoritmos de Prim y Kruskal y comparar sus salidas.
La implementación del algoritmo de Prim es directa a partir de la descripción que hemos visto en clase.
Para implementar el algoritmo de Kruskal vamos a utilizar un TAD auxiliar para “colorear” los vértices del grafo. Este TAD es conocido como “Disjoint Set.” [1].
Supongamos que “ds” es un DisjointSet con tamaño el número de vértices del grafo. Inicialmente cada vértice tiene un “color” distinto (tiene su propio conjunto) y esto se hace con ds.make_set(v.label()) para todo vértice v del grafo.
Después, durante el algoritmo, al seleccionar un lado que conecta dos vértices u--v, con ds.find(u.label()) tenemos el “color” del vértice u y con ds.find(v.label()) el “color” de v. Si sus colores son iguales, ese lado no nos interesará, pero si son distintos, ese lado pertenece al AAM y deberemos unir los conjuntos para formar uno solo con ds.join(u.label(), v.label()).
Al final del algoritmo, todos los vértices deberían tener el mismo color. En caso contrario es porque el grafo no es conexo.
Por otra parte, para ordenar la lista de lados, vamos a utilizar el algoritmo std::sort al que le daremos un functional (en [2] tienes un ejemplo) para que compare dos lados de forma que la lista quede ordenada de menor a mayor peso y, a igualdad de pesos, (a,b) < (b,c) < (b,d) donde a, b, c y d son las etiquetas de los vértices.
Es interesante que compruebes que aunque se pueden obtener soluciones diferentes con Prim (usando distintos nodos origen) y Kruskal, todas tienen el mismo coste mínimo.

## Evaluación

| Test                                                | Puntos |
| :-------------------------------------------------- | :----: |
| `graph/test_graph graph/00_tests_vertex`            |   1    |
| `graph/test_graph graph/01_tests_edge`              |   1    |
| `graph/test_graph graph/02_tests_graph`             |   2    |
| `graph/test_graph graph/03_tests_graph_fold_unfold` |   1    |
| `test_traversals 01_tests_df`                       |   1    |
| `test_traversals 02_tests_bf`                       |   1    |
| `test_traversals 03_tests_ts`                       |   1    |
| `test_traversals 04_tests_prim`                     |   1    |
| `test_traversals 05_tests_kruskal`                  |   1    |

\* **Nota**: si el TAD Grafo ya hubiera sido implementado en otra práctica sólo se evaluarán los tests relativos a los árboles abarcadores escalando la puntuación [0, 5] al rango [0, 10].

## Referencias

[1] [https://en.wikipedia.org/wiki/Disjoint-set_data_structure].
[2] [http://www.cplusplus.com/reference/algorithm/sort/].
