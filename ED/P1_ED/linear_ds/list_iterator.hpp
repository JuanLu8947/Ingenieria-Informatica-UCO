/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <list_node.hpp>

/**Forward declaration.*/
template <class T>
class List;

/**
 * @brief Models an iterator to edit a list.
 *
 * @tparam T the type of the items in the list.
 */
template <class T>
class ListIterator
{
public:
    /**
     * @brief Destroy the List Iterator object.
     *
     */
    ~ListIterator();

    typedef ListIterator<T> iterator;

    /** @name Observers.*/
    /** @{*/

    /**
     * @brief Is the iterator pointing to a valid list node?
     * A valid list node is a node other than the dummy node.
     */
    bool is_valid() const;

    /**
     * @brief Get item in the iterator position.
     *
     * @return item in the iterator position.
     * @pre is_valid()
     */
    T const &item() const;

    /**
     * @brief Get an iterator in a next position.
     *
     * @param dist number of next positions.
     * @return an iterator in a next position.
     */
    iterator next(size_t dist = 1) const;

    /**
     * @brief Get an iterator in a prev position.
     *
     * @param dist number of prev positions.
     * @return an iterator in a prev position.
     */
    iterator prev(size_t dist = 1) const;

    /**
     * @brief Distance between iterators.
     * Size of the range [this, other)
     * @param other the end of the range
     * @return distance between iterators.
     * @pre this iterator is an before position than other.
     */
    size_t distance(const iterator &other) const;

    /**
     * @brief Is ot iterator in the same position than this?
     */
    bool operator==(iterator const &ot) const;

    /**
     * @brief Is ot iterator in a different position than this?
     */
    bool operator!=(iterator const &ot) const;

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/
    /**
     * @brief Set the item object
     *
     * @param item the value to be set.
     */
    void set_item(const T &item);

    /**
     * @brief move iterator to a next position.
     *
     * @param dist number of next positions.
     */
    void goto_next(size_t dist = 1);

    /**
     * @brief move iterator to a prev position.
     *
     * @param dist number of prev positions.
     */
    void goto_prev(size_t dist = 1);
    /** @}*/

protected:
    friend class List<T>; /**Only a list can create iterators.*/

    /** @name Life cycle.*/
    /** @{*/

    /**
     * @brief Construct a new List Iterator object.
     * The iterator is invalid (points to nothing)
     * @post !is_valid()
     */
    ListIterator();

    /**
     * @brief Construct a new List Iterator points to a list node.
     *
     * @param node the node pointed by this iterator.
     */
    ListIterator(typename DNode<T>::Ref const &node);

    /** @}*/

    /**
     * @brief Get the node pointed by this iterator.
     *
     * @return the node pointed by this iterator.
     */
    typename DNode<T>::Ref node() const;

    /**
     * @brief Change the node pointed by this iterator.
     *
     * @param n the node pointed by this iterator.
     */
    void set_node(typename DNode<T>::Ref const &n);

    // TODO: give a representation.
    // Remember: a list iterator points to a list's node.
    typename DNode<T>::Ref node_;
    /*
    es un miembro de la clase ListIterator que representa un puntero compartido (std::shared_ptr) a un nodo en una lista doblemente enlazada. Aquí está el desglose:
    ·typename DNode<T>::Ref: Define un tipo de referencia compartida a un nodo de tipo DNode<T>. Ref es un alias para std::shared_ptr<DNode<T>>.
    ·node_: Es el nombre del miembro de la clase ListIterator que almacena el puntero compartido al nodo actual al que apunta el iterador.
    El propósito de node_ es mantener una referencia al nodo actual en la lista que está siendo iterada. Esto permite que el iterador acceda y modifique el nodo actual y se mueva a nodos adyacentes.
    */
    //
};
#include <list_iterator_imp.hpp>