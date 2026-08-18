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
#include <list_node.hpp>

template <class T>
bool DNode<T>::is_dummy() const
{
    // TODO: recode with respect to your representation.
    return _item == nullptr; 
    //si el item es nullptr es un nodo dummy
    //al crearse un nodo se crea vacío con únicamente un nodo dummy que es de la forma [prev,  , next]
    //
}

template <class T>
DNode<T>::DNode()
{
    // TODO
    _item = nullptr; //válido tb para punteros
    _next = nullptr;
    _prev = nullptr;
    //
    assert(is_dummy());
}

template <class T>
DNode<T>::DNode(T const &it)
{
    // TODO
    _item = std::make_shared<T>(it);
    _next = nullptr; //el nullptr es como el NULL de C, es una forma de incializar
    _prev = nullptr;
    //
    assert(!is_dummy());
    assert(next() == nullptr);
    assert(prev() == nullptr);
}

template <class T>
DNode<T>::DNode(T const &it, Ref next_n)
{
    // TODO
    _item = std::make_shared<T>(it);
    _next = next_n;
    _prev = nullptr; //lo suyo es poner todos los que se comprueban en los assert
    //
    assert(!is_dummy());
    assert(next() == next_n);
    assert(prev() == nullptr);
}

template <class T>
DNode<T>::DNode(T const &it, Ref next_n, Ref prev_n)
{
    // TODO
    _item = std::make_shared<T>(it);
    _next = next_n;
    _prev = prev_n;
    //
    assert(!is_dummy());
    assert(next() == next_n);
    assert(prev() == prev_n);
}

template <class T>
typename DNode<T>::Ref DNode<T>::create()
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>());
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::create(T const &it)
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>(it));
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::create(T const &it, Ref const &next_n)
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>(it, next_n));
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::create(T const &it, Ref const &next_n, Ref const &prev_n)
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>(it, next_n, prev_n));
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::This()
{
    return This_;
}

template <class T>
DNode<T>::~DNode()
{
    // TODO
    // Hint: if std::shared_ptr is used for the references,
    //   there is nothing todo.

    //
}

template <class T>
T const &DNode<T>::item() const
{
    assert(!is_dummy());

    // TODO: recode with respect to your representation.
    /*T fixme{};
    return fixme;*/   //GetItem
    return *_item; //item es un puntero, se necesita el *
    //
}

template <class T>
typename DNode<T>::Ref DNode<T>::prev() const
{
    // TODO: recode with respect to your representation.
    return _prev; //GetPrev
    //
}

template <class T>
typename DNode<T>::Ref DNode<T>::next() const
{
    // TODO: recode with respect to your representation.
    return _next; //GetNext
    //
}

template <class T>
void DNode<T>::set_item(const T &new_it)
{
    // TODO
    //_item = new_it; eso pero hay que hacer una conversión
    _item = std::make_shared<T>(new_it);
    /*
    ·std::make_shared<T>(new_it): Crea un nuevo std::shared_ptr que gestiona un objeto de tipo T inicializado con new_it. std::make_shared es una función que asigna memoria y construye un objeto de tipo T, devolviendo un std::shared_ptr que gestiona esa memoria.
    ·_item: Es el miembro de la clase DNode que almacena el puntero compartido al objeto de tipo T.
    ·= std::make_shared<T>(new_it): Asigna el nuevo std::shared_ptr creado a _item
    */
    //
}

template <class T>
void DNode<T>::set_prev(DNode<T>::Ref n)
{
    // TODO
    _prev = n;
    //
    assert(n == prev());
}

template <class T>
void DNode<T>::set_next(DNode<T>::Ref n)
{
    // TODO
    _next = n;
    //
    assert(n == next());
}
