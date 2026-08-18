/**
 * @file dijkstra_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <tuple>
#include <functional>
#include <limits>

#include <dijkstra_algorithm.hpp>
#include <priority_queue.hpp>

template <class T>
void dijkstra_algorithm(Graph<T, float> &g,
                        typename Graph<T, float>::VertexRef const &source,
                        std::vector<size_t> &predecessors,
                        std::vector<float> &distances)
{
    assert(g.has(source));

    /** @brief the Dijkstra tuple.
     * We use the tuple (dist,u's label,v's label) format to represent an edge.
     * Remember: tuples use lexicographic comparisons.
     */
    using Tuple = std::tuple<float, size_t, size_t>;

    // Reset visited flags.
    g.reset(false);

    // TODO: initialize the predecessors and distances vectors.
    // Remember: each vertex is predecessor of itself with distance infinite.
    size_t n = g.num_vertices();
    predecessors.resize(n);
    distances.resize(n);
    
    for(size_t i = 0; i < n; i++){
        predecessors[i] = i; //Inicialmente, cada vértice es su propio predecesor (esto se irá actualizando durante el algoritmo).
        distances[i] = std::numeric_limits<float>::infinity(); //La distancia mínima conocida a cada vértice se inicializa como infinito
    }
    
    distances[source->label()] = 0.0;
    /*
    ¿Para qué sirve esto?
    Esta inicialización es fundamental para el algoritmo de Dijkstra:
    ·Marca que al principio no se conoce ningún camino a ningún vértice (excepto el origen).
    ·Permite que el algoritmo vaya actualizando las distancias y predecesores a medida que encuentra caminos más cortos.

    Resumen
    ·Prepara los vectores de distancias y predecesores para todos los vértices.
    ·Inicializa todas las distancias a infinito, excepto la del origen, que es 0.
    ·Inicialmente, cada vértice es su propio predecesor.
    */
    //

    // TODO: implement the Dijkstra algorithm.
    // Note: you can use std::priority_queue if you have not implemented
    // the ADT PriorityQueue.
    std::vector<Tuple> queue_data;
    PriorityQueue<Tuple> q(queue_data, std::less<Tuple>());
    
    q.enqueue(std::make_tuple(0.0f, source->label(), source->label()));
    /*
    parámetros:
    ·distancia desde el origen a sí mismo es 0, vértice origen, su propio predecesor (al principio es él mismo).
    */

    while(!q.is_empty()){
        Tuple t = q.front(); //Se toma la tupla con menor distancia (t).
        q.dequeue(); 
        
        auto u = g.vertex(std::get<1>(t)); //Se obtiene el vértice u correspondiente a esa tupla.
        
        if(!u->is_visited()){
            predecessors[std::get<1>(t)] = std::get<2>(t); //Se actualiza su predecesor y su distancia mínima conocida.
            distances[std::get<1>(t)] = std::get<0>(t);

            u->set_visited(true); //se hace para no volver a visitarlo.

            auto u_iter = g.get_iterator(u);
            for(auto e_iter = g.edges_begin(u_iter); e_iter != g.edges_end(u_iter); ++e_iter){
                auto v = (*e_iter)->other(u);
                if(!v->is_visited()){
                    float new_dist = distances[u->label()] + (*e_iter)->item();
                    q.enqueue(std::make_tuple(new_dist, v->label(), u->label()));
                }
            }
        }
        /*
        ·Calcula la nueva distancia desde el origen hasta v pasando por u.
        ·Inserta en la cola la tupla (nueva distancia, v, u) para que se procese más adelante si es el camino más corto.
        */
    }
    /*
    Resumen
    ·Explora el grafo desde el origen, siempre expandiendo primero el vértice con menor distancia conocida.
    ·Actualiza las distancias mínimas y los predecesores de cada vértice.
    ·Marca los vértices como visitados para no procesarlos más de una vez.
    ·Usa una cola de prioridad para garantizar que siempre se expande el camino más corto disponible.

    ·Saca el vértice más cercano no visitado.
    ·Actualiza distancias y predecesores.
    ·Añade a la cola los vecinos alcanzables con la nueva distancia.
    ·Repite hasta que todos los vértices alcanzables han sido procesados.
    Así, al final, los vectores distances y predecessors contienen el camino más corto desde el origen a cada vértice.
    */
    //
}

inline std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t> const &predecessors)
{
    assert(src < predecessors.size());
    assert(dst < predecessors.size());
    assert(predecessors[src] == src);
    std::list<size_t> path;
    // TODO
    // Remember: if the destination is unreachable, return an empty list.
    if(predecessors[dst] == dst) //Si el predecesor de dst es él mismo, significa que no hay camino desde el origen hasta el destino (dst es inalcanzable). En ese caso, devuelve una lista vacía.
        return path;

    size_t current = dst;

    while(current != src){
        path.push_front(current);
        current = predecessors[current];
    }
    /*
    Reconstrucción del camino:
    ·Empieza desde el destino (dst).
    ·Añade cada vértice al principio de la lista (push_front), siguiendo los predecesores.
    ·Repite hasta llegar al origen (src).
    */

    path.push_front(src);

    if(src == dst) //Si el origen y el destino son el mismo vértice, añade el origen también al final (esto puede ser útil para representar caminos de longitud cero).
        path.push_back(src);

    /*
    Resumen
    ·Devuelve una lista ordenada con los labels de los vértices que forman el camino más corto desde src hasta dst.
    ·Si no hay camino, devuelve una lista vacía
    
    ·Si no hay camino, devuelve vacío.
    ·Si hay camino, lo reconstruye desde el destino hasta el origen usando el vector de predecesores.
    ·El resultado es el camino más corto en orden correcto (de origen a destino).
    */
    //
    return path;
}
