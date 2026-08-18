/**
 * @file graph_traversals_imp.hpp
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
#include <stack>
#include <queue>

#include <wgraph_traversals.hpp>

/**
 * @brief Depth first scanning of a graph from a given vertex.
 *
 * The traversal starts/continue from the vertex @a v arriving from @a u.
 * Only the connected component including this vertices will be traversed.
 *
 * @param g is the graph.
 * @param v is the vertex used to continue the traversal.
 * @param u is the predecessor vertex of v.
 * @param p is a functional to process a spanning tree edge.
 *
 * @warning p must accept the interface
 * 'void (typename Graph<T,E>::VertexRef & v, typename Graph<T,E>::VertexRef & u)'
 * meaning process 'v' arriving from 'u'
 */
template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g,
                      VertexIterator<T, E> &v,
                      VertexIterator<T, E> &u,
                      Processor &p)
{
    assert(!(*v)->is_visited());
    // TODO
    // Remember: we apply a prefix processing of nodes.
    // Hint: use and edge iterator to scan the edges incident on the vertex 'v'.
    (*v)->set_visited(true);
    p(*v, *u);

    auto v_it = g.get_iterator(*v);
    auto e_it = g.edges_begin(v_it);
    auto e_end = g.edges_end(v_it);

    while (e_it != e_end){
        auto w = (*e_it)->other(*v);
        if (!w->is_visited()){
            auto w_it = g.get_iterator(w);
            depth_first_scan(g, w_it, v, p);
        }
        ++e_it;
    }
    /*
    Este bloque implementa el recorrido en profundidad (DFS) desde un vértice v (llegando desde u).
    ·Marca el vértice como visitado.
    ·Aplica el procesador p en modo prefijo (antes de explorar hijos).
    ·Itera sobre las aristas incidentes a v usando un iterador de aristas.
    ·Para cada vecino no visitado, llama recursivamente a DFS.
    */
    //
}

template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: reset the visited flags to false.
    // Remember: to mark the start of the traversal, 'u' arriving
    // from 'u' must be indicated.
    g.reset(false);

    auto v_it = g.vertices_begin();
    auto v_end = g.vertices_end();

    while (v_it != v_end){
        if (!(*v_it)->is_visited())
            depth_first_scan(g, v_it, v_it, p);
        
        ++v_it;
    }
    /*
    Este bloque implementa el recorrido en profundidad para todo el grafo:
    ·Resetea todos los flags de visitado a false (para empezar de cero).
    ·Recorre todos los vértices; si alguno no está visitado, inicia DFS desde él.
    ·Para marcar el inicio, se llama a la versión recursiva con el mismo vértice como origen y destino (u llegando desde u).
    */
    //
}

/**
 * @brief Breadth first scanning of a graph.
 *
 * The traversal starts from the given vertex. Only the connected
 * component including this vertex will be traversed.
 *
 * @param g is the graph.
 * @param start_v is the scanning start vertex.
 * @param u is the predecessor vertex of v.
 * @param p is a functional to process a spanning tree edge.
 *
 * @warning p must accept the interface
 * 'void (typename Graph<T,E>::VertexRef & v, typename Graph<T,E>::VertexRef & u)'
 * meaning process 'v' arriving from 'u'
 */
template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, VertexIterator<T, E> &start_v,
                        Processor &p)
{
    assert(!(*start_v)->is_visited());

    // TODO
    // Remember: we need to use a std::queue to process the vertices.
    // Hint: enqueue a pair <v,u> to mark the vertex 'v' arriving from
    // vertex 'u'.
    // Hint: to enqueue the start vertex u with the pair <u,u>
    std::queue<std::pair<VertexIterator<T, E>, VertexIterator<T, E>>> q;
    (*start_v)->set_visited(true);
    p(*start_v, *start_v);
    q.push(std::make_pair(start_v, start_v));

    while (!q.empty()){
        auto current = q.front();
        auto v = current.first;
        q.pop();

        auto v_it = g.get_iterator(*v);
        auto e_it = g.edges_begin(v_it);
        auto e_end = g.edges_end(v_it);

        while (e_it != e_end){
            auto w = (*e_it)->other(*v);
            if (!w->is_visited()){
                auto w_it = g.get_iterator(w);
                w->set_visited(true);
                p(w, *v);
                q.push(std::make_pair(w_it, v));
            }
            ++e_it;
        }
    }
    /*
    Este bloque implementa el recorrido en anchura (BFS) desde un vértice:
    ·Usa una cola (std::queue) para procesar los vértices.
    ·Encola pares <v, u> para saber desde qué vértice se llega a cada uno.
    ·Marca el vértice inicial como visitado y lo procesa.
    ·Mientras la cola no esté vacía, saca el siguiente vértice, explora sus vecinos no visitados, los marca y los encola.
    */
    //
}

template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: reset to false the visited flags.
    g.reset(false);

    auto v_it = g.vertices_begin();
    auto v_end = g.vertices_end();

    while (v_it != v_end){
        if (!(*v_it)->is_visited())
            breadth_first_scan(g, v_it, p);

        ++v_it;
    }
    /*
    Este bloque implementa el recorrido en anchura para todo el grafo
    ·Resetea todos los flags de visitado a false.
    ·Recorre todos los vértices; si alguno no está visitado, inicia BFS desde él.
    */
    //
}

/**
 * @brief Helper function to do the topological sorting.
 *
 * @param g is the directed acyclic graph.
 * @param u is the vertex to continue the traversal.
 * @param sorting is the sorted vertices list.
 */
template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         VertexIterator<T, E> &u,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(!(*u)->is_visited());
    // TODO
    // Remember: use edge iterator to traverse the edges incident in u.
    // Remember: we apply a postfix processing of nodes.
    (*u)->set_visited(true);

    auto u_it = g.get_iterator(*u); 
    auto e_it = g.edges_begin(u_it);
    auto e_end = g.edges_end(u_it);

    while (e_it != e_end){
        auto w = (*e_it)->other(*u);
        if (!w->is_visited()){
            auto w_it = g.get_iterator(w);
            topological_sorting(g, w_it, sorting);
        }
        ++e_it;
    }

    sorting.push_front(*u);
    /*
    Este bloque implementa el recorrido para ordenación topológica desde un vértice:
    ·Marca el vértice como visitado.
    ·Usa un iterador de aristas para recorrer los vecinos.
    ·Para cada vecino no visitado, llama recursivamente.
    ·Al terminar de explorar los vecinos, añade el vértice al principio de la lista (postfijo).
    */
    //
}

template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(g.is_directed());
    // TODO
    // Remember: reset the visited flags to false.
    g.reset(false);

    auto v_it = g.vertices_begin();
    auto v_end = g.vertices_end();
    
    while (v_it != v_end){
        if (!(*v_it)->is_visited())
           topological_sorting(g, v_it, sorting);
        
        ++v_it;
    }
    /*
    Este bloque implementa la ordenación topológica para todo el grafo:
    ·Resetea todos los flags de visitado a false.
    ·Recorre todos los vértices; si alguno no está visitado, inicia la ordenación topológica desde él.
    */
    //
}