#pragma once
#include <priority_queue.hpp>

template <class T>
bool PriorityQueue<T>::is_empty() const
{
    // TODO: fixme
    return heap_.is_empty();
    //
}

template <class T>
size_t PriorityQueue<T>::size() const
{
    size_t ret_v = 0;
    // TODO
    ret_v = heap_.size();
    //
    assert(!heap_.is_empty() || ret_v == 0);
    return ret_v;
}

template <class T>
PriorityQueue<T>::PriorityQueue(std::vector<T> &values, Comp const &comp)
    : heap_(values, comp)
{
    assert(is_empty());
}

template <class T>
PriorityQueue<T>::~PriorityQueue() {}

template <class T>
const T &PriorityQueue<T>::front() const
{
    // TODO: fixme
    //return T{};
    return heap_.item(); //Devolvemos el primer elemento del heap
    //
}

template <class T>
void PriorityQueue<T>::enqueue(const T &new_v)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    heap_.insert(new_v); //Insertamos el nuevo elemento en el heap
    //
    assert(size() == old_size + 1);
}

template <class T>
void PriorityQueue<T>::dequeue()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    heap_.remove(); //Eliminamos el primer elemento del heap
    //
    assert(size() == old_size - 1);
}
