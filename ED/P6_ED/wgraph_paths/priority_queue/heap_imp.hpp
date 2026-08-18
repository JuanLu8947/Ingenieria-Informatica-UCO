/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <exception>
#include <cassert>
#include <algorithm>
#include <heap.hpp>

/**
 * @brief Compute the parent's index of a given child.
 *
 * @param i is the index of the child in the heap.
 * @return size_t
 */
inline size_t parent(size_t i)
{
    assert(i > 0);
    //  TODO: fixme
    //return 0;
    return (i-1)/2; //ec invertida
    /*
    El nodo en el índice i tiene:
    ·Su padre en el índice (i-1)/2 (división entera).
    ·Su hijo izquierdo en el índice 2*i + 1.
    ·Su hijo derecho en el índice 2*i + 2.
    
    La fórmula (i-1)/2 funciona porque:
    ·En un heap, el índice del padre de un nodo hijo se encuentra dividiendo el índice del hijo entre 2 (en base 0).
    ·Restar 1 antes de dividir ajusta la fórmula para que funcione correctamente con la indexación basada en 0.
    
    Representación:
    ·std::vector<T> *values_; //< A reference to the array of values
    ·size_t last_item_;       //< The index of the next leaf to be used regarding a complete binary tree.
    ·Comp comp_;              //< The comparison functor to use.
    */
    //
}

/**
 * @brief Compute the left child's index of a given parent.
 *
 * @param i is the index of the parent in the heap.
 * @return the index of the left child.
 */
inline size_t left(size_t i)
{
    // TODO: fixme
    //return 0;
    return 2*i+1;
    //
}

/**
 * @brief Compute the right child's index of a given parent.
 *
 * @param i is the index of the parent in the heap.
 * @return the index of the right child.
 */
inline size_t right(size_t i)
{
    // TODO: fixme
    //return 0;
    return 2*i+2;
    //
}

template <class T>
void Heap<T>::shift_up(size_t i)
{
    // TODO
    if(i>0 && comp_(values_->at(i), values_->at(parent(i)))){
        std::swap(values_->at(i), values_->at(parent(i)));
        shift_up(parent(i));
    }
    /*
    Condición i > 0:
    ·Verifica que el índice i no sea la raíz del heap (la raíz está en el índice 0 y no tiene padre).
    
    Uso del método at():
    ·Pertenece a std::vector y se utiliza para acceder a los elementos del vector de manera segura.
    */
    //
}

template <class T>
void Heap<T>::shift_down(size_t i)
{
    // TODO
    size_t n = i, lC = left(i), rC = right(i);
    //lC: índice izq    //rC: índice drcho
    //i: índice del nodo
    //last_item: The index of the next leaf to be used 
    //comp: comparison functor
    if(lC < last_item_ && comp_(values_->at(lC), values_->at(n)))
        n = lC;
    if(rC < last_item_ && comp_(values_->at(rC), values_->at(n)))
        n = rC;
    if(i != n){
        std::swap(values_->at(i), values_->at(n)); //swap: intercambia valores 
        shift_down(n);
    }
    //
}

template <class T>
bool Heap<T>::is_a_heap(size_t root) const
{
    bool ret_val = true;
    // TODO
    // Remember: the tree is a heap if both children are heaps and the root is
    // comp(parent, child) if true for both children.
    // Remember: a leaf is a heap.
    //last_item_ representa el tamaño actual del heap o el índice del próximo lugar disponible.
    if(root < last_item_){ //Verifica si el índice root está dentro del rango válido del heap.
        size_t lC = left(root), rC = right(root); //lC = left(root) -> Calcula el índice del hijo izquierdo del nodo en el índice root utilizando la función left
        if(lC < last_item_){ //Verifica si el índice del hijo izquierdo (lC) está dentro del rango válido del heap.
            ret_val = ret_val && is_a_heap(lC);
            ret_val = ret_val && comp_(values_->at(root), values_->at(lC));
        }
        if(rC < last_item_){
            ret_val = ret_val && is_a_heap(rC);
            ret_val = ret_val && comp_(values_->at(root), values_->at(rC));
        }
    }
    //
    return ret_val;
}

template <class T>
void Heap<T>::heapify()
{
    // TODO
    // Remember: we want O(N) here.
    for (int i=(size()/2)-1; i>=0; i--) //mediana
        shift_down(i);
    //
    assert(is_a_heap());
}

template <class T>
Heap<T>::Heap(std::vector<T> &values, Comp const &comp) : values_(&values), comp_(comp)
{
    // TODO
    // Hint: use the heapify function
    //Constructor + heapify
    values_ = &values;
    last_item_ = values.size(); //last_item_ es el tamaño del heap
                                //The index of the next leaf to be used
    comp_ = comp;
    heapify();
    //
    assert(is_a_heap());
    assert(size() == values.size());
}

template <class T>
Heap<T>::~Heap()
{
}

template <class T>
bool Heap<T>::is_empty() const
{
    // TODO: fixme
    //return true;
    //return values_->empty(); //empty() método de std::vector
    return last_item_ == 0; //El heap está vacío si no hay elementos
    //
}

template <class T>
size_t Heap<T>::size() const
{
    // TODO: fixme
    //return 0;
    //return values_->size(); //size() método de std::vector
    return last_item_; //El tamaño del heap es el número de elementos
                    //usamos last_item como size, ya que es como el end
    //
}

template <class T>
T const &Heap<T>::item() const
{
    assert(!is_empty());
    // TODO: fixme
    //return T{};
    return values_->at(0); //Devolvemos el primer elemento del heap
    //
}

template <class T>
void Heap<T>::insert(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    // Remember: we are using a dynamic array, so we need to check if the array
    // is full to push_back the new value if it is needed.
    if(last_item_ == values_->size())
        values_->push_back(new_it);
    else{
        values_->at(last_item_) = new_it;
    }
    last_item_++;
    shift_up(last_item_ - 1);
    //
    assert(is_a_heap());
    assert(size() == old_size + 1);
}

template <class T>
void Heap<T>::remove()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(!is_empty());
    // TODO
    if (!is_empty()){
        std::swap(values_->at(0), values_->at(last_item_ - 1));
        last_item_--;
        shift_down(0);
    }
    //
    assert(is_a_heap());
    assert(size() == old_size - 1);
}

template <class T>
void heapsort(std::vector<T> &values, std::function<bool(T const &a, T const &b)> const &comp)
{
    // TODO
    // Remember: we want O(N log N) here.
    Heap<T> heap(values, comp);
    while(!heap.is_empty())
        heap.remove();
    //
#ifndef NDEBUG
    for (size_t i = 1; i < values.size(); ++i)
        assert(comp(values[i], values[i - 1]));
#endif
}