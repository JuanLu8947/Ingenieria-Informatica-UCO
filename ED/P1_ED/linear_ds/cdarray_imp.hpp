/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <sstream>
#include <cassert>
#include <cdarray.hpp>

template <class T>
size_t
CDArray<T>::capacity() const
{
    // TODO: recode with respect to your representation.
    return capacity_; //O(1)
    //return data_.size();
    //return data_.get().size();
    //
}

template <class T>
size_t
CDArray<T>::size() const
{
    // TODO: recode with respect to your representation.
    return size_;
    //
}

template <class T>
bool CDArray<T>::is_empty() const
{
    // TODO: recode with respect to your representation.
    return size() == 0;
    //
}

template <class T>
bool CDArray<T>::is_full() const
{
    bool ret_v = false;
    // TODO
    ret_v = (size() == capacity());
    //
    assert(!ret_v || size() == capacity());
    return ret_v;
}

template <class T>
CDArray<T>::CDArray(size_t cap)
{
    assert(cap > 0);
    // TODO
    //data_ = std::shared_ptr<T[]>(new T[cap], std::default_delete<T[]>()); //libera un bloque de memoria
    data_ = std::shared_ptr<T[]>(new T[cap]);
    capacity_ = cap;
    size_ = 0;
    //
    assert(capacity() == cap);
    assert(is_empty());
    assert(size() == 0);
}

template <class T>
CDArray<T>::~CDArray()
{
    // TODO
    // Remember: depending on your representation, it is possible that nothing
    // must be done.

    //
}

template <class T>
CDArray<T>::CDArray(std::istream &in) noexcept(false) : CDArray(1)
{
    std::string token;
    in >> token;

    // TODO
    // Hint: use std::istringstream to convert from "string" to template
    //  parameter T type.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.
    if (token == "["){
        //mientras pueda leer, y token no sea "]"
        while(in >> token && token != "]"){
            std::istringstream iss(token); //convertir string -> T
            T value; //creamos un value tipo T
            iss >> value; //volcamos el valor de iss en value
            push_back(value); //insertado en el vector
        }
    }
    else{
        throw std::runtime_error("Wrong input format.");
    }
    //
}

template <class T>
std::ostream &
CDArray<T>::fold(std::ostream &out) const
{
    // TODO
    if (is_empty()){
        out << "[ ]";
    }
    else{
        out << "[ ";
        for (size_t i = 0; i < size(); i++){
            out << get(i) << " ";
        }
        out << "]";
    }
    //
    return out;
}

template <class T>
T const &CDArray<T>::get(size_t pos) const
{
    // TODO: recode with respect to your representation.
    return data_[(front_ + pos) % capacity()];
    //
}

template <class T>
void CDArray<T>::set(size_t pos, T const &new_v)
{
    // TODO
    data_[(front_ + pos) % capacity()] = new_v;
    //
    assert(new_v == get(pos));
}

size_t cInc(size_t v, size_t size)
{
    size_t ret_v;
    // TODO
    ret_v = (v + 1) % size;
    //
    return ret_v;
}

size_t cDec(size_t v, size_t size)
{
#ifndef NDEBUG
    size_t old_v = v;
#endif
    size_t ret_v;
    // TODO
    // Remember: v is a unsigned value, so you must cast to signed before decrementing
    ret_v = ((v - 1) + size) % size;
    //
    assert(old_v == cInc(ret_v, size));
    return ret_v;
}

template <class T>
void CDArray<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_front = is_empty() ? T() : get(0);
#endif
    // TODO
    if(is_empty()){
        front_ = 0;
        back_ = 0;
    }
    else{
        if(is_full()){
            grow();
        }
        front_ = cDec(front_, capacity());
    }
    //set(front_, new_it);
    //data_[front_], new_it;
    data_[front_] = new_it;
    size_++;
    //
    assert(size() == old_size + 1);
    assert(get(0) == new_it);
    assert(old_is_empty || (get(1) == old_front));
}

template <class T>
void CDArray<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_back = is_empty() ? T() : get(size() - 1);
#endif
    // TODO
    if(is_empty()){
        front_ = 0;
        back_ = 0;
    }
    else{
        if(is_full()){
            grow();
        }
        back_ = cInc(back_, capacity());
    }
    //set(back_, new_it);
    //data_[back_], new_it;
    data_[back_] = new_it;
    size_++;
    //
    assert(size() == old_size + 1);
    assert(get(size() - 1) == new_it);
    assert(old_is_empty || (get(size() - 2) == old_back));
}

template <class T>
void CDArray<T>::pop_front()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_front = size() > 1 ? get(1) : T();
#endif
    // TODO
    front_ = cInc(front_, capacity());
    size_--;
    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(0) == old_next_front);
}

template <class T>
void CDArray<T>::pop_back()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_prev_back = size() > 1 ? get(size() - 2) : T();
#endif
    // TODO
    back_ = cDec(back_, capacity());
    size_--;
    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(size() - 1) == old_prev_back);
}

template <class T>
void CDArray<T>::insert(size_t pos, T const &v)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_back = get(size() - 1);
    T old_pos_v = get(pos);
#endif
    // TODO
    // Hint: if pos==0, delegate in push_front.
    // Remember: back_ needs to be updated too.
    if(pos == 0){
        push_front(v);
    }
    else{
        if(is_full()){
            grow();
        }
        size_++;
        for(size_t i = (size() - 2); i >= pos; i--){
            set(i + 1, get(i));
        }
        set(pos, v);
        back_ = cInc(back_, capacity());
    }
    //
    assert(size() == old_size + 1);
    assert(get(pos) == v);
    assert(get(pos + 1) == old_pos_v);
    assert(get(size() - 1) == old_back);
}

template <class T>
void CDArray<T>::remove(size_t pos)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_pos_v = (pos <= (size() - 2)) ? get(pos + 1) : T();
#endif
    // TODO
    // Remember: back_ needs to be updated.
    for(size_t i = pos; i < (size() - 1); i++){
        set(i, get(i + 1));
    }
    back_ = cDec(back_, capacity());
    size_--;
    //
    assert(size() == old_size - 1);
    assert(pos == size() || get(pos) == old_next_pos_v);
}

template <class T>
void CDArray<T>::grow()
{
#ifndef NDEBUG
    size_t old_capacity = capacity();
    T old_front = get(0);
    T old_back = get(size() - 1);
#endif
    // TODO
    auto tmp = std::shared_ptr<T[]>(new T[2 * capacity_]);
    for(size_t i = 0; i < size_; i++){
        //set(i, get(i));
        //tmp[i], get(i);
        tmp[i] = get(i);
    }
    capacity_ *= 2; //eso pq después te lo comprueba y pq hay q hacerlo
    data_ = tmp;
    front_ = 0;
    back_ = size_ - 1; 
    //
    assert(capacity() == 2 * old_capacity);
    assert(get(0) == old_front);
    assert(get(size() - 1) == old_back);
}