/**
 * @file edge_imp.hpp
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
#include <edge.hpp>

template <class T, class E>
Edge<T, E>::Edge(VertexRef const &u, VertexRef const &v, E const &data)
{
    // TODO //constructor de copia
    u_ = u;
    v_ = v;
    item_ = data;
    /*
    u y v representan a los 2 extremos de edge
    item es el peso de edge
    */
    is_visited_ = false; //SetState
    //
    assert(has(u));
    assert(has(v));
    assert(other(u) == v);
    assert(other(v) == u);
    assert(first() == u);
    assert(second() == v);
    assert(item() == data);
    assert(!is_visited());
}

template <class T, class E>
typename Edge<T, E>::Ref Edge<T, E>::create(VertexRef const &u, VertexRef const &v, E const &data)
{
    return std::make_shared<Edge<T, E>>(u, v, data);
}

template <class T, class E>
Edge<T, E>::~Edge() {}

template <class T, class E>
bool Edge<T, E>::is_visited() const
{
    // TODO: fixme
    //return false;
    return is_visited_; //GetState
    //
}

template <class T, class E>
E const &Edge<T, E>::item() const
{
    // TODO: fixme
    //return E();
    return item_; //Get
    //
}

template <class T, class E>
bool Edge<T, E>::has(VertexRef const &n) const
{
    // TODO: fixme //Is vertex n an end of this edge? //Or it € grph?
    return n == u_ || n == v_;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::other(VertexRef const &n) const
{
    assert(has(n));
    // TODO: fixme
    /*VertexRef retv;
    return retv;*/
    return (n == u_) ? v_ : u_;
    /*
    if (n == u_)
        return v_;
    else
        return u_;
    */
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::other(VertexRef const &n)
{
    assert(has(n));
    // TODO: fixme
    /*VertexRef retv;
    return retv;*/
    return (n == u_) ? v_ : u_;
    /*
    if (n == u_)
        return v_;
    else
        return u_;
    */
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::first() const
{
    // TODO: fixme
    /*VertexRef retv;
    return retv;*/
    return u_; //Get first of (u, v)
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::first()
{
    // TODO: fixme
    /*VertexRef retv;
    return retv;*/
    return u_; //Get first of (u, v)
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::second() const
{
    // TODO: fixme
    /*VertexRef retv;
    return retv;*/
    return v_; //Get second of (u, v)
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::second()
{
    // TODO: fixme
    /*VertexRef retv;
    return retv;*/
    return v_; //Get second of (u, v)
    //
}

template <class T, class E>
void Edge<T, E>::set_visited(bool new_st)
{
    // TODO
    is_visited_ = new_st; //SetState
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

template <class T, class E>
void Edge<T, E>::set_item(E const &v)
{
    // TODO
    item_ = v;
    //
    assert(item() == v);
}
