# Búsqueda de caminos mínimos en grafos ponderados

_© F.J. Madrid Cuevas (fjmadrid@uco.es)
Estructuras de Datos. Grado de Ingeniería Informática. Universidad de Córdoba. España_

## Objetivo

- Aprender a implementar el TAD Grafo.
- Implementar el algoritmo de Dijkstra.
- Implementar el algoritmo de Floyd.
- Implementar el algoritmo A\*.
- Aprender a utilizar el tipo c++ std::tuple [1].

## Descripción

Existen varios algoritmos para buscar caminos mínimos en grafos ponderados. Podemos destacar:

- **Algoritmo de Dijkstra**: buscar todos los caminos mínimos desde un vértice origen al resto de vértices.
- **Algoritmo de Floyd**: buscar todos los caminos mínimos entre dos pares de vértices.
- **Algoritmo A\***: busca el camino más corto entre dos vértices usando una heurística para guiar la búsqueda.

## Evaluación

| Test                                                      |     Puntos     |
| :-------------------------------------------------------- | :------------: |
| `graph/test_graph graph/00_tests_vertex`                  |  2.5 \* 1/10   |
| `graph/test_graph graph/01_tests_edge`                    |  2.5 \* 1/10   |
| `graph/test_graph graph/02_tests_graph`                   |  2.5 \* 2/10   |
| `graph/test_graph graph/03_tests_graph_fold_unfold`       |  2.5 \* 1/10   |
|                                                           |                |
| `priority_queue/test_heap priority_queue/01_heap_editing` |  2.5 \* 5/10   |
| `priority_queue/test_heap priority_queue/02_heapifiy`     | 2.5 \* 2.5/10  |
| `priority_queue/test_heap priority_queue/03_heapsort`     | 2.5 \* 1.25/10 |
| `priority_queue/test_pqueue priority_queue/04_pqueue`     | 2.5 \* 1.25/10 |
|                                                           |                |
| `test_dijkstra 01_tests_dijkstra`                         |   5 \* 4/10    |
| `test_floyd 02_tests_floyd`                               |   5 \* 3/10    |
| `test_astar 03_tests_astar`                               |   5 \* 3/10    |

**Nota**: Puedes usar el tipo std::priority_queue [2] en vez de implementar el TAD "PriorityQueue" en los algoritmos Dijkstra y A\*.

## Referencias

[1] [https://en.cppreference.com/w/cpp/utility/tuple].
[2] [https://en.cppreference.com/w/cpp/container/priority_queue].
