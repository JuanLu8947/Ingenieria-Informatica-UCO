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
#include <sstream>

#include <btree_node.hpp>

template <class T>
BTNode<T>::BTNode(T const &it, const BTNode<T>::Ref &l,
                  const BTNode<T>::Ref &r)
{
    // TODO
    //constructor de toda la vida con asserts
    item_ = it;
    left_ = l;
    right_ = r;
    //
    assert(item() == it);
    assert(left() == l);
    assert(right() == r);
}

template <class T>
typename BTNode<T>::Ref BTNode<T>::create(T const &it,
                                          const BTNode<T>::Ref &left,
                                          const BTNode<T>::Ref &right)
{
    return typename BTNode<T>::Ref(new BTNode<T>(it, left, right));
}

template <class T>
const T &BTNode<T>::item() const
{
    // TODO: implement this method with respect to your representation.
    /*T fixme;
    return fixme;*/
    return item_; //Get
    //
}

template <class T>
typename BTNode<T>::Ref BTNode<T>::left() const
{
    typename BTNode<T>::Ref child;
    // TODO
    child = left_; //obtener el hijo subarbol izq
    //
    return child;
}

template <class T>
typename BTNode<T>::Ref BTNode<T>::right() const
{
    typename BTNode<T>::Ref child;
    // TODO
    child = right_; //igual pero con right
    //
    return child;
}

template <class T>
void BTNode<T>::set_item(const T &new_it)
{
    // TODO
    item_ = new_it; //setear el item, comprob assert
    //
    assert(item() == new_it);
}

template <class T>
void BTNode<T>::set_left(const BTNode<T>::Ref &new_child)
{
    // TODO
    left_ = new_child; //para ssert, y para asignar vaya
    //
    assert(left() == new_child);
}

template <class T>
void BTNode<T>::set_right(const BTNode<T>::Ref &new_child)
{
    // TODO
    right_ = new_child; //igual que antes
    //
    assert(right() == new_child);
}
