/**
 * @author Francisco José Madrid-Cuevas (fjmadrid@uco.es)
 * @brief Implements the ADT PriorityQueue.
 *
 * @copyright Copyright (c) 2025-
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 *
 */
#pragma once

#include <functional>
#include <heap.hpp>

/**
 * @brief Models a priority queue using a heap.
 *
 * @tparam T is the value type of the data items.
 * @tparam Comp is the comparison function object. Return true if a is before in order to b.
 */
template <class T>
class PriorityQueue
{
public:
    /** @name Life cicle.*/
    /** @{*/

    /**
     * @brief Type of the comparison function object.

     * For instance, std::greater_equal<T>() could be used if the queue give predominance to the
     * greatest values of priority and there could be repeated values.

     * @tparam T is the value type of the data items.
     * @param a is the first value to be compared.
     * @param b is the second value to be compared.
     * @return true if \a a is before in order to \a b.
     */
    using Comp = typename Heap<T>::Comp;

    /**
     * @brief Creates a priority queue.
     *
     * @param values is a vector used as buffer to store the items in the queue.
     * @param comp comparison functor used to order the items in the queue.
     * @post is_empty()
     *
     */
    PriorityQueue(std::vector<T> &values, Comp const &comp = std::greater_equal<T>());

    /**
     * @brief Destroy the Priority Queue object
     *
     */
    ~PriorityQueue();
    /** @} */

    /** @name Observers. */
    /** @{ */
    /**
     * @brief Is the queue empty?
     * @return true if the queue is empty.
     */
    bool is_empty() const;

    /**
     * @brief Size of the queue.
     *
     * @return the number of items in the queue.
     * @post !is_empty() || size() == 0.
     */
    size_t size() const;

    /**
     * @brief get the first item in the queue.
     *
     * @return the first item in the queue.
     */
    const T &front() const;

    /** @} */

    /** @name Modifiers. */
    /** @} */
    /**
     * @brief Insert a new item in the queue.
     *
     * @param new_item the new item to be inserted.
     * @post size()== old.size()+1
     */
    void enqueue(const T &new_item);
    /**
     * @brief Remove the first item in the queue.
     * @post size()== old.size()-1
     */
    void dequeue();
    /** @} */

protected:
    Heap<T> heap_; /*< The heap used to store the items in the queue. */
};

#include <priority_queue_imp.hpp>
