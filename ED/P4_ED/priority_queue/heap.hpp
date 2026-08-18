/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <iostream>
#include <vector>
#include <functional>

/**
 * @brief Implement the Heap ADT.
 * The parameter template Comp must implement the interface
 * bool operator()(T const& a, T const& b)
 * to compare two values a, b.
 * For instance, std::less_equal<T> could be used.
 * @invariant is_a_heap()
 */
template <class T>
class Heap
{
public:
    /**
     * @brief Type of the comparison function object.
     * For instance, std::less_equal<T>() could be used.
     * @tparam T is the value type of the data items.
     * @param a is the first value to be compared.
     * @param b is the second value to be compared.
     * @return true if \a a is before in order to \a b.
     */
    using Comp = std::function<bool(T const &a, T const &b)>;

    /** @name Life cicle.*/
    /** @{*/

    /**
     * @brief Create an Heap using a given array of values.
     * @post is_a_heap()
     * @post size() == values.size()
     */
    Heap(std::vector<T> &values, Comp const &comp);

    /** @brief Destroy a Heap.**/
    ~Heap();

    /** @}*/

    /** @name Observers*/

    /** @{*/

    /** @brief is the heap empty?.*/
    bool is_empty() const;

    /** @brief Get the heap size. */
    size_t size() const;

    /**
     * @brief Get the root item.
     * @pre not is_empty();
     * @return the root item.
     */
    T const &item() const;

    /** @}*/

    /** @name Modifiers*/

    /** @{*/

    /**
     * @brief insert a new item.
     * @param new_it is the new item to be inserted.
     */
    void insert(T const &new_it);

    /**
     * @brief Remove the root item.
     * @pre not is_empty()
     */
    void remove();

    /** @}*/

protected:
    /**
     * @brief Shift up a value in the heap.
     *
     * @param i is the index of the value to be shifted up.
     */
    void shift_up(size_t i);

    /**
     * @brief Shift down a value in the heap.
     *
     * @param i is the index of the value to be shifted down.
     */
    void shift_down(size_t i);

    /**
     * @brief Make the vector of values a heap.
     * @post is_a_heap()
     */
    void heapify();

    /**
     * @brief Check the head invariant for the subtree.
     * @param root is array's index which is the root of the subtree.
     * @pre 0<=root && root < size()
     */
    bool is_a_heap(size_t root = 0) const;

    std::vector<T> *values_; /*< A reference to the array of values.*/
    size_t last_item_;       /*< The index of the next leaf to be used regarding a complete binary tree.*/
    Comp comp_;              /*< The comparison functor to use.*/
};

/**
 * @brief Sort an array of values using heapsort algorithm.
 *
 * @tparam T is the value type of the data items.
 * @param values are the values to be sorted.
 * @param comp is the comparison function object. Return true if a is before in order to b.
 */
template <class T>
void heapsort(std::vector<T> &values, std::function<bool(T const &a, T const &b)> const &comp);

#include <heap_imp.hpp>