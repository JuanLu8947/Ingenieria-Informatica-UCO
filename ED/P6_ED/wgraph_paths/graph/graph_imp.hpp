/**
 * @file graph_imp.hpp
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
#include <graph.hpp>

template <class T, class E>
Graph<T, E>::Graph(bool directed)
{
    next_label_ = 0;

    // TODO //constructor por defecto + copia
    vertices_.clear(); //inicializamos la lista de vertices
    is_directed_ = directed; //inicializamos el atributo que indica si es dirigido o no
    //

    assert(is_empty());
    assert(!directed || is_directed());
    assert(directed || !is_directed());
}

template <class T, class E>
bool Graph<T, E>::is_empty() const
{
    // TODO: fixme
    // Remember: the graph is empty if there are not vertices.
    //return false;
    return vertices_.empty(); //usamos el método empty de la STL
    //
}

template <class T, class E>
bool Graph<T, E>::is_directed() const
{
    // TODO: fixme
    //return false;
    return is_directed_; //este almacena si se trata se un grafo dirigido
    //
}

template <class T, class E>
size_t Graph<T, E>::num_vertices() const
{
    // TODO: fixme
    //return 0; //vertices_ es una lista de pares
    return vertices_.size(); //usamos el método size de la STL
    //
}

template <class T, class E>
size_t Graph<T, E>::num_edges() const
{
    size_t ret_v = 0;
    // TODO
    // Remember: is the graph is undirected the edge (u:v) was duplicated in
    // the incident list of u an v.
    for(auto it = vertices_.begin(); it != vertices_.end(); ++it) //Cuenta todas las aristas sumando las listas de adyacencia de cada vértice.
        ret_v += it->second.size();
    /*
    ·second es el segundo elemento del std::pair que almacena cada entrada en la lista vertices_ del grafo.
    std::list<std::pair<VertexRef, edges_list_t>> vertices_:
     Donde:
     ·first es el vértice (VertexRef)
     ·second es la lista de aristas incidentes a ese vértice (edges_list_t)
    */
    
    if (!is_directed())
        ret_v /= 2; // Si el grafo no es dirigido, dividimos entre 2, ya que pasa 2 veces por cada arista, debido a que el camino se lo permite
    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::has(VertexRef const &u) const
{
    assert(u != nullptr);
    // TODO: fixme
    // Hint: use vertex() to find the vertex with u's label.
    //return false;
    return vertex(u->label()) != nullptr; // Verificamos si el vértice existe.
    /*
    u->label():
    ·llama al método label() del objeto al que apunta el puntero inteligente u (que es un VertexRef, es decir, un std::shared_ptr<Vertex<T>>).
    ·Este método devuelve el identificador único (label_) del vértice u dentro del grafo.
    En resumen:
    ·u->label() devuelve el número (ID) que identifica de forma única al vértice u en el grafo.
    */
    //
}

