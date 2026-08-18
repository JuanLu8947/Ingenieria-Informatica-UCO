# TAD Trie

_© F.J. Madrid Cuevas (fjmadrid@uco.es)
Estructuras de Datos. Grado de Ingeniería Informática. Universidad de Córdoba. España_

## Objetivos

- Aprender a implementar el TAD Trie.
- Aprender a usar el tipo std::map
- Aprender a usar el tipo std::pair
- Aprender a usar el tipo std::stack

## Descripción

Un Trie [1] es un árbol multicamino especializado en recuperar las claves almacenadas basándose en prefijos.

En un Trie todo nodo (salvo la raíz) representa un prefijo de clave formado por el camino desde la raíz a dicho nodo y el subárbol que tiene a dicho nodo como raíz almacena todas las clave que tienen como prefijo el definido por el nodo raíz. En esta práctica, vamos a sacar partido de esta cualidad para resolver de forma eficiente una sopa de letras.

## Detalles de implementación.

Para representar el diccionario que asocia símbolo con nodo hijo vamos a utilizar el tipo std::map [2].

Vamos a asumir que se usa codificación utf-8 para el texto que representan las claves. Para plegar/desplegar el símbolo que asocia un nodo padre con un nodo hijo vamos a utilizar una codificación en hexadecimal [5] codificando el código del símbolo con un entero sin signo de 16 bits [6].

## Evaluación

<div style="margin-left: auto;
            margin-right: auto;
            width: 90%">

| Test                                            | Puntos |
| :---------------------------------------------- | :----- |
| `test_trie_node 01_tests_trie_node`             | 2      |
| `test_trie_node 02_tests_trie_node_fold_unfold` | 1.5    |
| `test_trie 03_tests_trie`                       | 2      |
| `test_trie 04_tests_trie_fold_unfold`           | 1.5    |
| `test_trie 05_tests_retrieve`                   | 2      |

</div>

## Referencias

- [1] Trie: http://en.wikipedia.org/wiki/Trie
- [2] std::map: http://www.cplusplus.com/reference/map/map/
- [3] std::pair: https://www.cplusplus.com/reference/utility/pair/pair/
- [4] std::stack: http://www.cplusplus.com/reference/stack/stack/
- [5] Manipuladores de flujo: https://www.cplusplus.com/reference/library/manipulators/
- [6] Tipos estándar para enteros: https://www.cplusplus.com/reference/cstdint/
