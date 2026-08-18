/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include <btree_utils.hpp>

template <class T>
int compute_height(const BTree<T> &t)
{
    int height = 0;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    /*height = -1; //se inicializa el cáñculo -> árbol vacío
    if(!t.is_empty()){
        int max_height = -1; ///same
        for(int i = 0; i < ; i++){
            //maxH =
        }
        height = max_height + 1;
    }*/
    if (t.is_empty())
        height = -1;
    else{
        height = 1 + std::max(compute_height<T>(t.left()), compute_height<T>(t.right()));
    }
    /*
    ·compute_height<T>(t.left()) llama recursivamente a compute_height para calcular la altura del subárbol izquierdo.
    ·compute_height<T>(t.right()) llama recursivamente a compute_height para calcular la altura del subárbol derecho.
    ·std::max(compute_height<T>(t.left()), compute_height<T>(t.right())) toma el máximo de las alturas de los subárboles izquierdo y derecho.
    ·1 + std::max(...) añade 1 al máximo de las alturas de los subárboles para incluir la raíz actual en la altura total.
    En resumen, esta línea de código calcula la altura de un árbol binario sumando 1 al máximo de las alturas de sus subárboles izquierdo y derecho. La función compute_height se llama recursivamente hasta que alcanza los nodos hoja, y luego combina los resultados para obtener la altura total del árbol.
    */
    //
    return height;
}

template <class T>
size_t compute_size(const BTree<T> &t)
{
    size_t ret_val = 0;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    /*if(!t.is_empty()){
        ret_val = 1;
        for(int i = 0; i < t.arity(); i++){
            //size +=
        }
    }*/
    if (!t.is_empty())
        ret_val = 1 + compute_size<T>(t.left()) + compute_size<T>(t.right());
    /*
    ·Si el árbol no está vacío, se calcula el tamaño de los subárboles izquierdo y derecho.
    ·compute_size<T>(t.left()) llama recursivamente a compute_size para calcular el tamaño del subárbol izquierdo.
    ·compute_size<T>(t.right()) llama recursivamente a compute_size para calcular el tamaño del subárbol derecho
    ·1 + compute_size<T>(t.left()) + compute_size<T>(t.right()) suma 1 (para el nodo actual) al tamaño de los subárboles izquierdo y derecho.
    En resumen, esta línea de código calcula el tamaño de un árbol binario sumando 1 (para el nodo actual) al tamaño de sus subárboles izquierdo y derecho. La función compute_size se llama recursivamente hasta que alcanza los nodos hoja, y luego combina los resultados para obtener el tamaño total del árbol.
    */
    //
    return ret_val;
}

template <class T, typename Processor>
bool prefix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    /*
    if(!tree.is_empty()){
        //
    }
    //implementado como lambda?
    */
    if (!tree.is_empty()){
        retVal = retVal && p(tree.item());
        /*
        ·Se aplica el procesador p al elemento del nodo actual (tree.item()).
        ·p(tree.item()) devuelve un valor booleano que se asigna a retVal.
        ·Si p(tree.item()) devuelve false, retVal será false y el procesamiento se detendrá.
        */
        retVal = retVal && prefix_process<T, Processor>(tree.left(), p);
        /*
        ·Se llama recursivamente a prefix_process para procesar el subárbol izquierdo.
        ·retVal se actualiza con el resultado de la llamada recursiva.
        ·Si retVal ya es false, el operador && asegura que no se realicen más llamadas recursivas.
        */
        retVal = retVal && prefix_process<T, Processor>(tree.right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool infix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    /*
    if(!tree.is_empty()){
        //
    }
    //implementado como lambda?
    */
    if (!tree.is_empty()){
        retVal = infix_process<T, Processor>(tree.left(), p);
        /*
        ·Se llama recursivamente a infix_process para procesar el subárbol izquierdo.
        ·retVal se actualiza con el resultado de la llamada recursiva.
        ·Si retVal es false, el operador && asegura que no se realicen más llamadas recursivas.
        */
        retVal = retVal && p(tree.item());
        /*
        ·Se aplica el procesador p al elemento del nodo actual (tree.item()).
        ·p(tree.item()) devuelve un valor booleano que se asigna a retVal.
        ·Si p(tree.item()) devuelve false, retVal será false y el procesamiento se detendrá.
        */
        retVal = retVal && infix_process<T, Processor>(tree.right(), p);
        /*
        ·Se llama recursivamente a infix_process para procesar el subárbol derecho.
        ·retVal se actualiza con el resultado de la llamada recursiva.
        ·Si retVal es false, el operador && asegura que no se realicen más llamadas recursivas.
        */
    }
    //
    return retVal;
}

template <class T, class Processor>
bool postfix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    /*
    if(!tree.is_empty()){
        //
    }
    //implementado como lambda?
    */
    if (!tree.is_empty()){
        retVal = postfix_process<T, Processor>(tree.left(), p);
        /*
        ·Se llama recursivamente a postfix_process para procesar el subárbol izquierdo.
        ·retVal se actualiza con el resultado de la llamada recursiva.
        ·Si retVal es false, el operador && asegura que no se realicen más llamadas recursivas.
        */
        retVal = retVal && postfix_process<T, Processor>(tree.right(), p);
        /*
        ·Se llama recursivamente a postfix_process para procesar el subárbol derecho.
        ·retVal se actualiza con el resultado de la llamada recursiva.
        ·Si retVal es false, el operador && asegura que no se realicen más llamadas recursivas.
        */
        retVal = retVal && p(tree.item());
        /*
        ·Se aplica el procesador p al elemento del nodo actual (tree.item()).
        ·p(tree.item()) devuelve un valor booleano que se asigna a retVal.
        ·Si p(tree.item()) devuelve false, retVal será false y el procesamiento se detendrá.
        */
    }
    //
    return retVal;
}

