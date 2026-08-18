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
#include <list_iterator.hpp>

template <class T>
ListIterator<T>::~ListIterator() {}

template <class T>
bool ListIterator<T>::is_valid() const
{
    bool ret_v = false;
    // TODO: recode with respect to your representation.
    // Hint: Do not invoke node() here because that provoques an infinite recursion.
    //return node_ != nullptr; //se pordía hacer así, pero entonces tendríamos un waring por no usar ret_v
    ret_v = node_ != nullptr;
    return ret_v;
    //
}

template <class T>
ListIterator<T>::ListIterator()
{
    // TODO
    //constructor por defecto
    node_ = nullptr;
    //
    assert(!is_valid());
};

template <class T>
ListIterator<T>::ListIterator(typename DNode<T>::Ref const &n)
{
    // TODO
    node_ = n;
    //
    assert(n == nullptr || is_valid());
    assert(n != nullptr || !is_valid());
};

template <class T>
T const &ListIterator<T>::item() const
{
    assert(is_valid());
    // TODO: recode with respect to your representation.
    /*T fixme{};
    return fixme;*/
    return node_->item();
    //
}

template <class T>
ListIterator<T> ListIterator<T>::next(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO
    ret_v = *this;
    ret_v.goto_next(dist);
    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::prev(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO
    ret_v = *this;
    ret_v.goto_prev(dist);
    //
    return ret_v;
}

template <class T>
size_t ListIterator<T>::distance(ListIterator<T> const &other) const
{
    assert(is_valid());
    assert(other.is_valid());
    size_t ret_v = 0;
    // TODO
    //usa ret_v como dist
    //auto it = *this;
    auto it = node_;
    //while(it != other){
    while(it != other.node_){
        //it.goto_next(1);
        it = it -> next();
        ret_v++;
    }
    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const &o) const
{
    // TODO: recode with respect to your representation.
    // Remember: two iterators are equal if both point to the same node.
    return node_ == o.node_;
    //
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const &o) const
{
    bool ret_v = false;

    // TODO: recode with respect to your representation.
    // Remember: two iterators are equal if both point to the same node.
    //return node_ != o.node_; //aquí ocurre lo mismo
    ret_v = node_ != o.node_;
    return ret_v;
    //
}

template <class T>
void ListIterator<T>::set_item(T const &it)
{
    assert(is_valid());
    // TODO
    node_->set_item(it);
    //
}

template <class T>
void ListIterator<T>::goto_next(size_t dist)
{
    assert(is_valid());
    // TODO
    while(dist > 0){
        node_ = node_->next();
        dist--;
    }
    //
}

template <class T>
void ListIterator<T>::goto_prev(size_t dist)
{
    assert(is_valid());
    // TODO
    while(dist > 0){
        node_ = node_->prev();
        dist--;
    }
    //
}

template <class T>
typename DNode<T>::Ref ListIterator<T>::node() const
{
    typename DNode<T>::Ref ret_v;
    // TODO: recode with respect to your representation.
    return node_; //GetNode
    //
}

template <class T>
void ListIterator<T>::set_node(typename DNode<T>::Ref const &n)
{
    // TODO
    node_ = n;
    //
    assert(node() == n);
}