/**
 * @file floyd_algorithm.hpp
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
#include <map>
#include <graph.hpp>
#include <matrix.hpp>


/**
 * @brief Search for the minium path between vertices using the Floyd's algorithm.
 * @param[in] g is a weighted graph.
 * @param[out] D is the Distances matrix.
 * @param[out] I is the Intermediate matrix using D indexes.
 */
template <class T>
void floyd_algorithm(Graph<T, float> const &g,
                     FMatrix &D,
                     IMatrix &I);

/**
 * @brief Given the Floyd's Intermidiate matrix, compute the path.
 * @param[in] src is the label of the start vertex.
 * @param[in] dst is the label of the end vertex.
 * @param[in] I is the Floyd's Intermidiate matrix.
 * @return the path as list with the sequence of vertex's labels for
 *           the minimum path linking u with v.
 * @pre u and v are connected (D[src,dst]<inf).
 */
std::list<size_t> floyd_path(size_t src, size_t dst, const IMatrix &I);

#include <floyd_algorithm_imp.hpp>
