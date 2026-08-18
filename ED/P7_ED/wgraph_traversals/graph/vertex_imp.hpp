/**
 * @file vertex_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <vertex.hpp>

template <class T>
Vertex<T>::Vertex(size_t l, T const &data)
{
    // TODO //constructor de copia por defecto
    label_ = l; //id-vertex
    item_ = data; //info de vertex(string, int, etc.)
    is_visited_ = false;
    //
    assert(label() == l);
    assert(item() == data);
    assert(!is_visited());
}

template <class T>
typename Vertex<T>::Ref Vertex<T>::create(size_t l, T const &data)
{
    return std::make_shared<Vertex<T>>(l, data);
}

template <class T>
const T &Vertex<T>::item() const
{
    // TODO: fixme
    //return T{};
    return item_; //Get
    //
}

template <class T>
size_t Vertex<T>::label() const
{
    // TODO: fixme
    //return 0;
    return label_; //Get
    //
}

template <class T>
bool Vertex<T>::is_visited() const
{
    // TODO: fixme
    //return false;
    return is_visited_; //GetState
    //
}

template <class T>
void Vertex<T>::set_item(T const &v)
{
    // TODO
    item_ = v;
    //
    assert(item() == v);
}

template <class T>
void Vertex<T>::set_visited(bool new_st)
{
    // TODO
    is_visited_ = new_st; //SetState
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}