template <class T, class E>
bool Graph<T, E>::has(EdgeRef const &e) const
{
    assert(e != nullptr);
    assert(has(e->first()));
    assert(has(e->second()));
    bool ret_v = false;
    // TODO
    // Hint: use get_iterator() to get an iterator points to the first vertex.
    auto u_iter = get_iterator(e->first()); //Busca el iterador al vértice origen de la arista e (es decir, el primer extremo de la arista).
    auto e_iter = edges_begin(u_iter); //Obtiene un iterador al principio de la lista de aristas incidentes al vértice u (el origen de la arista).

    while(e_iter != edges_end(u_iter) && !ret_v){
        if((*e_iter)->other(e->first()) == e->second())
            ret_v = true;

        ++e_iter;
    }
    /*Recorre todas las aristas incidentes al vértice u:
    ·e_iter != edges_end(u_iter): mientras no lleguemos al final de la lista de aristas.
    ·!ret_v: y mientras no hayamos encontrado la arista buscada.
    
    if((*e_iter)->other(e->first()) == e->second())
    ·Para cada arista, comprueba si el otro extremo de la arista es igual al segundo vértice de e.
    ·Es decir, busca una arista que conecte exactamente los mismos vértices que e
    
    ret_v = true;
    ·Si encuentra la arista, marca ret_v como true.

    ++e_iter;
    ·Avanza al siguiente elemento de la lista de aristas.
    */
    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::is_adjacent(VertexRef const &u, VertexRef const &v) const
{
    assert(has(u));
    assert(has(v));

    // TODO: fixme
    // Remember: a vertex u is adjacent to v if there is a edge (u,v) or
    // if the graph is undirected, there is a edge (v,u).
    // Hint: use the method edge(x, y).
    //return false;
    return edge(u, v) != nullptr; // Verificamos si existe una arista entre los vértices u y v.
    //
}

template <class T, class E>
typename Graph<T, E>::EdgeRef Graph<T, E>::edge(VertexRef const &u,
                                                VertexRef const &v) const
{
    assert(has(u));
    assert(has(v));
    EdgeRef ret_v = nullptr;

    // TODO
    // Remember: if the graph is undirected, the edge (u,v) is the same as (v,u).
    // Hint: use vertex and edge iterators.
    auto u_iter = get_iterator(u); //Busca el iterador al vértice u en la lista de vértices del grafo.

    for(auto e_iter = edges_begin(u_iter); e_iter != edges_end(u_iter); ++e_iter)
        if((*e_iter)->other(u) == v){
            ret_v = *e_iter;
            break;
        }
    /*
    ·Recorre todas las aristas incidentes al vértice u.
    ·Para cada arista, comprueba si el otro extremo es v
    ·Si encuentra la arista que conecta u y v, la guarda en ret_v y sale del bucle.
    */
    
    if(ret_v == nullptr && !is_directed_){
        auto v_iter = get_iterator(v);
        for(auto e_iter = edges_begin(v_iter); e_iter != edges_end(v_iter); ++e_iter)
            if((*e_iter)->other(v) == u){
                ret_v = *e_iter;
                break;
            }
    }
    /*
    ·Si no se encontró la arista en el primer bucle y el grafo es no dirigido, busca también en la lista de aristas de v.
    ·en grafos no dirigidos, la arista puede estar almacenada en la lista de adyacencia de cualquiera de los dos vértices, con lo que se vuelve una tarea necesaria
    ·Se repite el proceso: busca si alguna arista de v conecta con u.
    
    ¿Por qué es así?:
    ·En grafos dirigidos, la arista solo existe en la lista de adyacencia del vértice origen (u).
    ·En grafos no dirigidos, la arista puede estar en la lista de adyacencia de u o de v, por eso se buscan ambas posibilidades.
    
    Resumen:
    ·Busca una arista entre u y v.
    ·Si el grafo es dirigido, solo busca en las aristas de u.
    ·Si es no dirigido, busca en las aristas de u y, si no la encuentra, también en las de v.
    ·Si la encuentra, la devuelve; si no, devuelve nullptr.
    */
    //

    assert(!ret_v || (!is_directed() || ret_v->first() == u));
    assert(!ret_v || (!is_directed() || ret_v->second() == v));
    assert(!ret_v || (is_directed() || ret_v->has(u)));
    assert(!ret_v || (is_directed() || ret_v->other(u) == v));
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::reset(bool state)
{
    // TODO
    // Remember: Both vertices and edges has a visited flag to be reset.
    for(auto v_it = vertices_begin(); v_it != vertices_end(); ++v_it){ //Recorre todos los vértices del grafo
        (*v_it)->set_visited(state); //Marca el vértice como visitado o no visitado
        for(auto e_it = edges_begin(v_it); e_it != edges_end(v_it); ++e_it) //Recorre todas las aristas incidentes a ese vértice
            (*e_it)->set_visited(state); //Marca cada arista como visitada o no visitada
    }
    /*
    Este método resetea el estado de visitado de todos los vértices y todas las aristas del grafo.
    
    Resumen
    ·Marca todos los vértices y todas las aristas del grafo como visitados (true) o no visitados (false), según el valor de state.
    ·Es una forma de "poner a cero" el grafo antes de un recorrido o después de usarlo.
    */
    //
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::find_vertex(typename T::key_t const &value) const
{
    VertexRef ret_v = nullptr;
    // TODO
    for(auto it = vertices_.begin(); it != vertices_.end(); ++it) //Recorre todos los vértices del grafo
        if(it->first->item().key() == value){ //Comprueba si la clave del vértice coincide con value
            ret_v = it->first; //Si encuentra el vértice, lo guarda y termina el bucle
            break;
        }
    /*
    ·Sirve para buscar un vértice en el grafo a partir de una clave única (por ejemplo, el nombre de una ciudad, un identificador, etc.).
    ·Devuelve una referencia al vértice si lo encuentra, o nullptr si no existe.

    Resumen:
    ·Recorre todos los vértices.
    ·Busca el primero cuya clave coincida con value.
    ·Si lo encuentra, lo devuelve; si no, devuelve nullptr.
    */
    //
    assert(ret_v == nullptr || ret_v->item().key() == value);
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::vertex(size_t value) const
{
    VertexRef ret_v = nullptr;
    // TODO
    for(auto it = vertices_.begin(); it != vertices_.end(); ++it) //Recorre todos los vértices del grafo
        if(it->first->label() == value){ //Comprueba si la etiqueta del vértice coincide
            ret_v = it->first;
            break;
        }
    //
    assert(ret_v == nullptr || ret_v->label() == value);
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::add_vertex(T const &v)
{
#ifndef NDEBUG
    size_t old_next_label = next_label_;
#endif

    VertexRef ret_v = nullptr;
    // TODO
    // Remember: use push_back to add the vertex to the list of vertices.
    // Remember: updated the next label attribute to next integer.
    ret_v = Vertex<T>::create(next_label_, v);
    vertices_.push_back(std::make_pair(ret_v, edges_list_t()));
    ++next_label_;
    /*
    ·Se crea un vért.
    ·Se añade a la lista de vértices del grafo.
    ·Se incrementa el atributo next_label_ para que el siguiente vértice tenga una etiqueta única.
    */
    //
    assert(next_label_ == (old_next_label + 1));
    assert(ret_v->label() == (old_next_label));
    assert(has(ret_v));
    assert(ret_v->item() == v);
    assert(!ret_v->is_visited());
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::remove_vertex(const VertexRef &v)
{
    assert(has(v));
#ifndef NDEBUG
    auto old_num_vertices = num_vertices();
#endif
    // TODO
    // Remember: you must also remove all edges incident in this vertex.
    // Remember: if the graph is undirected, the edge (u,v) was duplicated in
    // the incident list of u and v.
    for(auto v_it = vertices_begin(); v_it != vertices_end();){ //Recorre todos los vértices del grafo
        if(*v_it == v){ //Si el vértice actual es el que queremos eliminar (v), simplemente avanza al siguiente y usa continue para saltar el resto del bucle (no hace nada con él en esta pasada).
            ++v_it;
            continue; //permite saltar a la siguiente iteración
        }
        auto e_it = find_first(v_it, v->item().key()); //Para los demás vértices, busca si existe una arista que los conecte con v usando find_first.
        
        if(e_it != edges_end(v_it)) //Si encuentra una arista que conecta el vértice actual con v, la elimina usando remove_edge(*v_it, v).
            remove_edge(*v_it, v);
        ++v_it;
    }
    //En un grafo, para eliminar un vértice correctamente, primero hay que eliminar todas las aristas que lo conectan con otros vértices (tanto entrantes como salientes).
    
    auto it = vertices_.begin();
    while(it != vertices_.end()){ //Recorre la lista de vértices del grafo
        if(it->first == v){ //Cuando encuentra el vértice v, lo elimina de la lista usando erase y sale del bucle.
            it = vertices_.erase(it);
            break;
        }
        ++it;
    }

    /*
    Resumen:
    ·Elimina todas las aristas que conectan a v con otros vértices.
    ·Elimina el propio vértice v de la lista de vértices del grafo.
    Así, el vértice y todas sus conexiones desaparecen completamente del grafo.
    */
    //
    assert(!has(v));
    assert(num_vertices() == (old_num_vertices - 1));
}

template <class T, class E>
typename Graph<T, E>::EdgeRef Graph<T, E>::add_edge(VertexRef const &u, VertexRef const &v, E const &item)
{
    assert(has(u));
    assert(has(v));

#ifndef NDEBUG
    auto old_num_edges = num_edges();
#endif

    EdgeRef ret_v = nullptr;

    // TODO
    // Remember: if the graph is directed, the edge only is incident on
    // the u end but if it is not directed, the edge is incident on both u and v ends.
    // Hint: use get_iterator() to get the iterator to
    //   the adjacent list of vertices u and v.
    // Remember: We add the new edge to the end of adjacent lists.
    ret_v = Edge<T, E>::create(u, v, item); //Se crea una nueva arista (Edge) entre los vértices u y v, con el dato item
    auto u_iter = get_iterator(u); //se añade la arista a la lista de adyacencia de u
    u_iter.it_->second.push_back(ret_v);
    /*
    ·Se obtiene el iterador al vértice u en la lista de vértices del grafo.
    ·u_iter.it_->second es la lista de aristas incidentes a u.
    ·Se añade la nueva arista a esa lista.
    */

    if(!is_directed()){ //Si el grafo no es dirigido, la arista también se añade a la lista de adyacencia de v.
        auto v_iter = get_iterator(v);
        v_iter.it_->second.push_back(ret_v);
    }
    /*
    ¿Por qué así?
    ·En grafos dirigidos, la arista solo se almacena en la lista de adyacencia del vértice origen (u).
    ·En grafos no dirigidos, la arista se almacena en las listas de ambos extremos (u y v), porque no hay dirección y ambos pueden ser origen o destino.
    
    Resumen
    ·Crea una arista entre u y v con el dato item.
    ·Añade la arista a la lista de aristas de u.
    ·Si el grafo es no dirigido, también la añade a la lista de aristas de v.
    Así, la arista queda correctamente registrada en la estructura interna del grafo.
    */
    //
    assert(num_edges() == (old_num_edges + 1));
    assert(!ret_v->is_visited());
    assert(ret_v->first() == u);
    assert(ret_v->second() == v);
    assert(ret_v->item() == item);
    assert(ret_v->has(u));
    assert(ret_v->has(v));
    assert(ret_v->other(u) == v);
    assert(ret_v->other(v) == u);
    assert(is_adjacent(u, v));
    assert(is_directed() || is_adjacent(v, u));
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::remove_edge(VertexRef const &u, VertexRef const &v)
{
    assert(has(u));
    assert(has(v));
#ifndef NDEBUG
    auto old_num_edges = num_edges();
#endif
    // TODO
    // Remember: if the graph is undirected, the edge u-v was duplicated as
    // incident in the u and v adjacent lists.
    auto u_iter = get_iterator(u); //Buscar y eliminar la arista en la lista de adyacencia de u
    auto& u_edges = u_iter.it_->second;
    auto e_it = u_edges.begin();
    /*
    auto u_iter = get_iterator(u);
    ·Busca el iterador al vértice u en la lista de vértices del grafo.

    auto& u_edges = u_iter.it_->second;
    ·Accede a la lista de aristas incidentes a u.

    auto e_it = u_edges.begin();
    ·Prepara un iterador para recorrer esa lista.
    */

    while(e_it != u_edges.end() && ((*e_it)->other(u) != v))
        ++e_it;
    /*
    Para cada arista, comprueba si el otro extremo es v ((*e_it)->other(u) == v).
    Si la encuentra, sale del bucle.
    */

    if(e_it != u_edges.end())//Si la arista se encuentra (e_it != u_edges.end()), se elimina de la lista de aristas de u
        u_edges.erase(e_it);
    
    if(!is_directed()){ //Si el grafo es no dirigido, eliminar también en la lista de v
        auto v_iter = get_iterator(v);
        auto& v_edges = v_iter.it_->second;
        auto e_it = v_edges.begin();

        while(e_it != v_edges.end() && ((*e_it)->other(v) != u))
            ++e_it;

        if(e_it != v_edges.end())
            v_edges.erase(e_it);
    }
    /*
    Resumen
    ·Elimina la arista entre u y v de la lista de aristas de u.
    ·Si el grafo es no dirigido, también la elimina de la lista de aristas de v.
    Así, la arista desaparece completamente del grafo.
    */
    //
    assert(!is_adjacent(u, v));
    assert(num_edges() == (old_num_edges - 1));
}

template <class T, class E>
std::ostream &
Graph<T, E>::fold(std::ostream &out) const
{
    // TODO
    // Remember: to fold and edge we use item().key() to fold the edge's ends.
    if(is_directed_)
        out << "DIRECTED" << std::endl;
    else
        out << "UNDIRECTED" << std::endl;

    auto vertices = get_vertices(*this); //Obtiene todos los vértices del grafo y escribe cuántos hay.
    out << vertices.size() << std::endl;

    /*for(auto it = vertices.begin(); it != vertices.end(); ++it)
        out << (*it)->item() << std::endl;*/
    for(auto v : vertices) //Escribe la información de cada vértice (el dato que almacena cada vértice, por ejemplo, el nombre de una ciudad).
        out << v->item() << std::endl;
    
    auto edges = get_edges(*this);
    out << edges.size() << std::endl;

    for(auto e : edges){
        auto source_key = e->first()->item().key();
        auto target_key = e->second()->item().key();
        auto weight = e->item();
        out << source_key << " " << target_key << " " << weight << std::endl;
    }
    /*
    Para cada arista, escribe:
    ·La clave del vértice origen (source_key)
    ·La clave del vértice destino (target_key)
    ·El dato de la arista (weight, por ejemplo, el peso)
    Todo en una línea, separado por espacios.
    
    Resumen:
    Este método permite guardar el grafo en un formato de texto plano, que luego puede ser leído para reconstruir el grafo
    ·Escribe si el grafo es dirigido o no.
    ·Escribe el número de vértices y sus datos.
    ·Escribe el número de aristas y los extremos y dato de cada una.
    */
    //
    return out;
}

template <class T, class E>
Graph<T, E>::Graph(std::istream &in) noexcept(false)
{
    // TODO
    // Remember: Throw std::runtime_error("Wrong graph") when detecting a wrong
    //           input format.
    // Remember: key_t type is used to unfold the edge's ends.

    // TODO
    // Reset the next label attribute to 0.
    next_label_ = 0;
    //

    // TODO
    // First: is it directed or undirected?
    std::string graph_type;
    in >> graph_type;
    
    if(graph_type == "DIRECTED")
        is_directed_ = true;
    else if(graph_type == "UNDIRECTED")
        is_directed_ = false;
    else{
        throw std::runtime_error("Wrong graph");
    }
    //

    size_t size = 0;
    // TODO
    // Second: get the number of vertices and create a Graph with this capacity.
    in >> size;
    if(in.fail() || size < 0)
        throw std::runtime_error("Wrong graph");

    vertices_.clear();
    //

    // TODO
    // Third: load the N data items and add a vertex for each one.
    for(size_t i = 0; i < size; ++i){ //size es el número de vértices que se leyó previamente del flujo de entrada, se repite por cada vértice.
        T data; //tipo de dato que almacena cada vértice,
        in >> data;

        if(in.fail())
            throw std::runtime_error("Wrong graph");
        
        add_vertex(data);
    }
    //

    size_t n_edges = 0;

    // TODO
    // Fourth: load the number of edges.
    in >> n_edges;
    
    if(in.fail() || n_edges < 0)
        throw std::runtime_error("Wrong graph");
    //

    // TODO
    // Fifth: load the N edges.
    // Remember: Use T::key_t type to unfold the edge's end keys.
    // Hint: use find_vertex(T::key_t) to get a reference to the vertex with that key.
    for (size_t i = 0; i < n_edges; ++i) {
        typename T::key_t u_key, v_key;
        in >> u_key >> v_key;
        
        E edge_data;
        in >> edge_data;
        /*
        ·Se leen las claves (key_t) de los dos vértices que forman los extremos de la arista (u_key y v_key).
        ·Se lee el dato asociado a la arista (edge_data)
        */
        
        if(in.fail())
            throw std::runtime_error("Wrong graph");
        
        auto u = find_vertex(u_key); //Se buscan los vértices en el grafo usando sus claves.
        auto v = find_vertex(v_key);
        
        if(u == nullptr || v == nullptr){
            throw std::runtime_error("Wrong graph");
        }
        
        add_edge(u, v, edge_data);
    }
    /*
    Resumen:
    Permite reconstruir todas las aristas del grafo a partir de un archivo o entrada de texto, asegurando que cada arista conecta vértices válidos y que el formato es correcto.
    ·Lee los extremos y el dato de cada arista desde la entrada.
    ·Si hay un error o los vértices no existen, lanza una excepción.
    ·Si todo va bien, añade la arista al grafo.
    Así, tras este bucle, el grafo tendrá todas sus aristas correctamente cargadas desde el archivo o entrada de texto.
    */
    //
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::vertices_begin() const
{
    return VertexIterator<T, E>(const_cast<Graph *>(this)->vertices_.begin());
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::vertices_end() const
{
    return VertexIterator<T, E>(const_cast<Graph *>(this)->vertices_.end());
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::find_first(typename T::key_t const &value) const
{
    auto iter = vertices_begin();
    // TODO
    while(iter != vertices_end() && (*iter)->item().key() != value) //Para cada vértice, obtiene el dato almacenado ((*iter)->item()) y su clave (.key()).
        ++iter;
    //
    assert(iter == vertices_end() || (*iter)->item().key() == value);
    return iter;
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::get_iterator(const VertexRef &v) const
{
    assert(has(v));
    auto iter = vertices_begin();
    // TODO
    while(iter != vertices_end() && (*iter) != v)
        ++iter;
    //
    assert((*iter) == v);
    return iter;
}

template <class T, class E>
void Graph<T, E>::remove_vertex(const VertexIterator<T, E> &iter)
{
    assert(has(*iter));
#ifndef NDEBUG
    auto old_num_vertices = num_vertices();
#endif
    // TODO
    // Hint: use remove_vertex(const VertexRef &v) method.
    remove_vertex(*iter);
    //
    assert(!has(*iter));
    assert(num_vertices() == (num_vertices() - 1));
}

template <class T, class E>
EdgeIterator<T, E> Graph<T, E>::edges_begin(const VertexIterator<T, E> &v) const
{
    return EdgeIterator<T, E>(v.it_->second.begin());
}

template <class T, class E>
EdgeIterator<T, E> Graph<T, E>::edges_end(const VertexIterator<T, E> &v) const
{
    return EdgeIterator<T, E>(v.it_->second.end());
}

template <class T, class E>
EdgeIterator<T, E> Graph<T, E>::find_first(VertexIterator<T, E> u_iter, typename T::key_t const &value) const
{
    auto edge_iter = edges_begin(u_iter);
    // TODO
    while(edge_iter != edges_end(u_iter)){ //Recorre todas las aristas incidentes al vértice apuntado por u_iter.
        if((*edge_iter)->other(*u_iter)->item().key() == value) //obtiene el vértice opuesto a u_iter en la arista actual y comprueba si su clave coincide con value.
            break;
        ++edge_iter;
    }
    //
    assert(edge_iter == edges_end(u_iter) || (*edge_iter)->has(*u_iter));
    assert(edge_iter == edges_end(u_iter) || (*edge_iter)->other(*u_iter)->item().key() == value);
    return edge_iter;
}

template <class T, class E>
std::vector<typename Graph<T, E>::VertexRef>
get_vertices(const Graph<T, E> &g)
{
    std::vector<typename Graph<T, E>::VertexRef> vs;
    // TODO
    // Hint: use a VertexIterator to traverse the graph's vertices.
    vs.reserve(g.num_vertices()); //reserva espacio suficiente para almacenar al menos g.num_vertices() elementos.

    for(auto it = g.vertices_begin(); it != g.vertices_end(); ++it)
        vs.push_back(*it);
    //
    return vs;
}

template <class T, class E>
std::vector<typename Graph<T, E>::EdgeRef>
get_edges(const Graph<T, E> &g)
{
    std::vector<typename Graph<T, E>::EdgeRef> es;
    // TODO
    // Hint: use VertexIterator and EdgeIterator iterators to traverse the graph.
    // Remember: if the graph is undirected, the edge (u,v) was duplicated as (v, u) into
    // the incident list of u and v but we only want one copy in the returned vector.
    es.reserve(g.num_edges());
    
    if(g.is_directed())
        for(auto v_it = g.vertices_begin(); v_it != g.vertices_end(); ++v_it)
            for(auto e_it = g.edges_begin(v_it); e_it != g.edges_end(v_it); ++e_it)
                es.push_back(*e_it);
    /*
    ·Recorre todos los vértices y todas sus aristas.
    ·Añade todas las aristas al vector es.
    */
    else
        for(auto v_it = g.vertices_begin(); v_it != g.vertices_end(); ++v_it)
            for(auto e_it = g.edges_begin(v_it); e_it != g.edges_end(v_it); ++e_it)
                if((*v_it)->label() < (*e_it)->other(*v_it)->label())
                    es.push_back(*e_it);
    /*
    ·Recorre todos los vértices y sus aristas.
    ·Evita duplicados: en grafos no dirigidos, cada arista aparece dos veces (una en cada extremo).
     ·Solo añade la arista si el label del vértice actual es menor que el del otro extremo, así solo se añade una vez cada arista.*/
    for(size_t i = 0; i < es.size(); ++i)
        for(size_t j = 0; j < es.size() - i - 1; ++j)
            if(es[j]->first()->label() > es[j+1]->first()->label() || (es[j]->first()->label() == es[j+1]->first()->label() && es[j]->second()->label() > es[j+1]->second()->label())){
                auto aux = es[j];
                es[j] = es[j+1];
                es[j+1] = aux;
            }
    /*
    ·Ordena el vector de aristas primero por el label del primer vértice y, si son iguales, por el label del segundo vértice.
    ·Así, el vector de aristas queda en un orden canónico (útil para guardar o comparar grafos).*/
    /*
    Resumen
    ·Recolecta todas las aristas del grafo en un vector.
    ·Evita duplicados en grafos no dirigidos.
    ·Ordena las aristas por los labels de sus extremos.
    ·Devuelve el vector resultante.
    */
    //
    return es;
}
