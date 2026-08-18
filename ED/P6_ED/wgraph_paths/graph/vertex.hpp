/**
 * @file vertex.hpp
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
/**
 * @brief Class to model the Vertex of a Graph ADT.
 *
 * @tparam T is the vertex's data item type.
 *
 * It is assumed that T type defines a type T::key_t and
 * a method 'T::key_t T::key() const'
 *
 * @ingroup graph
 */
template <class T>
class Vertex
{
public:
    /** @brief alias for a reference to a Vertex.*/
    using Ref = std::shared_ptr<Vertex<T>>;

    /** @name Makers*/
    /** @{*/

    /**
     * @brief Makes a new vertex.
     * @param label is the vertex label.
     * @param item is the vertex data item.
     * @post !is_visited()
     */
    Vertex(size_t label, T const &item);

    /**
     * @brief Makes a new vertex.
     * @param label is the vertex label.
     * @param item is the vertex data item.
     * @post !is_visited()
     */
    static Ref create(size_t label, T const &item);

    ~Vertex() {}
    /** @}*/

    /** @name Observers*/
    /**@{*/

    /**
     * @brief Get saved data item.
     * @return the saved data item.
     */
    const T &item() const;

    /**
     * @brief get the label of the vertex.
     * @return the vertex's label.
     * @post no other vertex in the graph has this label.
     */
    size_t label() const;

    /**
     * @brief Has been the vertex visited?
     * @return true if the vertex was visited.
     */
    bool is_visited() const;

    /**@}*/

    /** @name Modifiers*/
    /** @{*/

    /**@brief Set data saved in the vertex.
     * @param[in] item is the data to save in.
     * @post item()==item
     */
    void set_item(T const &new_item);

    /**
     *  @brief Set the flag visited
     *  @param new_state is the state to set.
     *  @post new_state || !is_visited()
     *  @post !new_state || is_visited()
     */
    void set_visited(bool new_state);
    /** @} */

protected:
    size_t label_;    /**< the vertex label (unique in the graph)*/
    T item_;          /**< the data item associated to the vertex.*/
    bool is_visited_; /**< the visited flag.*/
};

#include <vertex_imp.hpp>
