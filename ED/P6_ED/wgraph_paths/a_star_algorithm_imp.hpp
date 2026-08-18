/**
 * @file a_star_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <tuple>
#include <limits>
#include <functional>

#include <a_star_algorithm.hpp>
#include <priority_queue.hpp>

template <class T, class Heuristic>
size_t
a_star_algorithm(Graph<T, float> &g,
                 typename Graph<T, float>::VertexRef &start,
                 typename Graph<T, float>::VertexRef &end,
                 Heuristic &H,
                 std::vector<size_t> &predecessors,
                 std::vector<float> &distances)
{
    assert(g.has(start));
    assert(g.has(end));

    /** @brief the Dijkstra tuple.
     * We use the tuple (dist,u's label,v's label) format to represent an edge.
     * Remember: tuples use lexicographic comparisons.
     */
    using Tuple = std::tuple<float, float, size_t, size_t>;

    size_t iterations = 0;
    g.reset(false);

    // TODO: initialize the predecessors and distances vectors.
    // Remember: each vertex is predecessor of itself with distance infinite.
    size_t n = g.num_vertices();
    predecessors.resize(n);
    distances.resize(n);

    for(size_t i = 0; i < n; i++){
        predecessors[i] = i;
        distances[i] = std::numeric_limits<float>::infinity();
    }
    
    distances[start->label()] = 0.0;
    /*
    Resumen
    ·Marca que al principio no se conoce ningún camino a ningún vértice (excepto el de inicio).
    ·Permite que el algoritmo vaya actualizando las distancias y predecesores a medida que encuentra caminos más cortos.

    ·Prepara los vectores de distancias y predecesores para todos los vértices.
    ·Inicializa todas las distancias a infinito, excepto la del inicio, que es 0.
    ·Inicialmente, cada vértice es su propio predecesor.
    */
    //

    // TODO: implement the A* algorithm.
    // Note: you can use std::priority_queue if you have not implemented
    // the ADT PriorityQueue.
    std::vector<Tuple> queue_data;
    PriorityQueue<Tuple> q(queue_data, std::less<Tuple>());
    
    float h_start = H(start, end);
    q.enqueue(std::make_tuple(h_start, 0.0f, start->label(), start->label()));
    
    g.reset(false); 

    while (!q.is_empty() && !end->is_visited()) {
        iterations++;
        
        Tuple t = q.front();
        q.dequeue();
        
        auto u = g.vertex(std::get<2>(t));
        
        if (!u->is_visited()) {
            predecessors[std::get<2>(t)] = std::get<3>(t);
            distances[std::get<2>(t)] = std::get<1>(t);
            
            u->set_visited(true);

            /*
            ·Mientras la cola no esté vacía y el destino no haya sido visitado:
             ·Saca la tupla con menor coste estimado total.
             ·Obtiene el vértice actual u.
             ·Si u no ha sido visitado:
              ·Actualiza su predecesor y la distancia mínima conocida.
              ·Marca u como visitado.
            */
            
            auto u_it = g.get_iterator(u);
            for (auto e_it = g.edges_begin(u_it); e_it != g.edges_end(u_it); ++e_it) {
                auto v = (*e_it)->other(u);
                
                if (!v->is_visited()) {
                    float new_dist = std::get<1>(t) + (*e_it)->item();
                    float h_v = H(v, end);
                    
                    q.enqueue(std::make_tuple(new_dist + h_v, new_dist, v->label(), std::get<2>(t)));
                }
            }
            /*
            ·Para cada arista que sale de u:
             ·Obtiene el vértice vecino v.
             ·Si v no ha sido visitado:
              ·Calcula la nueva distancia real desde el inicio hasta v (new_dist).
              ·Calcula la heurística desde v hasta el destino (h_v).
              ·Inserta en la cola la tupla
            */
        }
    }
    /*
    Resumen
    ·El algoritmo A* explora los caminos más prometedores primero, usando una heurística para estimar el coste restante hasta el destino.
    ·Actualiza distancias y predecesores igual que Dijkstra, pero prioriza los nodos según g + h.
    ·Cuando el destino es visitado, se puede reconstruir el camino más corto usando el vector de predecesores.
    */
    //
    return iterations;
}

inline std::list<size_t>
a_star_path(size_t src, size_t dst,
            std::vector<size_t> const &predecessors)
{
    assert(src < predecessors.size());
    assert(dst < predecessors.size());
    assert(predecessors[src] == src);
    std::list<size_t> path;
    // TODO
    if(src == dst){ //Si el origen y el destino son el mismo vértice, el camino es solo ese vértice.
        path.push_back(src);
        return path;
    }

    if(predecessors[dst] == dst && src != dst)
        return path;
    /*
    Sin camino:
    ·Si el predecesor de dst es él mismo y el origen y destino son distintos, significa que no hay camino desde src hasta dst.
    ·Devuelve una lista vacía.
    */

    size_t current = dst;

    while(current != src){
        path.push_front(current);
        current = predecessors[current];
    }
   
    path.push_front(src);
    /*
    Reconstrucción del camino:
    ·Empieza desde el destino (dst).
    ·Añade cada vértice al principio de la lista (push_front), siguiendo los predecesores.
    ·Repite hasta llegar al origen (src).
    ·Finalmente, añade el origen al principio del camino.


    Resumen
    ·Devuelve una lista ordenada con los labels de los vértices que forman el camino más corto desde src hasta dst.
    ·Si no hay camino, devuelve una lista vacía.

    ·Si origen y destino son iguales, el camino es solo ese vértice.
    ·Si no hay camino, devuelve vacío.
    ·Si hay camino, lo reconstruye desde el destino hasta el origen usando el vector de predecesores, y lo devuelve en orden correcto (de origen a destino).
    */
    //
    return path;
}
