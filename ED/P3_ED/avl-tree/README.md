# Implementación del TAD AVLTree[T]

_© F.J. Madrid Cuevas (fjmadrid@uco.es)
Estructuras de Datos. Grado de Ingeniería Informática. Universidad de Córdoba. España_

## Objetivos

- Implementar el TAD Árbol Binario de Búsqueda.
- Implementar los algoritmos de equilibrio AVL.

## Descripción

En esta práctica se propone implementar el TAD BSTree[T] y el TAD AVLTree[T].

(1) Un árbol Binario de Búsqueda T, es un árbol binario que asegura el invariante: “$T$ es un árbol vacío o para todo subárbol no vacío $s \in T$, se cumple que `{claves en s.left()} < {s.item()} < {claves en s.right()}`”

Por otra parte un árbol AVL extiende al árbol binario de búsqueda añadiendo además el invariante:

(2) Un árbol AVL $T$ es un árbol binario de búsqueda que asegura el invariante: "en todo subárbol no vacío $s \in T$ se cumple que `|s.right().height() - s.left().right()| <= 1`",

es decir, Un árbol AVL es un árbol binario de búsqueda equilibrado.

Para conseguir mantener este invariante, tras realizar una operación de inserción/borrado en el árbol (usando el mismo algoritmo que en el árbol BST), se procederá a revisar si el subárbol afectado en la inserción, o los subárboles en el camino que conecta el nodo borrado con la raíz, están equilibrados (cumplen el invariante). Si no es así, se procederá a realizar una o dos operaciones de rotación en el subárbol que ha perdido el equilibrio para equilibrar de nuevo. Por lo tanto para implementar un árbol AVL necesitamos un mecanismo para seguir el camino que conecta un nodo con sus predecesores hasta la raíz del árbol.

Un TAD relacionado es el `AVLTreeIterator` que permitirá recorrer en orden todas las claves almacenadas en el árbol usando una semántica de puntero sobrecargando los operadores `++`, `--` para moverlo por el árbol y los operadores de deferencia `*` y `->` para acceder los items almacenados.

## Evaluación

La práctica se estructurará en dos semanas:

1. La primera semana se debe implementar sólo las operaciones de árbol binario de búsqueda (**ONLY_BSTREE**): Implementar la interfaz de AVLTNode sólo para enlaces de padres a hijos y los algoritmos de localización, inserción y borrado de claves sin balanceo (árbol BSTree). Por último implementar la generación de un árbol binario de búsqueda perfectamente equilibrado conocidas todas las claves.

2. En la segunda semana se deben implementar las operaciones para obtener el árbol de búsqueda AVL: extensión del TAD BSTNode al TAD AVLTNode manteniendo un enlace de nodo hijo a nodo padre y la altura pre calculada del nodo junto con el algoritmo de balanceo tras la inserción/borrado de claves que usa las operaciones de rotación necesarias para equilibrar el árbol. También implementar el iterador del árbol y la función que calcula mayor y menor longitud de una rama en el árbol.

<div style="border-style:solid;padding:1em;font-size:0.75em">

| Tests                                                 | Puntos |
| :---------------------------------------------------- | :----: |
| `test_bstnode 01_tests_bstnode`                        |   1    |
| `test_bstree 02_tests_bstree`                         |   3    |
| `test_bstree 03_tests_bstree_perfectly_balanced`      |   1    |
| `test_avltnode 04_tests_avltnode`                      |   0.5  |
| `test_avltree 05_tests_avltree`                       |   3    |
| `test_avltree 06_tests_compute_min_max_branch_length` |   0.5  |
| `test_avltree 07_tests_avltree_iterator`              |   1    |

</div>
