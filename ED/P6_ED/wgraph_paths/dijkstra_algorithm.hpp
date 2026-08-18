/**
 * @file dijkstra_algorithm.hpp
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
#include <list>

#include "graph.hpp"

/** @brief The Dijkstra's algorithm.
 *
 * Compute all the minimum paths to the rest of vertices from a given vertex.
 *
 * @param[in] g is a weighted graph.
 * @param[in] source is the start vertex.
 * @param[out] predecessors vector specifying for each vertex, what's the the predecessor vertex.
 * @param[out] distances vector specifying the distance from the source to each vertex.
 * @pre g.has(source)
 * @warning predecessor[n]=n means both vertex or is the start vertex,
 *          (distance[n]==0) and the vertex is not connected to the start
 *          vertex (distance[n]=inf).
 */
template <class T>
void dijkstra_algorithm(Graph<T, float> &g,
                        typename Graph<T, float>::VertexRef const &source,
                        std::vector<size_t> &predecessors,
                        std::vector<float> &distances);

/**
 * @brief Retrieve a path using the Dijkstra's predecessor vector.
 * @param[in] src is the start vertex's label.
 * @param[in] dst is the destination vertex's label.
 * @param[in] predecessors the predecessors vector returned by the Dijkstra algorithm.
 * @return a list with the path of vertex labels from src to dst.
 * @pre src<predecessors.size()
 * @pre dst<predecessors.size()
 * @pre predecessor[src]==src
 */
std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t> const &predecessors);

#include <dijkstra_algorithm_imp.hpp>