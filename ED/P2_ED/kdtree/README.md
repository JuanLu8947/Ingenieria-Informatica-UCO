# TAD "KDTree"

_© F.J. Madrid Cuevas (fjmadrid@uco.es)_
_Estructuras de Datos. Grado de Ingeniería Informática_
_Universidad de Córdoba. España_

## Objetivos

- Aprender qué es un KDTree y como se puede implementar usando un árbol binario.
- Aprender cuál es el problema del vecino más cercano y cómo resolverlo usando un KDTree.

## Descripción

Un KDTree [1] es un árbol binario que se utiliza para organizar un espacio vectorial de $K$ dimensiones. Cada subárbol en el nivel $l$ representa un subconjuto $\mathcal{S}$ del dataset y utiliza la dimensión $d = l \mod K$, para definir el hiperplano $$x_d = \mathrm{p[d]},$$ que particiona $\mathcal{S}$ en dos subconjuntos (se crea un árbol binario).

El patrón $p\in \mathcal{S}$ comúnmente se selecciona como el patrón cuyo valor de la dimensión $p[d]$ es la mediana de los valores para esa dimensión $d$ en el subconjunto $\mathcal{S}$ de patrones que representa el subárbol y será la raíz del mismo.

Una vez seleccionado el patrón $p$ se divide el subconjunto $\mathcal{S}$ de patrones en dos partes: la parte izquierda $\mathcal{S}_l$ estará formada por todo patrón $t\in \{\mathcal{S}-p\}$, $t[d]\le p[d]$, y será representada por subárbol izquierdo del nivel $l+1$. La parte derecha $\mathcal{S}_r$ estará formada por los patrones $t$, $t[d]>p[d]$ y será representada por el subárbol derecho en nivel $l+1$ (ver Algoritmo 1 para más detalles).

<div style="border-style:solid;">

**Algoritmo 1.**

```pascal
Function make_kdtree (ds:DArray[Pattern], depth:Integer)
   :Binarytree[Pattern]
Var
    kdtree: BinaryTree[Pattern]
    axis: Integer
    median: Pattern
Begin
    kdtree := BinaryTree.make()
    If ds.size()>0 Then
        axis := depth mod Point.dimensions();
        //Sort vector using pattern's axis as criteria.
        sort_axis(ds, axis)
        median := ds[ds.size() div 2]
        kdtree.createRoot(median)
        kdtree.set_left(make_kdtree(ds[0:ds.size() div 2],
           depth+1);
        kdtree.set_right(make_kdtree(ds[ds.size() div 2 + 1:],
           depth+1);
    End-if
    Return kdtree
End.
```

</div>

### Búsqueda del vecino más cercano

Un KDTree puede realizar la búsqueda del vecino más cercano [2] con $O(\log N)$ en el caso promedio y por eso se suele utilizar en algoritmos como el clasificador/regresor k-NN [2] o el algoritmo de agrupamiento "k-medias" [3]

El Algoritmo 2 muestra el diseño de la búsqueda del vecino más cernano a un patrón usando un KDTree.

<div style="border-style:solid;">

**Algoritmo 2.**

```pascal
Function find_NN(t:KDTree, p:Pattern, depth:Integer):
   Pattern
Prec: Not t.is_empty()
Var
    axis:Integer //The axis to inspect.
    curr, curr2: Pattern //The best up to date candidate.
Begin
    axis := depth mod p.dim() //Selected the axis to split.
    curr := t.root() //the current candidate on this level.
    curr2 := curr

    // STEP 1: find candidate in the corresponding subtree.
    If p[axis]<=t.item()[axis] And Not t.left().is_empty() Then
        curr2 := find_NN(t.left(), p, depth+1)
    Else If p[axis]>t.item()[axis] And
                                 Not t.right().is_empty() Then
        curr2 := find_NN(t.right(), p, depth+1)
    End-If

    // STEP 2: update candidate if needed.
    If dist(p, curr2)<dist(p, curr) Then
        curr := curr2

    // STEP 3: find candidate in the other subtree or cut
    // the search.
    If abs(p[axis]-t.item()[axis]) < dist(curr, p) Then
        curr2 := curr
        If p[axis]>t.root()[axis] And
                                 Not t.left().is_empty() Then
            curr2 := find_NN(t.left(), p, depth+1)
        Else If Not t.right.is_empty() Then
            curr2 := find_NN(t.right(), p, depth+1)
        End-If
    End-If

    // STEP 4: update candidate if needed.
    If dist(curr2, p)<dist(curr, p) Then
        curr := curr2
    Return curr
End.
```

</div>

## Evaluación

En la Tabla 1 se muestra la puntuación que se obtendrá en función de los test que el código pase.

Se recomienda distribuir la realización de la práctica en dos semanas de la siguiente forma:

- Semana 1: todos los tests de los TADs Pattern, BTNode y los test de fold/unfold del TAD BTree.
- Semana 2: el resto de tests del TAD BTree y los tests del TAD KDTree.

<div style="border-style:solid;padding:1em;font-size: 0.75em;">

| Test                                                          | Puntos |
| :------------------------------------------------------------ | :----: |
| pattern/test_pattern pattern/01_tests_pattern                 |  1/3   |
| pattern/test_pattern pattern/02_tests_pattern_dataset         |  1/3   |
| pattern/test_pattern pattern/03_tests_pattern_distances       |  1/3   |
|                                                               |        |
| binary_tree/test_btree_node binary_tree/01_tests_btree_node   |   1    |
| binary_tree/test_btree binary_tree/02_tests_btree_fold_unfold |   1    |
| binary_tree/test_btree binary_tree/03_tests_btree_height_size |   1    |
| binary_tree/test_btree binary_tree/04_tests_traversals        |   1    |
| binary_tree/test_btree binary_tree/05_tests_inorder           |   1    |
|                                                               |        |
| test_kdtree 01_tests_create_kdtree                            |   2    |
| test_kdtree 02_tests_find_nn_L1                               |   1    |
| test_kdtree 03_tests_find_nn_L2                               |   1    |

**Tabla 1**: Puntuación obtenida en función de los tests que código pase.

</div>

## Referencias

- [1] Tad KDTree: https://en.wikipedia.org/wiki/K-d_tree
- [2] Algoritmo K-NN: https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm
- [3] Algoritmo K-means: https://en.wikipedia.org/wiki/K-means_clustering
