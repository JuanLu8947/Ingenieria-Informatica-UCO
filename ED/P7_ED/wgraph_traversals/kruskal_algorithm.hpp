/**
 * @file kruskal_algorithm.hpp
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
#include <tuple>

#include "graph.hpp"

/**
 * @brief The Kruskal's algorithm.
 * Compute the minimum spanning tree.
 * @arg[in] g is the graph.
 * @arg[out] mst is the list of edges of g that forms the minium spanning tree.
 * @return the total weight of the minimum spanning tree.
 * @pre g is an undirected connected graph.
 * @throw std::runtime_error("It is a unconnected graph.") if the input graph
 *        is an unconnected one.
 */
template <class T>
float kruskal_algorithm(Graph<T, float> &g,
                        std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false);

#include "kruskal_algorithm_imp.hpp"