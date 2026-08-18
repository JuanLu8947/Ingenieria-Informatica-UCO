/**
 * @file hash_table_iterator.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <hash_table_iterator.hpp>

template <class K, class V>
size_t HashTableIterator<K, V>::index() const
{
    // TODO
    return idx_; //Get actual index
    //
}

template <class K, class V>
const HashTable<K, V> *HashTableIterator<K, V>::table() const
{
    // TODO
    return ht_; //Get - puntero a la tabla hash
    //
}

template <class K, class V>
HashTable<K, V> *HashTableIterator<K, V>::table()
{
    // TODO
    return ht_;
    //
}

template <class K, class V>
HashTableIterator<K, V>::HashTableIterator()
{
    // TODO
    ht_ = nullptr; //constructor por defecto
    idx_ = 0;
    //
    assert(table() == nullptr);
    assert(index() == 0);
    assert(!is_valid());
}

template <class K, class V>
HashTableIterator<K, V>::HashTableIterator(HashTable<K, V> *ht, size_t idx)
{
    assert(ht != nullptr);
    // TODO
    ht_ = ht; //constructor de copia
    idx_ = idx;
    //
    assert(table() == ht);
    assert(index() == idx);
}

template <class K, class V>
bool HashTableIterator<K, V>::is_valid() const
{
    // TODO
    // Remember: check that idx_ is in the table's range and the entry is valid.
    return ht_ != nullptr && idx_ < ht_->size() && ht_->entry(idx_).is_valid(); //observer
    /*
    ·Verifica si el iterador es válido:
     ·ht_ != nullptr: Está asociado a una tabla.
     ·idx_ < ht_->size(): El índice está dentro del rango de la tabla.
     ·ht_->entry(idx_).is_valid(): La entrada en el índice actual es válida.
    */
    //
}

template <class K, class V>
HashTableIterator<K, V> &
HashTableIterator<K, V>::operator++()
{
    assert(is_valid());
    // TODO
    do{
        ++idx_;
    }while (idx_ < ht_->size() && !ht_->entry(idx_).is_valid());
    /*
    ·Avanza el iterador al siguiente índice válido en la tabla:
     ·Incrementa idx_ hasta encontrar una entrada válida o llegar al final de la tabla.
    ·Devuelve una referencia al iterador actualizado.
    */
    //
    return *this;
}

template <class K, class V>
HashTableIterator<K, V>
HashTableIterator<K, V>::operator++(int)
{
    assert(is_valid());
    HashTableIterator ret_v(*this);
    ++(*this);
    return ret_v;
}

template <class K, class V>
bool HashTableIterator<K, V>::operator==(HashTableIterator<K, V> const &other) const
{
    bool ret_v = false;
    // TODO //'==' -> compara 2 iteradores
    ret_v = table() == other.table() && index() == other.index();
    //
    return ret_v;
}
template <class K, class V>
bool HashTableIterator<K, V>::operator!=(HashTableIterator<K, V> const &other) const
{
    return !(*this == other);
}

template <class K, class V>
K const &
HashTableIterator<K, V>::key() const
{
    // TODO
    return ht_->entry(idx_).key(); //Get entry_index_key
    //
}

template <class K, class V>
V const &
HashTableIterator<K, V>::value() const
{
    // TODO
    return ht_->entry(idx_).value(); //Get entry_index_value
    //
}

template <class K, class V>
void HashTableIterator<K, V>::set_value(V const &v) const
{
    // TODO
    ht_->entry(idx_).set_value(v);
    //
}
