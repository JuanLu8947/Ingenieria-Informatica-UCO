# TAD PriorityQueue

## Objetivos

- Implementar el TAD Heap.
- Implementar el algoritmo Heapsort.
- Implementar una cola de prioridad.

## Descripción

Una cola de prioridad es una cola (esquema FIFO) que además permite que al añadir un nuevo item a la cola este se pueda situar delante de los items que ya estuvieran en la cola pero con menor (mayor) prioridad.

Para diseñar una cola de prioridad podemos utilizar un montículo (Heap) que nos proporciona O(1) para observar el item con mayor prioridad y O(Log N) para insertar nuevos items o borrar el item con mayor prioridad.

Los montículo fueron desarrollados inicialmente para ordenar mediante el algoritmo conocido como "Heapsort" que ordena una secuencia con O(N Log N) usando un heap.

Un montículo es un árbol binario que mantiene dos invariante:

- Es un árbol quasi-completo.
- El árbol está vacío o para cada subárbol, la raíz es mayor (menor) que todos sus descendientes proprios.

Un árbol binario quasi-completo es aquél que tiene todos sus niveles completos excepto el último que estará llenándose de izquierda a derecha sin dejar huecos.

El diseño del montículo utiliza un array de tamaño $N$ (el que se quiere ordenar). Así cada índice $0 \le i < N//2$ puede tener asociados el hijo izquierdo $l=i*2+1$, y $l<N$ y derecho $r=i*2+2$ y $r<N$, Así mismo todo índice $0<j<N$ tiene asociado un padre $p=(j-1)//2$.

Hay dos operaciones básicas para construir un montículo:

- _Flotar_: sube un nuevo item desde un nodo hoja hasta el nivel del árbol donde se cumpla el invariante de orden.
- _Hundir_: bajará el item de un nodo hacia una hoja hasta que se cumpla el invariante de orden.

Cons estas operaciones básicas se diseñan el resto de operaciones modificadoras:

- _Heapify_, que consigue que dado un array este se convierta en un montículo con O(N).
- _Insertar_ un nuevo valor con O(Log N).
- _Eliminar_, que elimina el mayor (menor) valor del montículo con O (Log N).

## Calificación

| Tests                     | Puntos |
| ------------------------- | :----: |
| test_heap 01_heap_editing |   5    |
| test_heap 02_heapifiy     |  2.5   |
| test_heap 03_heapsort     |  1.25  |
| test_pqueue 04_pqueue     |  1.25  |
