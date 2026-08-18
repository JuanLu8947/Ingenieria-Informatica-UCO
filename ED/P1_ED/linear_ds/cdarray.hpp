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
#include <memory>

/**
 * @brief ADT CDArray
 * Models a Circular Dynamic Array.
 * This adt also is known as deque (double ended queue).
 */
template <class T>
class CDArray
{
public:
    /** @name Life cycle.*/
    /** @{*/

    /** @brief Create an empty CDArray.
     * @param cap specify the initial capacity of the cdarray.
     * @pre cap>0
     * @post capacity()==cap
     * @post is_empty()
     */
    CDArray(size_t cap = 1);

    /**
     * @brief Create a CDArray unfolding from an input stream.
     *
     * The input format will be
     * "[" item1 item2 ... item_n "]" where item1 is the front and
     * item_n is the back.
     *
     * @param in is the input stream.
     * @warning if the input format is not correct a std::runtime_error with
     * what message "Wrong input format." will be raised.
     * @return A shared reference to the new cdarray.
     */
    CDArray(std::istream &in) noexcept(false);

    /** @brief Destroy a CDArray.**/
    ~CDArray();

    /** @}*/

    /** @name Observers*/

    /** @{*/

    /**
     * @brief is the cdarray empty?.
     * @return true if it is an empty cdarray.
     */
    bool is_empty() const;

    /**
     * @brief Is the cdarray full?
     * If it's full, a push or insertion will make grow to double capacity.
     * @return true if the cdarray is full.
     * @post !ret_v || size()==capacity()
     */
    bool is_full() const;

    /** @brief Get the current maximum number of items in the cdarray before a growing.*/
    size_t capacity() const;

    /** @brief Get the current number of items in the cdarray.*/
    size_t size() const;

    /**
     * @brief Fold to an output stream.
     *
     * The format will be '[' item1 item2 item3 ... item_n ']'
     * where item1 is the front and item_n is the back.
     *
     * @param out is the output stream.
     * @return the output stream.
     */
    std::ostream &fold(std::ostream &out) const;

    /**
     * @brief Gets an item value given its index.
     * @param pos is the index in the cdarray.
     * @return T
     * @pre 0<=pos<size()
     */
    T const &get(size_t pos) const;

    /**@}*/

    /** @name Modifiers*/

    /** @{*/

    /**
     * @brief Sets an item value given its index.
     * @param idx is the index in the cdarray.
     * @param new_v is the new value.
     * @return T
     * @pre 0<=pos<size()
     * @post new_v == get(pos);
     */
    void set(size_t pos, T const &new_v);

    /**
     * @brief insert a new item as the new cdarray's front.
     * @param new_it is the item to insert.
     * @post front()==new_it
     * @post size()==(old.size()+1)
     */
    void push_front(T const &new_it);

    /**
     * @brief insert a new item as the new cdarray's back.
     * @param new_it is the item to insert.
     * @post front()==new_it
     * @post size()==(old.size()+1)
     */
    void push_back(T const &new_it);

    /**
     * @brief Remove the current front.
     * @pre !is_empty()
     * @post is_empty() || front() == old.get(1)".
     * @post size()==(old.size()-1)
     */
    void pop_front();

    /**
     * @brief Remove the current back.
     * @pre !is_empty()
     * @post is_empty() || back() == old.get(old.size()-2)
     * @post size()==(old.size()-1)
     */
    void pop_back();

    /**
     * @brief insert a new item before the position.
     * @param pos position in the cdarray where inserting.
     * @param v is the item to insert.
     * @post 0<=pos<size()
     * @post get(pos)==v
     * @post get(pos+1) = old.get(pos)
     * @post size()==(old.size()+1)
     */
    void insert(size_t pos, T const &v);

    /**
     * @brief Remove the item at a given position.
     * @pre 0<=pos<size()
     * @post pos==size() || get(pos) = old.get(pos+1)
     * @post size()==(old.size()-1)
     */
    void remove(size_t pos);

    /** @}*/

protected:
    /**
     * @brief Grow the data to double size.
     * @post capacity()==(old.capacity()*2)
     * @post get(0)==old.get(0)
     * @post get(size()-1)==old.get(size()-1)
     */
    void grow();

    // TODO
    // Give a representation.
    // Hint: use std::shared_ptr<T[]> to manage the block of allocated memory.
    std::shared_ptr<T[]> data_; //reserva de un bloque de memoria, uso de los punteros inteligentes, el puntero como tal hace referencia, no reserva memorias
    size_t capacity_;
    size_t size_;
    size_t front_;
    size_t back_;
    //
};

#include <cdarray_imp.hpp>