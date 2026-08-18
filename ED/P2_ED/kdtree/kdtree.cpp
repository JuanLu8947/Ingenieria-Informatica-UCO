/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <algorithm>
#include <limits>

#include "kdtree.hpp"

bool operator==(const Pattern &a, const Pattern &b)
{
    return a.class_label() == b.class_label() &&
           a.dim() == b.dim() &&
           (a.values() == b.values()).min();
}

KDTree::~KDTree()
{
}

bool KDTree::is_empty() const
{
    bool empty = true;
    // TODO
    empty = _tree.is_empty();
    //empty = _k == 0;
    //
    return empty;
}

Pattern KDTree::item() const
{
    assert(!is_empty());
    Pattern ret_v;
    // TODO
    ret_v = _tree.item(); //ya eso devuelve el item directamente
    //
    return ret_v;
}

KDTree KDTree::left() const
{
    assert(!is_empty());
    KDTree ret_v;
    // TODO
    ret_v = KDTree(_tree.left(), _k);
    /*
    Resumen:
    ·crea un nuevo objeto KDTree utilizando el subárbol izquierdo del árbol actual y el mismo valor de _k.
    Desglose:
    ·_tree.left() devuelve el subárbol izquierdo del árbol _tree actual.
    ·KDTree(_tree.left(), _k) construye un nuevo objeto KDTree utilizando el subárbol izquierdo y el valor actual de _k.
    ·El objeto KDTree recién creado se asigna a ret_v.
    */
    //
    return ret_v;
}

KDTree KDTree::right() const
{
    assert(!is_empty());
    KDTree ret_v;
    // TODO
    ret_v = KDTree(_tree.right(), _k);
    //
    return ret_v;
}

size_t
KDTree::get_k() const
{
    size_t k = 0;
    // TODO
    k = _k;
    //
    return k;
}

KDTree::KDTree()
{
    // TODO
    _k = 0;
    _tree = BTree<Pattern>();
    /*
    ·BTree<Pattern>() crea un nuevo objeto de tipo BTree que almacena elementos de tipo Pattern.
    ·_tree = BTree<Pattern>() asigna este nuevo objeto BTree a la variable miembro _tree de la clase KDTree.
    */
    //
    assert(is_empty());
}

KDTree::KDTree(const BTree<Pattern> &tree, size_t k)
{
    // TODO
    _tree = tree;
    _k = k;
    //
}

BTree<Pattern> KDTree::btree() const
{
    BTree<Pattern> ret_v;
    // TODO
    ret_v = _tree;
    //
    return ret_v;
}

void KDTree::set_btree(const BTree<Pattern> &new_tree)
{
    // TODO
    _tree = new_tree;
    //
}

void KDTree::set_k(size_t k)
{
    // TODO
    _k = k;
    //
    assert(get_k() == k);
}

/**
 * @brief Create a level of the kdtree object.
 *
 * Create a binary tree in a recursive way splitting each dimension into two
 * parts using the median as pivot and calling recursively for each part.
 * The pivot will be the root of the binary tree.
 *
 * @param begin is the an iterator at the begin of patterns seq.
 * @param end is the an iterator at the end of patterns seq.
 * @param level is the current level of this subtree.
 * @param k is the number of dimensions of the pattern's space.
 * @return a ref to the binary tree created of this level.
 */
static BTree<Pattern>
create_kdtree(std::vector<Pattern>::iterator begin,
              std::vector<Pattern>::iterator end,
              size_t level, size_t k)
{
    BTree<Pattern> btree;
    const size_t size = std::distance(begin, end);

    if (size > 0)
    {
        // TODO

        // First: locate the median pattern.
        // Hint: use a lambda to implement the pattern comparison algorithm.
        int axis = level % k;
        auto lambda = [axis](const Pattern &a, const Pattern &b)
        {
            return a.values()[axis] < b.values()[axis];
        };
        /*
        Resumen:
        ·define una función lambda que se utiliza para comparar dos objetos Pattern basándose en un valor específico de una dimensión (eje).
        Desglose:
        ·auto lambda = [axis](const Pattern &a, const Pattern &b) define una función lambda y la asigna a la variable lambda. La lambda captura la variable axis por valor.
        ·La lambda toma dos parámetros, const Pattern &a y const Pattern &b, que son referencias constantes a objetos Pattern.
        ·return a.values()[axis] < b.values()[axis]; compara los valores de a y b en la dimensión especificada por axis y devuelve true si el valor de a es menor que el valor de b
        */
        std::sort(begin, end, lambda);
        auto median = begin + size / 2;
        /*
        ·begin + size / 2 utiliza aritmética de iteradores para avanzar desde begin hasta el elemento mediano.
        ·La razón por la que se añade begin es porque begin es un iterador que apunta al primer elemento del rango. Al sumar size / 2 a begin, se obtiene un iterador que apunta al elemento en la posición size / 2 dentro del rango, que es el elemento mediano.
        */
        // Second: create the root of the binary tree with the median pattern.
        btree = BTree<Pattern>(*median);

        // Third: Set the left and right subtrees (if needed) by recursion using
        // the begin and end iterators to set the range of the patterns for each subtree.
        // Remember: increment the level parameter.
        btree.set_left(create_kdtree(begin, median, level + 1, k)); //desde begin hasta la mediana, se crea un nuevo nivel, la dim se mantiene
        btree.set_right(create_kdtree(median + 1, end, level + 1, k)); //desde el sig de la mediana hasta el final, etc

        //
    }
    return btree;
}

