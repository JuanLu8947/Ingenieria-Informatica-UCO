/**
 * @file graph.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <list>
#include <vertex.hpp>
#include <edge.hpp>
#include <graph_iterators.hpp>

/**
 * @brief Models a Graph ADT.
 *
 * @tparam T is the vertex's data type item.
 * @tparam E is the edge's data type item.
 */
template <class T, class E>
class Graph
{
public:
  /** @brief alias type for a reference to a graph's vertex. */
  using VertexRef = typename Vertex<T>::Ref;

  /** @brief alias type for a reference to a graph's edge. */
  using EdgeRef = typename Edge<T, E>::Ref;

  /** @name Makers*/
  /** @{*/

  /**
   * @brief Makes a Graph.
   * @post is_empty()
   * @post !is_directed || is_directed()
   * @post is_directed || !is_directed()
   */
  Graph(bool is_directed);

  /**
   * @brief Makes a graph from an input stream.
   *
   * The input format follow the following scheme:
   *
   * 'DIRECTED'|'UNDIRECTED'
   * <NUM. NODES>
   * <NODE_0_ITEM>
   * ...
   * <NODE_N-1_ITEM>
   * <NUM_EDGES>
   * <U_KEY_0> <V_KEY_0> <EDGE_ITEM_0>
   * ...
   * <U_KEY_num_edges-1> <V_KEY_num_edges-1> <EDGE_ITEM_num_edges-1>
   *
   * @param in is the input stream.
   * @throw std::runtime_error("Wrong graph") if the input format is wrong.
   */
  Graph(std::istream &input) noexcept(false);

  /**
   * @brief Destroy the Graph object
   *
   */
  ~Graph() {}

  /** @}*/

  /** @name Observers*/
  /**@{*/

  /**
   * @brief is the graph empty?
   * @return true if there is not any vertex.
   * @pos !is_empty() or size()==0
   */
  bool is_empty() const;

  /**
   * @brief Is a directed graph?
   *
   * @return true if is a directed graph.
   */
  bool is_directed() const;

  /**
   * @brief Get current number of vertices.
   */
  size_t num_vertices() const;

  /**
   * @brief Get current number of edges.
   */
  size_t num_edges() const;

  /** @brief is u a vertex of this graph?
   * @pre u is not nullptr.
   * @return if its true.
   */
  bool has(VertexRef const &u) const;

  /**
   * @brief is u a vertex of this graph?
   * @param[in] e is the edge to be checked.
   * @return true if \a e is an edge of this graph.
   * @pre has(e->first()) && has(e->second())
   */
  bool has(EdgeRef const &e) const;

  /**
   * @brief Is vertex u adjacent to vertex v?
   * A vertex u is adjacent to v if there is a directed edge (u,v) or
   * if the graph is undirected, there is an edge (u,v) or (v,u).
   * @param[in] u ,
   * @param[in] v are vertices.
   * @return true if there is an edge (u,v) or if it's undirected an edge (v,u).
   * @pre u and v are vertices of the graph.
   */
  bool is_adjacent(VertexRef const &u, VertexRef const &v) const;

  /**
   * @brief Find a vertex given an item key value.
   * @param value is the data item to be found.
   * @return a reference to the first vertex with that item key value.
   * @post !ret_v || ret_v->item().key() == value
   */
  VertexRef find_vertex(typename T::key_t const &value) const;

  /**
   * @brief Find a vertex given a label.
   *
   * @param label is the label of the vertex to be found.
   * @return a reference to the vertex with that label.
   * @post !ret_v || ret_v->label() == label
   */
  VertexRef vertex(size_t label) const;

  /**
   * @brief Get the edge (u,v).
   * @param u,
   * @param v are the ends of the edge (first, second if the graph is directed).
   * @return a reference to the edge or nullptr if it doesn't exist.
   * @pre has(u)
   * @pre has(v)
   * @post !ret_v || (!is_directed() || ret_v->first()==u)
   * @post !ret_v || (!is_directed() || ret_v->second()==v)
   * @post !ret_v || (is_directed() || ret_v->has(u))
   * @post !ret_v || (is_directed() || ret_v->other(u)==v)
   */
  EdgeRef edge(VertexRef const &u, VertexRef const &v) const;

  /**
   * @brief Fold a weighted graph to an output stream.
   * When folding, the graph is always "DIRECTED".
   * @see constructor to get the grammar.
   * @param out is the output stream.
   * @return the output stream.
   */
  std::ostream &fold(std::ostream &out) const;

  /**
   * @brief Get an iterator to the first vertex.
   * @return an iterator to the first vertex.
   */
  VertexIterator<T, E> vertices_begin() const;

  /**
   * @brief Get an iterator to the end of the vertex list.
   * @return an iterator to the end of the vertex list.
   */
  VertexIterator<T, E> vertices_end() const;

  /**
   * @brief Find the first occurrence of a vertex with the given key value.
   *
   * @param value is the key value to compare with.
   * @return an iterator to the first vertex with that key value.
   */
  VertexIterator<T, E> find_first(typename T::key_t const &value) const;

