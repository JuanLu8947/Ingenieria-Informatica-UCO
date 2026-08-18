/**
 * @file kruskal_algorithm_imp.hpp
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
#include <memory>
#include <algorithm>

#include "disjointsets.hpp"
#include "kruskal_algorithm.hpp"

template <class T>
float kruskal_algorithm(Graph<T, float> &g,
                        std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false)
{
    float total_distance = 0.0;

    DisjointSets sets(g.num_vertices());

    // Generate a set for each node.
    for (size_t i = 0; i < g.num_vertices(); ++i)
        sets.make_set(i);

    auto edges = get_edges(g);

    // Sort the edges using the comparison function.
    auto compare = [](const typename Graph<T, float>::EdgeRef &a,
                      const typename Graph<T, float>::EdgeRef &b) -> bool
    {
        bool ret_v = false;
        // TODO: implement the comparison function.
        // Remember: the edge is seen as a tuple (weight,first_key,second_key).
        // Remember: compare(a,b) must return true if edge a must be before
        // edge b using lexicographic order.
        if (a->item() < b->item())
            ret_v = true;
        else if (a->item() == b->item()){
            if (a->first()->label() < b->first()->label())
                ret_v = true;
            else if (a->first()->label() == b->first()->label() && 
                     a->second()->label() < b->second()->label())
                ret_v = true;
        }
        /*
        Esta función compara dos aristas (a y b) para ordenarlas de forma lexicográfica según:
        1.Peso de la arista (item()):
         ·Si el peso de a es menor que el de b, a va antes.
        2.Etiqueta del primer vértice (first()->label()):
         ·Si los pesos son iguales, compara la etiqueta del primer vértice de cada arista.
         ·Si la de a es menor, a va antes.
        3.Etiqueta del segundo vértice (second()->label()):
         ·Si también son iguales, compara la etiqueta del segundo vértice.
         ·Si la de a es menor, a va antes.
        En resumen:
        ·se garantiza un orden total y estable para las aristas, necesario para que Kruskal funcione correctamente y, en caso de empate, 
         siempre elija la misma arista.
        ·El orden lexicográfico asegura que, si hay varias aristas con el mismo peso, se elige la que conecta los vértices con etiquetas menores.

        Este bloque implementa la comparación lexicográfica (peso, primer vértice, segundo vértice) entre dos aristas, 
         que es el criterio estándar para ordenar aristas en el algoritmo de Kruskal.
        */
        //
        return ret_v;
    };
    std::sort(std::begin(edges), std::end(edges), compare);

    // TODO: implement the Kruskal algorithm.
    // Remember: use 'DisjointSets::find(u_label)' method to find the "color"
    // of vertex u and DisjointSets::joint(u_label, v_label) to join the subset
    // with vertex u->label() with the subset with vertex v.
    mst.resize(0);
    for (size_t i = 0; i < edges.size() && mst.size() < g.num_vertices()-1; ++i){
        auto u = edges[i]->first();
        auto v = edges[i]->second();
        if (sets.find(u->label()) != sets.find(v->label())){
            sets.joint(u->label(), v->label());
            mst.push_back(edges[i]);
            total_distance += edges[i]->item();
        }
    }
    if (mst.size() < g.num_vertices()-1)
        throw std::runtime_error("It is an unconnected graph.");
    /*
    1.Inicializa el MST vacío:
     Se asegura de que el vector de aristas del árbol generador mínimo (MST) esté vacío antes de empezar.
    2.Recorre las aristas ordenadas:
     El bucle recorre todas las aristas ordenadas por peso (y en caso de empate, por etiquetas de vértices),
      pero se detiene cuando el MST tiene N-1 aristas (N es el número de vértices).
    3.Para cada arista:
    ·Obtiene los dos extremos de la arista: u y v.
    ·Comprueba si u y v están en conjuntos diferentes usando la estructura de conjuntos disjuntos (DisjointSets).
     Esto significa que añadir esta arista no formará un ciclo.
    ·Si están en conjuntos diferentes:
     ·Une ambos conjuntos (sets.joint).
     ·Añade la arista al MST.
     ·Suma el peso de la arista al coste total.
    4.Comprueba si el grafo es conexo:
     Si al final el MST no tiene N-1 aristas, significa que el grafo no es conexo y lanza una excepción.
    
    En resumen:
    Este bloque implementa el núcleo del algoritmo de Kruskal: recorre las aristas más baratas y las añade al MST solo si no forman ciclo, 
    hasta obtener un árbol generador mínimo o detectar que el grafo no es conexo.
    */
    //

    // TODO: check if the graph is connected and throw
    // std::runtime_error("It is an unconnected graph.") exception if it is not.
    // Remember: In a connected graph th MST will have N-1 edges (N is the number of vertices).
    if (mst.size() < g.num_vertices()-1)
        throw std::runtime_error("It is an unconnected graph.");
    /*
    Esto garantiza que solo se acepta un MST válido si el grafo es conexo. 
    no es posible construir un árbol generador mínimo en un grafo no conexo.
    */
    //

    assert(mst.size() == g.num_vertices() - 1);
    return total_distance;
}
