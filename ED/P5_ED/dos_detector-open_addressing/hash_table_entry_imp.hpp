/**
 * @file hash_table_entry_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <cassert>
#include <hash_table_entry.hpp>

template <class K, class V>
HashTableEntry<K, V>::HashTableEntry()
{
    // TODO
    state_ = EMPTY; //constructor por defecto
    data_ = std::make_pair(K(), V()); //Inicializa los datos con valores por defecto para la clave (K()) y el valor (V()).
    //
    assert(is_empty());
}

template <class K, class V>
HashTableEntry<K, V>::HashTableEntry(const K &k, const V &v)
{
    // TODO  //constructor de copia
    state_ = VALID; //estado de la entrada
    data_ = std::make_pair(k, v); //Almacena la clave y el valor proporcionados.
    //
    assert(is_valid());
    assert(key() == k);
    assert(value() == v);
}

template <class K, class V>
bool HashTableEntry<K, V>::is_valid() const
{
    bool ret_val = false;
    // TODO
    ret_val = (state_ == VALID); //Observer
    //
    return ret_val;
}

template <class K, class V>
bool HashTableEntry<K, V>::is_empty() const
{
    bool ret_val = false;
    // TODO
    ret_val = (state_ == EMPTY); //Observer
    //
    return ret_val;
}

template <class K, class V>
bool HashTableEntry<K, V>::is_deleted() const
{
    bool ret_val = false;
    // TODO
    ret_val = (state_ == DELETED); //Observer
    //
    return ret_val;
}

template <class K, class V>
K const &
HashTableEntry<K, V>::key() const
{
    assert(!is_empty());
    // TODO: recode according to your representation.
    /*K aux;
    return aux;*/
    return data_.first; //Get first entry -> key
    //
}

template <class K, class V>
void HashTableEntry<K, V>::set(const K &k, const V &v)
{
    // TODO
    data_ = std::make_pair(k, v);
    state_ = VALID;
    //
    assert(is_valid());
    assert(key() == k);
    assert(value() == v);
}

template <class K, class V>
V const &HashTableEntry<K, V>::value() const
{
    // TODO: recode according to your representation.
    /*V aux;
    return aux;*/ //<k,v> key, value
    return data_.second; //Get second entry -> value
    //
}

template <class K, class V>
void HashTableEntry<K, V>::set_value(const V &new_v)
{
    assert(is_valid());

    // TODO: recode according to your representation.
    data_.second = new_v;
    //
    assert(is_valid());
    assert(value() == new_v);
}

template <class K, class V>
void HashTableEntry<K, V>::set_deleted()
{
    assert(is_valid());
    // TODO
    state_ = DELETED;
    //
    assert(is_deleted());
}
