/**
 * @file prim_algorithm.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <vector>

#include "graph.hpp"

/**
 * @brief The Prim's algorithm.
 * The Prim's algorithm create the minimum spanning tree on an undirected
 * weighted graph.
 * @arg[in] g is the graph.
 * @arg[in] start_vertex is the vertex from which the algorithm starts (the root of the mst).
 * @arg[out] mst is the list of edges of g that forms the minium spanning tree.
 * @return the total weight of the minimum spanning tree.
 * @pre g.is_undirected()
 * @throw std::runtime_error("It is an unconnected graph.") if the input graph
 *        is an unconnected one.
 */
template <class T>
float prim_algorithm(Graph<T, float> &g,
                     VertexIterator<T, float> &start_vertex,
                     std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false);

#include "prim_algorithm_imp.hpp"