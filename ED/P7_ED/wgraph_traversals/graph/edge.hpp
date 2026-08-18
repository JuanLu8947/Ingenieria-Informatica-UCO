/**
 * @file edge.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <memory>
#include <vertex.hpp>

/**
 * @brief Class to model the Edge of a Graph ADT.
 * An edge refers both a directed link u->v or an undirected link (u,v)
 *
 * @tparam T is the vertex's data type item.
 * @tparam E is the edge's data type item.
 *
 * @ingroup Graph
 */
template <class T, class E>
class Edge
{
public:
    /** @brief alias for a reference to a vertex.*/
    using VertexRef = typename Vertex<T>::Ref;

    /** @brief alias for a reference to an Edge.*/
    using Ref = std::shared_ptr<Edge<T, E>>;

    /** @name Lifecycle Makers*/
    /** @{*/

    /**
     * @brief Makes an edge.
     * @param[in] u,
     * @param[in] v are the edge's end (first, second if directed)
     * @param[in] item is the edge's data item.
     * @post first()==u
     * @post second()==v
     * @post has(u)
     * @post has(v)
     * @post other(u)==v
     * @post other(v)==u
     * @post item()==item
     * @post ! is_visited()
     */
    Edge(VertexRef const &u, VertexRef const &v, E const &item);

    /**
     * @brief Makes an edge.
     * @param[in] u,
     * @param[in] v are the edge's end (first, second if directed)
     * @param[in] item is the edge's data item.
     * @post first()==u
     * @post second()==v
     * @post has(u)
     * @post has(v)
     * @post other(u)==v
     * @post other(v)==u
     * @post item()==item
     * @post ! is_visited()
     */
    static Ref create(VertexRef const &u, VertexRef const &v, E const &item);

    /**
     * @brief Destroy the Edge object
     */
    ~Edge();

    /** @}*/

    /** @name Observers*/
    /** @{*/

    /**
     *  @brief Get edge's data item.
     */
    E const &item() const;

    /**
     * @brief Is the vertex visited?
     * @return true if the vertex is visited.
     */
    bool is_visited() const;

    /**
     *  @brief Is vertex u an end of this edge.
     * @param[in] u is the vertex to test.
     * @return true is @a u is one of the edge's ends.
     */
    bool has(VertexRef const &u) const;

    /**
     * @brief The other vertex end that is not u.
     * @param[in] u is one of the vertex ends.
     * @return the other vertex end that is not @a u.
     * @pre has(u)
     * @post has(retVal) and other(retVal)==u
     */
    const VertexRef &other(VertexRef const &u) const;

    /**
     * @brief The other vertex end that is not u.
     * @param[in] u is one of the vertex ends.
     * @return the other vertex end that is not @a u.
     * @pre has(u)
     * @post has(retVal) and other(retVal)==u
     */
    VertexRef &other(VertexRef const &u);

    /**
     * @brief the first vertex of the directed edge (u, v)
     * @return @a u.
     */
    const VertexRef &first() const;
    /**
     * @brief the first vertex of the directed edge (u, v)
     * @return @a u.
     */
    VertexRef &first();

    /** @brief the second vertex of the directed edge (u, v).
     * @return @a v.
     */
    const VertexRef &second() const;

    /** @brief the second vertex of the directed edge (u, v).
     * @return @a v.
     */
    VertexRef &second();

    /**@}*/

    /** @name Modifiers*/
    /** @{*/

    /**
     * @brief Set data saved in the vertex.
     * @param[in] v is the data to save in.
     * @post item()==v
     */
    void set_item(E const &v);

    /**
     *  @brief Set the flag visited
     *  @param new_state is the state to set.
     *  @post new_state || !is_visited()
     *  @post !new_state || is_visited()
     */
    void set_visited(bool new_state);

    /** @} */

protected:
    VertexRef u_;     /**< the first end.*/
    VertexRef v_;     /**< the second end.*/
    E item_;          /**< the data item associated to this edge.*/
    bool is_visited_; /**< the visited flag.*/
};

#include <edge_imp.hpp>
