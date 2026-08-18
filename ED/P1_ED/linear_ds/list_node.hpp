/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <memory>

/** @brief a Double linked node.*/
template <class T>
class DNode
{
public:
    /** @brief Define a shared reference to a DNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    using Ref = std::shared_ptr<DNode<T>>;

    /** @name Life cycle.*/
    /** @{*/

    /**
     * @brief Create a dummy node using dynamic memory.
     * @return a shared reference to the dummy node.
     * @post ret_v->is_dummy()
     */
    static typename DNode<T>::Ref create();

    /**
     * @brief Create a DNode using dynamic memory.
     * @param it the value save in the node.
     * @return a shared reference to the new node.
     */
    static typename DNode<T>::Ref create(T const &it);

    /**
     * @brief Create a DNode using dynamic memory.
     * @param it the value save in the node.
     * @param next_n the link to the next node.
     * @return a shared reference to the new node.
     * @post !ret_v->is_dummy()
     * @post ret_v->item()==it
     * @post ret_v->next()==next_n
     * @post ret_v == ret_v->This()
     */
    static typename DNode<T>::Ref create(T const &it, Ref const &next_n);

    /**
     * @brief Create a DNode using dynamic memory.
     * @param it the value save in the node.
     * @param next_n the link to the next node.
     * @param prev_n the link to the prev node.
     * @return a shared reference to the new node.
     * @post !ret_v->is_dummy()
     * @post ret_v->item()==it
     * @post ret_v->next()==next_n
     * @post ret_v->prev()==prev_n
     * @post ret_v == ret_v->This()
     */
    static typename DNode<T>::Ref create(T const &it, Ref const &next_n, Ref const &prev_n);

    /** @brief Destroy a DNode.**/
    ~DNode();

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /**
     * @brief Is it a dummy node?
     * A dummy node is a node which does not contain any data. Usually it is
     * used to mark the end of a list.
     * @return true when it is.
     */
    bool is_dummy() const;

    /** @brief Get the data item.*/
    T const &item() const;

    /**
     * @brief Get the link to next element.
     */
    typename DNode<T>::Ref prev() const;

    /** @brief Get the link to next element.*/
    typename DNode<T>::Ref next() const;

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T &new_it);

    /** @brief Set the link to the next node.*/
    void set_prev(DNode<T>::Ref prev);

    /** @brief Set the link to the next node.*/
    void set_next(DNode<T>::Ref next);

    /** @brief Get a self reference to this. */
    Ref This();

    /** @}*/

protected:
    Ref This_; /**Hold a self reference to this.*/

    // We want to use the constructor only from the static methods.

    /** @brief Create a dummy node.
     *  A dummy node has not item data used to mark the "end" of the sequence.   *
     *  @post is_dummy()
     *  @post next()==prev()==This()
     */
    DNode();

    /** @brief Create a node.
     *  @post it == item()
     *  @post next()==nullptr
     *  @post prev()==nullptr
     *  @post !is_dummy()
     */
    DNode(T const &it);

    /** @brief Create a node.
     *  @post it == item()
     *  @post next()==next_n
     *  @post prev()==nullptr
     *  @post !is_dummy()
     */
    DNode(T const &it, Ref next_n);

    /** @brief Create a node.
     *  @post it == item()
     *  @post next()==next_n
     *  @post prev()==prev_n
     *  @post !is_dummy()
     */
    DNode(T const &it, Ref next_n, Ref prev_n);

    // TODO: Give a representation.
    // Remember: for a simple list we only need a item and the next node link.
    // However for a double linked list we need a link to the previous node.
    // Hint: for a double linked list, we will need a node with no data,
    // also known as a "dummy node", so a smart pointer can be useful here.
    std::shared_ptr<T> _item;
    Ref _prev;
    Ref _next;
    /*
    Ref _prev y Ref _next son miembros de la clase DNode que representan punteros compartidos (std::shared_ptr) a otros nodos en una lista doblemente enlazada. Aquí está el desglose:
    ·Ref _prev: Es un puntero compartido al nodo anterior en la lista.
    ·Ref _next: Es un puntero compartido al nodo siguiente en la lista.
    Estos punteros permiten que cada nodo en la lista tenga referencias tanto al nodo anterior como al siguiente, lo que facilita la navegación en ambas direcciones a través de la lista.
    */
    //
};

#include <list_node_imp.hpp>
