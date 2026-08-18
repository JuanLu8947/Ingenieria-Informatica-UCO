/**
 * @file graph_traversals.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <list>
#include <graph.hpp>

/**
 * @brief Depth first scanning of a graph.
 *
 * The traversal starts from the first vertex and continues until all the vertices
 * have been processed.
 *
 * @param g is the graph.
 * @param p is a functional to process a spanning tree edge.
 *
 * @warning p must accept the interface
 * 'void (typename Graph<T,E>::VertexRef & v, typename Graph<T,E>::VertexRef & u)'
 * meaning process 'v' arriving from 'u'
 */
template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g, Processor &p);

/**
 * @brief Breadth first scanning of a graph.
 *
 * The traversal starts from the first vertex and continues until all the vertices
 * have been processed.
 *
 * @param g is the graph.
 * @param p is a functional to process a spanning tree edge.
 *
 * @warning p must accept the interface
 * 'void (typename Graph<T,E>::VertexRef & v, typename Graph<T,E>::VertexRef & u)'
 * meaning process 'v' arriving from 'u'
 */
template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, Processor &p);

/**
 * @brief Topological sorting of a graph.
 *
 * @param[in,out] g is the directed acyclic graph.
 * @param[in,out] sorting saves the topological sorting of the vertices.
 *
 * @pre g is directed.
 * @pre g is acyclic.
 */
template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         std::list<typename Graph<T, E>::VertexRef> &sorting);

#include <wgraph_traversals_imp.hpp>