  /**
   * @brief Get an iterator points to a vertex.
   *
   * @param v is the vertex to be pointed.
   * @return the iterator.
   * @pre has(v)
   * @post (*ret_v) == v
   */
  VertexIterator<T, E> get_iterator(const VertexRef &v) const;

  /**
   * @brief Get an iterator to the first edge incident to the given vertex
   *
   * @param v is an iterator to a vertex.
   * @return an iterator to first edge incident to the vertex.
   * @pre v is a valid iterator.
   */
  EdgeIterator<T, E> edges_begin(const VertexIterator<T, E> &v) const;

  /**
   * @brief Get an interator to the end of the edge list incident to the given vertex
   *
   * @param v is an iterator to a vertex.
   * @return an iterator to the end of the edge list incident to the vertex.
   * @pre v is a valid iterator.
   */
  EdgeIterator<T, E> edges_end(const VertexIterator<T, E> &v) const;

  /**
   * @brief Find the first edge (u,v) occurrence given the ends.
   * @param u_iter is a vertex iterator to u
   * @param value is the key value to compare with to find the other end (v).
   * @return an iterator to the first edge found or edges_end(u_iter) if not found.
   * @post ret_v==edges_end(u_iter) || (*ret_v)->has(*u_iter)
   * @post ret_v==edges_end(u_iter) || (*ret_v)->other(*u_iter)->item().key() == value
   */
  EdgeIterator<T, E> find_first(VertexIterator<T, E> u_iter, typename T::key_t const &value) const;

  /** @}*/

  /** @name Modifiers*/
  /** @{*/

  /**
   * @brief set the visited state for all the vertices and edges.
   */
  void reset(bool state);

  /**
   * @brief Add a new vertex.
   * @param[in] v is the data item to be save in the new vertex.
   * @post has(ret_v)
   * @post ret_v->item()==v
   * @post !ret_v->is_visited()
   */
  VertexRef add_vertex(T const &v);

  /**
   * @brief Remove a vertex.
   *
   * All the edges incident on current vertex will be removed also.
   *
   * @param v is the vertex to be removed.
   *
   * @pre has(v)
   * @post !has(v)
   * @post num_vertices()==(old.num_vertices()-1)
   */
  void remove_vertex(const VertexRef &v);

  /**
   * @brief Remove a vertex.
   *
   * All the edges incident on current vertex will be removed also.
   *
   * @param v is the vertex to be removed.
   *
   * @pre has(*iter)
   * @post !has(*iter)
   * @post num_vertices()==(old.num_vertices()-1)
   */
  void remove_vertex(const VertexIterator<T, E> &iter);

  /**
   * @brief Add a new edge.
   *
   * If the graph is directed, the edge will be the directed edge u->v and it means that u is adjacent to v.
   * If the graph is not directed, the edge (u,v) means both u is adjacent to v and v is adjacent to u.
   *
   * @param[in] u is the first end.
   * @param[in] v is the second end.
   * @param[in] weight is the edge's weight.
   * @return a reference to the added edge.
   * @pre !is_adjacent(u, v)
   * @post !is_directed() || is_adjacent( @a u, @a v)
   * @post is_directed() || (is_adjacent( @a u, @a v) && is_adjacent( @a v, @a u))
   * @post current_vertex() == u
   * @post current_edge()->second() == v
   * @post current_edge()->item() == item
   */
  EdgeRef add_edge(VertexRef const &u, VertexRef const &v, E const &item);

  /**
   * @brief Remove an edge.
   * @param u,
   * @param v are the ends of the edge to be removed.
   * @pre has(u)
   * @pre has(v)
   * @post !is_adjacent(u, v)
   * @post num_edges()==(old.num_edges()-1)
   */
  void remove_edge(VertexRef const &u, VertexRef const &v);

  /** @} */

  /** @} */

protected:
  friend class VertexIterator<T, E>;
  friend class EdgeIterator<T, E>;

  size_t next_label_;                                                    /**< you need a next label attribute to give unique labels to the new vertices.*/
  bool is_directed_;                                                     /**< is it a directed graph?*/
  using edges_list_t = std::list<EdgeRef>;                               /**< alias to define list of edges.*/
  using vertices_list_t = std::list<std::pair<VertexRef, edges_list_t>>; /**< alias to define pair of vertex and its incident edge list.*/
  vertices_list_t vertices_;                                             /**< the list of vertex and their incident edge lists.*/
};

/**
 * @brief Get the graph's vertices.
 *
 * @return a vector with the graph's vertices.
 */
template <class T, class E>
std::vector<typename Graph<T, E>::VertexRef> get_vertices(const Graph<T, E> &g);

/**
 * @brief Get the graph's edges.
 *
 * @return a vector with the graph's edges.
 */
template <class T, class E>
std::vector<typename Graph<T, E>::EdgeRef> get_edges(const Graph<T, E> &g);

#include <graph_imp.hpp>
