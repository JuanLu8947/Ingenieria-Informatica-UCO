/**
 * @file avltree_iterator_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <avltree_iterator.hpp>

template <class T>
const typename AVLTNode<T>::Ref &AVLTreeIterator<T>::node() const
{
    // TODO: recode using your representation.
    //return typename AVLTNode<T>::Ref();
    return current_node_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTreeIterator<T>::node()
{
    // TODO: recode using your representation.
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return current_node_;
    //
}

template <class T>
AVLTreeIterator<T>::AVLTreeIterator()
{
    // TODO
    current_node_ = nullptr; //constructor por defecto
    //
    assert(node() == nullptr);
}

template <class T>
AVLTreeIterator<T>::AVLTreeIterator(typename AVLTNode<T>::Ref const &node)
{
    // TODO
    current_node_ = node; //constructor de copia
    //
    assert(this->node() == node);
}

template <class T>
bool AVLTreeIterator<T>::operator==(AVLTreeIterator<T> const &other) const
{
    bool equal = false;
    // TODO
    equal = (node() == other.node());
    //
    return equal;
}

template <class T>
bool AVLTreeIterator<T>::operator!=(AVLTreeIterator<T> const &other) const
{
    bool different = false;
    // TODO
    different = (node() != other.node());
    //
    return different;
}

template <class T>
T const &AVLTreeIterator<T>::operator*() const
{
    assert(node());
    return node()->item();
}

template <class T>
const T *AVLTreeIterator<T>::operator->() const
{
    assert(node());
    return &node()->item();
}

template <class T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator++()
{
    assert(node());
    // TODO
    //++drcha
    if (node()->right() != nullptr){ //1º drcha
        current_node_ = node()->right();
        while (node()->left()) //2º full izq
            current_node_ = node()->left();
    }
    else{ //no tiene hijo drcho, se sube al padre
        auto current = node();
        auto parent = current->parent();
        
        while (parent != nullptr && current == parent->right()) {
            current = parent;
            parent = current->parent();
        }
        current_node_ = parent;
    }
    //
    return *this;
}

template <class T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator++(int)
{
    AVLTreeIterator<T> old = *this;
    ++(*this);
    return old;
}

template <class T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator--()
{
    assert(node());
    // TODO
    if(node()->left() != nullptr){ //1º izq
        current_node_ = node()->left();
        while(node()->right()) //2º full drcha 
            current_node_ = node()->right();
    }
    else{
        auto current = node();
        auto parent = current->parent();
        
        while (parent != nullptr && current == parent->left()) {
            current = parent;
            parent = current->parent();
        }
        current_node_ = parent;
    }
    //
    return *this;
}

template <class T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator--(int)
{
    AVLTreeIterator<T> old = *this;
    --(*this);
    return old;
}
