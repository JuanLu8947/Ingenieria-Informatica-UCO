/**
 * @file graph_iterators.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <graph_iterators.hpp>

template <class T, class E>
typename Vertex<T>::Ref &VertexIterator<T, E>::operator*() const
{
    return it_->first;
}

template <class T, class E>
VertexIterator<T, E> &VertexIterator<T, E>::operator++()
{
    ++it_;
    return *this;
}
template <class T, class E>
VertexIterator<T, E> VertexIterator<T, E>::operator++(int)
{
    VertexIterator tmp = *this;
    ++it_;
    return tmp;
}
template <class T, class E>
VertexIterator<T, E> &VertexIterator<T, E>::operator--()
{
    --it_;
    return *this;
}
template <class T, class E>
VertexIterator<T, E> VertexIterator<T, E>::operator--(int)
{
    VertexIterator tmp = *this;
    --it_;
    return tmp;
}
template <class T, class E>
VertexIterator<T, E> &VertexIterator<T, E>::operator=(const VertexIterator &other)
{
    it_ = other.it_;
    return *this;
}
template <class T, class E>
VertexIterator<T, E> &VertexIterator<T, E>::operator=(VertexIterator &&other) noexcept
{
    it_ = std::move(other.it_);
    return *this;
}
template <class T, class E>
bool VertexIterator<T, E>::operator==(const VertexIterator &other) const
{
    return it_ == other.it_;
}
template <class T, class E>
bool VertexIterator<T, E>::operator!=(const VertexIterator &other) const
{
    return !(it_ == other.it_);
}
template <class T, class E>
VertexIterator<T, E>::VertexIterator(const VertexIterator &other) : it_(other.it_) {}
template <class T, class E>
VertexIterator<T, E>::VertexIterator(VertexIterator &&other) noexcept : it_(std::move(other.it_)) {}

template <class T, class E>
typename Edge<T, E>::Ref &EdgeIterator<T, E>::operator*() const
{
    return *it_;
}
template <class T, class E>
EdgeIterator<T, E> &EdgeIterator<T, E>::operator++()
{
    ++it_;
    return *this;
}
template <class T, class E>
EdgeIterator<T, E> &EdgeIterator<T, E>::operator++(int)
{
    EdgeIterator tmp = *this;
    ++it_;
    return tmp;
}
template <class T, class E>
EdgeIterator<T, E> &EdgeIterator<T, E>::operator--()
{
    --it_;
    return *this;
}
template <class T, class E>
EdgeIterator<T, E> &EdgeIterator<T, E>::operator--(int)
{
    EdgeIterator tmp = *this;
    --it_;
    return tmp;
}
template <class T, class E>
EdgeIterator<T, E> &EdgeIterator<T, E>::operator=(const EdgeIterator &other)
{
    it_ = other.it_;
    return *this;
}
template <class T, class E>
EdgeIterator<T, E> &EdgeIterator<T, E>::operator=(EdgeIterator &&other) noexcept
{
    it_ = std::move(other.it_);
    return *this;
}
template <class T, class E>
bool EdgeIterator<T, E>::operator==(const EdgeIterator &other) const
{
    return it_ == other.it_;
}
template <class T, class E>
bool EdgeIterator<T, E>::operator!=(const EdgeIterator &other) const
{
    return !(it_ == other.it_);
}

template <class T, class E>
EdgeIterator<T, E>::EdgeIterator(const EdgeIterator &other) : it_(other.it_) {}
template <class T, class E>
EdgeIterator<T, E>::EdgeIterator(EdgeIterator &&other) noexcept : it_(std::move(other.it_)) {}