void KDTree::fit(std::vector<Pattern> &dataset)
{
    assert(dataset.size() > 0);
    // TODO
    // Hint: use the create_kdtree function to create the binary tree.
    //Rebuild the kdtree to fit a new dataset.
    //se calcula con el primer nvl del árbol, ya q repr. al nodo raiz, y aque la construccion del árbol empieza por el mismo
    _tree = create_kdtree(dataset.begin(), dataset.end(), 0, dataset[0].dim());
    _k = dataset[0].dim(); 
    //
    assert(get_k() == dataset[0].dim());
}

KDTree::KDTree(std::vector<Pattern> &dataset)
{
    assert(dataset.size() > 0);
    // TODO
    // Hint: use the fit method.
    fit(dataset);
    //
    assert(dataset.size() == 0 || !is_empty());
}

KDTree::KDTree(std::istream &in) noexcept(false)
    : KDTree()
{
    // TODO
    /*_tree = BTree<Pattern>(in); 
    _k = _tree.item().dim();*/
    in >> _k;
    _tree = BTree<Pattern>(in);
    //
}

std::ostream &KDTree::fold(std::ostream &out) const
{
    // TODO
    out << _k << " "; //1º se añade la dimensión
    _tree.fold(out); //2º se añade el árbol, usamos el método ya existente en BTree
    //
    return out;
}

std::tuple<float, Pattern>
KDTree::find_nn(Pattern const &p, const KDTree::distance_function_t &dist,
                size_t level) const
{
    // Which dimension is splitted here.
    size_t axis = level % p.dim();

    Pattern curr = item();
    float curr_dist = dist(p, curr);

    auto curr2 = curr;
    auto curr2_dist = curr_dist;

    // TODO: step 1: find candidate in the corresponding subtree.
    // Hint: use std::tie to set the return values to curr2 and curr2_dist.
    if(p.values()[axis] <= curr.values()[axis] && !left().is_empty()){
        std::tie(curr2_dist, curr2) = left().find_nn(p, dist, level + 1);
    }
    else if(p.values()[axis] > curr.values()[axis] && !right().is_empty()){
        std::tie(curr2_dist, curr2) = right().find_nn(p, dist, level + 1);
    }
    //

    // TODO: step 2: update the current candidate if needed.
    /*if(curr2_dist < curr_dist){
        curr = curr2;
        curr_dist = curr2_dist;
    }*/
    if(dist(p, curr2) < dist(p, curr)){
        curr = curr2;
        curr_dist = dist(p, curr2);
    }
    //

    // TODO: step 3: find candidate in the other subtree or cut the search.
    /*if (std::abs(p.values()[axis] - curr.values()[axis]) < curr_dist){
        if (p.values()[axis] > curr.values()[axis] && !left().is_empty())
            std::tie(curr2_dist, curr2) = left().find_nn(p, dist, level + 1);
        else if (!right().is_empty())
            std::tie(curr2_dist, curr2) = right().find_nn(p, dist, level + 1);
    }*/
    if (std::abs(p.values()[axis] - item().values()[axis]) < dist(curr, p)){
        if (p.values()[axis] > item().values()[axis] && !left().is_empty())
            std::tie(curr2_dist, curr2) = left().find_nn(p, dist, level + 1);
        else if (!right().is_empty())
            std::tie(curr2_dist, curr2) = right().find_nn(p, dist, level + 1);
        
        if (dist(p, curr2) < dist(p, curr)){
            curr = curr2;
            curr_dist = dist(p, curr2);
        }
    }
    //

    // TODO: step 4: update the current candidate if needed.
    /*if (curr2_dist < curr_dist){
        curr = curr2;
        curr_dist = curr2_dist;
    }*/
    if (dist(p, curr2) < dist(p, curr)){
        curr = curr2;
        curr_dist = dist(p, curr2);
    }
    //

    return std::make_tuple(curr_dist, curr);
}

std::tuple<float, Pattern>
KDTree::find_nn(Pattern const &p, const KDTree::distance_function_t &dist) const
{
    assert(!is_empty());
    assert(p.dim() == get_k());
    return find_nn(p, dist, 0);
}
