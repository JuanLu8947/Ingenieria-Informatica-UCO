/**
 * @file prim_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <exception>
#include <limits>

#include "prim_algorithm.hpp"

template <class T>
float prim_algorithm(Graph<T, float> &g,
                     VertexIterator<T, float> &start_vertex,
                     std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false)
{
    assert(!g.is_directed());

    float total_distance = 0.0;
    mst.resize(0);

    // Create and initialize auxiliary vectors.
    auto U = get_vertices(g);
    std::vector<size_t> V(g.num_vertices());
    for (size_t i = 0; i < V.size(); ++i)
        V[i] = i;
    std::vector<bool> A(g.num_vertices(), false);
    std::vector<float> C(g.num_vertices(), std::numeric_limits<float>::infinity());

    // Find the index 'u' of the start vertex in vector U.
    size_t u = 0;
    while (U[u] != *start_vertex)
        ++u;

    // Add the start vertex to the Minimum Spanning Tree with cost 0.
    A[u] = true;
    C[u] = 0.0;

    // TODO
    // Remember: Use auxiliary vectors U, V, A and C.
    // Remember: U vector has the graph's nodes.
    // Remember: We need to find the N-1 edges.
    for (size_t i = 1; i < U.size(); ++i)
    {
        // Update distances to MST for not visited vertex using as predecessor
        // the vertex 'u'.
        for (size_t v = 0; v < U.size(); ++v)
            if (!A[v] && g.is_adjacent(U[u], U[v])){
                /*
                ·A[v] indica si el vértice v ya está en el árbol generador mínimo (MST).
                ·Solo se consideran los vértices que aún no están en el MST y que son adyacentes al vértice actual u.
                */
                auto edge = g.edge(U[u], U[v]);
                float edge_weight = edge->item();
                if (edge_weight < C[v]){
                    C[v] = edge_weight;
                    V[v] = u;
                }
                /*
                ·Si el peso de la arista es menor que el coste actual almacenado en C[v], se actualiza:
                 ·C[v] almacena el menor coste para llegar a v desde el MST.
                 ·V[v] almacena el índice del vértice predecesor desde el que se llega a v con ese menor coste.
                */
            }
        /*
        Resumen:
        Este bloque actualiza, para cada vértice no incluido aún en el MST, 
        el coste mínimo para conectarlo al árbol usando el vértice u recién añadido. 
        Así, siempre se mantiene el menor coste para conectar cada vértice al MST y desde qué vértice se haría.
        */
        //

        float least_cost = std::numeric_limits<float>::infinity();
        // Select the next vertex 'u' to add to the MST (with the least cost).
        for (size_t v = 0; v < U.size(); ++v){
            if (!A[v] && C[v] < least_cost){
                least_cost = C[v];
                u = v;
            }
        }
        /*
        En resumen:
        ·Busca el siguiente vértice a añadir al árbol generador mínimo (MST):
         ·Recorre todos los vértices del grafo (v).
         ·Solo considera los vértices que no están aún en el MST (!A[v]).
         ·De esos, busca el que tiene el menor coste para ser conectado al MST (C[v] < least_cost).
         ·Si encuentra uno con menor coste, actualiza least_cost y guarda el índice u de ese vértice.

        Este paso selecciona el vértice más barato para añadir al MST en la siguiente iteración, siguiendo la lógica de Prim: siempre añadir el vértice más cercano al árbol actual.
        ·least_cost guarda el coste mínimo encontrado en esta búsqueda.
        ·u será el índice del vértice que se añadirá al MST en la siguiente fase.

        Este bucle selecciona el próximo vértice a añadir al MST, 
        eligiendo siempre el que tiene el menor coste de conexión desde el árbol actual.
        */
        //

        assert(!A[u]); // u does not belong to the MST yet.

        if (least_cost == std::numeric_limits<float>::infinity())
            throw std::runtime_error("It is an unconnected graph.");

        // Add the found vertex to the MST.
        total_distance += least_cost;
        A[u] = true;
        mst.push_back(g.edge(U[V[u]], U[u]));
    }
    //

    return total_distance;
}
