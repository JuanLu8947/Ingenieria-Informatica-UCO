/**
 * @file a_star_algorithm.hpp
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
#include <vector>

#include <graph.hpp>

/**
 * @brief The A* algorithm.
 * Its a version of Dijkstra algorithm with an heuristic to find out the
 * the shortest path between two vertex.
 * @param[in] g is the graph.
 * @param[in] start,
 * @param[in] end are the vertices to link.
 * @param[in] H is a functional to compute a Heuristic of the distance between
 *          two vertices.
 * @param[out] predecessors is the predecesor vector.
 * @param[out] distances is the distances vector.
 * @return the number of iterations executed.
 * @pre g.has(source)
 * @pre g.has(end)
 *
 * @warning the functional H has the signature: float (Graph<T,float>::VertexRef, Graph<T,float>::VertexRef)
 */
template <class T, class Heuristic>
size_t
a_star_algorithm(Graph<T, float> &g,
                 typename Graph<T, float>::VertexRef &start,
                 typename Graph<T, float>::VertexRef &end,
                 Heuristic &H,
                 std::vector<size_t> &predecessors,
                 std::vector<float> &distances);

/**
 * @brief Retrieve a path from A*'s predecessor vector.
 * @param src is the start vertex's label.
 * @param dst is the destination vertex's label.
 * @param predecessors vector returned by the Dijkstra algorithm.
 * @return a list with the path of vertices from src to dst.
 * @pre src<predecessors.size()
 * @pre dst<predecessors.size()
 * @pre predecessor[src]==src
 */
std::list<size_t>
a_star_path(size_t src, size_t dst,
            std::vector<size_t> const &predecessors);

#include <a_star_algorithm_imp.hpp>