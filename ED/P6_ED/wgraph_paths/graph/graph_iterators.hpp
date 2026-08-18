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

// forward declarations
template <class T>
class Vertex;
template <class T, class E>
class Edge;
template <class T, class E>
class Graph;

template <class T, class E>
class VertexIterator
{
public:
    typename Vertex<T>::Ref &operator*() const;
    VertexIterator &operator++();
    VertexIterator operator++(int);
    VertexIterator &operator--();
    VertexIterator operator--(int);
    VertexIterator &operator=(const VertexIterator &other);
    VertexIterator &operator=(VertexIterator &&other) noexcept;
    bool operator==(const VertexIterator &other) const;
    bool operator!=(const VertexIterator &other) const;
    VertexIterator() = default;
    VertexIterator(const VertexIterator &other);
    VertexIterator(VertexIterator &&other) noexcept;

protected:
    friend class Graph<T, E>;
    VertexIterator(typename Graph<T, E>::vertices_list_t::iterator it) : it_(it) {}
    typename Graph<T, E>::vertices_list_t::iterator it_; /**< the iterator to the vertex list. */
};

template <class T, class E>
class EdgeIterator
{
public:
    typename Edge<T, E>::Ref &operator*() const;
    EdgeIterator &operator++();
    EdgeIterator &operator++(int);
    EdgeIterator &operator--();
    EdgeIterator &operator--(int);
    EdgeIterator &operator=(const EdgeIterator &other);
    EdgeIterator &operator=(EdgeIterator &&other) noexcept;
    bool operator==(const EdgeIterator &other) const;
    bool operator!=(const EdgeIterator &other) const;
    EdgeIterator() = default;
    EdgeIterator(const EdgeIterator &other);
    EdgeIterator(EdgeIterator &&other) noexcept;

protected:
    friend class Graph<T, E>;
    EdgeIterator(typename Graph<T, E>::edges_list_t::iterator it) : it_(it) {}
    typename Graph<T, E>::edges_list_t::iterator it_; /**< the iterator to the edge list. */
};

#include <graph_iterators_imp.hpp>