template <class T, class Processor>
bool breadth_first_process(const BTree<T> &tree, Processor &p)
{
    bool go_on = true;
    // TODO
    // Hint: think about which data structure can help you to do this kind
    //   of traversal.
    std::queue<BTree<T>> q;
    BTree<T> subtree;
    q.push(tree); //metemos el árbol recibido pr param en la cola
    while (!q.empty() && go_on){
        subtree = q.front();
        q.pop();
        if (!subtree.is_empty()){
            go_on = p(subtree.item());
            q.push(subtree.left());
            q.push(subtree.right());
        }
    }
    //
    return go_on;
}

template <class T>
std::ostream &
print_prefix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a prefix_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto lambda = [&out](const T &item) -> bool
    {
        /*
        ·La lambda captura la referencia out por referencia (&out), lo que permite que la lambda escriba en el flujo de salida out.
        */
        out << item << " ";
        return true;
    };
    prefix_process<T>(tree, lambda);
    //
    return out;
}

template <class T>
std::ostream &
print_infix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use an infix_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto lambda = [&out](const T &item) -> bool
    {
        out << item << " ";
        return true;
    };
    infix_process<T>(tree, lambda);
    //
    return out;
}

template <class T>
std::ostream &
print_postfix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a postfix_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto lambda = [&out](const T &item) -> bool
    {
        out << item << " ";
        return true;
    };
    postfix_process<T>(tree, lambda);
    //
    return out;
}

template <class T>
std::ostream &
print_breadth_first(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a breadth_first_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto lambda = [&out](const T &item) -> bool
    {
        out << item << " ";
        return true;
    };
    breadth_first_process<T>(tree, lambda);
    //
    return out;
}

template <class T>
bool search_prefix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the prefix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto lambda = [&it, &found, &count](const T &item) -> bool
    {
        /*
        ·La lambda captura las variables it, found y count por referencia (&).
        ·it es el elemento que se está buscando.
        ·found es una variable booleana que indica si el elemento ha sido encontrado.
        ·count es un contador que lleva la cuenta del número de elementos procesados
        */
        count++;
        if (item == it)
            found = true;
            
        return !found;
    };
    prefix_process<T>(tree, lambda);
    //
    return found;
}

template <class T>
bool search_infix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the infix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto lambda = [&it, &found, &count](const T &item) -> bool
    {
        count++;
        if (item == it)
            found = true;

        return !found;
    };
    infix_process<T>(tree, lambda);
    //
    return found;
}

template <class T>
bool search_postfix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the postfix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto lambda = [&it, &found, &count](const T &item) -> bool
    {
        count++;
        if (item == it)
            found = true;
        return !found;
    };
    postfix_process<T>(tree, lambda);
    //
    return found;
}

template <class T>
bool search_breadth_first(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the breadth_first_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto lambda = [&it, &found, &count](const T &item) -> bool
    {
        count++;
        if (item == it)
            found = true;
        return !found;
    };
    breadth_first_process<T>(tree, lambda);
    //
    return found;
}

template <class T>
bool check_btree_in_order(const BTree<T> &tree)
{
    bool ret_val = true;
    // TODO
    // Hint: You can create a lambda function with a parameter to compare it with
    //  the last the value seen.
    //  Use the lambda with the infix_process.
    std::vector<T> v;
    auto lambda = [&v, &ret_val](const T &item) -> bool
    {
        /*
        ·La lambda captura las variables v y ret_val por referencia (&).
        ·v es un vector que se utiliza para almacenar los elementos del árbol a medida que se procesan.
        ·ret_val es una variable booleana que indica si los elementos están en orden.
        */
        v.push_back(item);
        //return std::is_sorted(v.begin(), v.end());
        /*+ librerias
        ·#include <algorithm>
        ·#include <vector>
        <*/
        for (size_t i = 1; i < v.size(); ++i){
            if (v[i - 1] >= v[i])
                ret_val = false;
            else if(v[i - 1] < v[i])
                ret_val = true;
        }
        return ret_val;
    };
    ret_val = infix_process<T>(tree, lambda);
    //
    return ret_val;
}

template <class T>
bool has_in_order(const BTree<T> &tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    bool ret_val = false;
    // TODO
    if (tree.is_empty())
        return false;
    if (v < tree.item())
        ret_val = has_in_order<T>(tree.left(), v);
    else if (v > tree.item())
        ret_val = has_in_order<T>(tree.right(), v);
    else{
        ret_val = true;
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(BTree<T> &&tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    // TODO
    if (tree.is_empty())
        tree.create_root(v);

    if (v < tree.item()){
        if (tree.left().is_empty()){
            auto left = BTree<T>(v);
            tree.set_left(left);
        }
        else{
            insert_in_order<T>(tree.left(), v);
        }
    }
    else if (v > tree.item()){
        if (tree.right().is_empty()){
            BTree<T> right = BTree<T>(v);
            tree.set_right(right);
        }
        else{
            insert_in_order<T>(tree.right(), v);
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}

template <class T>
void insert_in_order(BTree<T> &tree, T const &v)
{
    insert_in_order(std::move(tree), v);
}