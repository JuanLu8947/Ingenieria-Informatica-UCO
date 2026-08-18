# Estructuras de datos lineales

_© F.J. Madrid Cuevas (fjmadrid@uco.es). Estructura de Datos. Grado de Ingeniería Informática. Universidad de Córdoba. España_

## Objetivos

- Aprender a implementar el TAD CDArray.
- Aprender a implementar el TAD List usando una lista de nodos doblemente enlazados.
- Aprender a implementar el TAD ListIterator.
- Aprender a implementar algoritmos basados en listas: fold, unfold, find, sort, merge.
- Aprender a implementar el TAD Stack usando una lista.
- Aprender a implementar el TAD Queue usando un array dinámico circular.

## Descripción

En esta práctica tienes que implementar varias estructuras de datos lineales. Hay dos estructuras básicas: el array dinámico circular (CDArray)y la lista (List).

Con la lista podrás implementar después la pila (Stack) y con el el array dinámico circular podrás implementar la cola (Queue).

Para implementar la lista, vamos a utilizar un diseño de cadena de nodos doblemente enlazados (DNode), aunque en la primera semana de la práctica se puede simplificar a una lista simple de nodos enlazados usando sólo un enlace al siguiente nodo.

Para editar la lista utilizaremos iteradores por lo que deberás implementar el TAD ListIterator.

Por último, se propone implementar varios algoritmos aplicados a las listas como son: Plegado/Desplegado (fold/unfold), localizar (find), traspasar nodos (splice), combinar listas ordenadas (merge) y ordenar la lista (mergeSort).

Se recomienda la siguiente forma de realizar la práctica:

- **Primera semana**: implementar los tipos CDArray, Queue, los tipos DNode y List pero sólo las interfaces para implementar la interfaz de lista simple (crear, front(), push_front(), pop_front()) y el tipo Stack.
- **La segunda semana**: implementar los tipos DNode completo (doble enlazado), ListITerator, operaciones de edición de Lista (usando iteradores) y los algoritmos de lista splice, merge y sort.

## Evaluación

Esta práctica se evaluará de la forma siguiente:

| Tests                                     | Puntos |
| ----------------------------------------- | :----: |
| test_cdarray 01_tests_cdarray             |   1    |
| test_cdarray 02_tests_cdarray_fold_unfold |   1    |
| test_queue   03_tests_queue               |   0.5  |
| test_dnode   04_tests_simple_list_node    |   1    |
| test_list    05_tests_simple_list         |   1    |
| test_dnode   06_tests_list_node           |   1    |
| test_iterator 07_tests_list_iterator      |   1    |
| test_list    08_tests_list_editing        |   1    |
| test_list    09_tests_list_fold_unfold    |   1    |
| test_list    10_list_algorithms           |   1    |
| test_stack   11_tests_stack               |   0.5  |
