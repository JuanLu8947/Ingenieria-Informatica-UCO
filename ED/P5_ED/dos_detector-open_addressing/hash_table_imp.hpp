/**
 * @file hash_table_imp.hpp
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

#include <hash_table.hpp>
#include <hash_table_iterator.hpp>

template <class K, class V>
HashTable<K, V>::HashTable(size_t m,
                           const Key_to_uint64_t &key_to_int,
                           OACollisionResolution::Ref hash)
{
    assert(m == hash->m());
    // TODO  //constructor de copia
    key_to_int_ = key_to_int; //f(x) conversión de key a int
    hash_ = hash; //f(x) hash -> estrategia resolución colisiones
    table_.resize(m); //redimensionar tabla a M
    used_entries_ = 0; //contador de entradas usadas en la tabla, tb notado como N
    //
    assert(size() == m);
}

template <class K, class V>
size_t
HashTable<K, V>::size() const
{
    size_t ret_v = 0;
    // TODO
    ret_v = table_.size(); //Get
    //
    return ret_v;
}

template <class K, class V>
float HashTable<K, V>::load_factor() const
{
    float ret_v = 0.0f;
    // TODO  //Get -> a = N/M
    ret_v = static_cast<float>(used_entries_) / static_cast<float>(size());
    //
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::begin() const
{
    HashTableIterator<K, V> ret_v;
    // TODO
    // Remember: the iterator should point to the first valid entry.
    // Hint: you must use const_cast to remove the const qualifier from this.
    
    // Inicializamos el iterador al final de la tabla -> si no hay entradas válidas, begin() == end()
    ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), size());
    for (size_t i = 0; i < size(); ++i){ //recorremos la tabla para encontrar la primera entrada válida
        if (entry(i).is_valid()){
            // Si encontramos una entrada válida, creamos el iterador en esta posición
            ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), i);
            break;
        }
    }
    /*
    Resumen
    ·Devuelve un iterador que apunta a la primera entrada válida de la tabla.
    ·Si no hay entradas válidas, el iterador apunta al final de la tabla (begin() == end())
    */
    //
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::end() const
{
    HashTableIterator<K, V> ret_v;
    // TODO
    // Remember: the iterator should point one position pass the end of the table.
    // Hint: you must use const_cast to remove the const qualifier from this.
    ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), size()); //Get
    //
    assert(!ret_v.is_valid());
    return ret_v;
}

template <class K, class V>
size_t HashTable<K, V>::find_position(K const &k) const
{
    assert(load_factor() < 1.0f);
    size_t idx = 0;
    // TODO
    auto h = key_to_int_(k); // Buscamos la posición de la clave k en la tabla hash
    bool found = false;
    size_t i = 0;
    idx = hash_->operator()(h, i);
    size_t first_deleted_pos = size(); // Posición para recordar el primer slot eliminado

    //Se realiza una búsqueda hasta encontrar la clave, o un slot vacío o hasta haber recorrido toda la tabla
    while (i < size() && !found){
        idx = hash_->operator()(h, i);
        if (entry(idx).is_valid()){
            if (entry(idx).key() == k) // Si la entrada es válida y la clave coincide, se ha encontrado la posición
                found = true;
            else{ //si no coincide, se sigue buscando
                ++i;
            }
        }
        else if (entry(idx).is_deleted()){ // Si la entrada está marcada como eliminada, recordamos la primera posición eliminada
            if (first_deleted_pos == size())
                first_deleted_pos = idx;
                
            ++i;
        }
        else{ // Si encontramos una entrada vacía (nunca usada), terminamos la búsqueda
            break;
        }
    }
    // Si no encontramos la clave pero hay una posición eliminada, devolvemos esa posición
    if (!found && first_deleted_pos < size())
        idx = first_deleted_pos;
    /*
    ·Encuentra la posición de una clave k en la tabla:
     ·Usa la función hash para calcular el índice inicial.
     ·Si encuentra una entrada válida con la clave, devuelve su índice.
     ·Si encuentra una entrada marcada como eliminada, guarda su posición para reutilizarla si no se encuentra la clave.
     ·Si no encuentra la clave, devuelve la posición de la primera entrada eliminada o una posición vacía.
    */
    //
    assert(0 <= idx && idx < size());
    return idx;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::find(K const &k) const
{
    HashTableIterator<K, V> ret_v = end();
    // TODO
    // Hint: use find_position.
    // Hint: you must use const_cast to remove the const qualifier from this.
    size_t idx = find_position(k);
    if (entry(idx).is_valid())
        ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), idx);
    else{
        ret_v = end();
    }
    /*
    ·Busca una clave k en la tabla:
     ·Usa find_position() para encontrar la posición de la clave.
     ·Si la entrada es válida, devuelve un iterador a esa posición.
     ·Si no, devuelve un iterador al final de la tabla.
    */
    //
    assert(ret_v == end() || (ret_v.is_valid() && ret_v.key() == k));
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::insert(K const &k, V const &v)
{
    assert(load_factor() <= 0.5f);
    HashTableIterator<K, V> ret_v = end();
    const size_t current_size = size();
    // TODO
    // Remember: increment the number of used entries only when an
    //    empty entry was used.
    // Remember: you must call to rehash before inserting a new entry to avoid
    //    a load factor greater than 0.5.
    // Remember: if a rehashing was done (current_size != new size returned by
    //    rehash function), you need to find the new location of the inserted key.
    size_t idx = find_position(k);
    if(!entry(idx).is_empty() && entry(idx).is_valid()){ //Si la clave ya existe -> se actualiza el valor
        entry(idx).set(k, v);
        ret_v = HashTableIterator<K, V>(this, idx);
        return ret_v;
    }

    if((used_entries_ + 1.0f) / current_size > 0.5f){ //Si el factor de carga supera 0.5, se realiza un rehash
        rehash();
        idx = find_position(k); //Se recalcula la posición de la clave
    }

    if (entry(idx).is_empty()) // Si la entrada está vacía, simplemente se incrementa el contador de entradas usadas
        used_entries_++;
    
    entry(idx).set(k, v);
    ret_v = HashTableIterator<K, V>(this, idx);
    /*
    ·Inserta una clave-valor en la tabla:
     ·Si la clave ya existe, actualiza su valor.
     ·Si el factor de carga supera 0.5, realiza un rehash() antes de insertar.
     ·Incrementa used_entries_ solo si se usa una entrada vacía.
    */
    //
    assert(ret_v.is_valid());
    assert(ret_v.key() == k);
    assert(ret_v.value() == v);
    assert(load_factor() <= 0.5f);
    return ret_v;
}

template <class K, class V>
void HashTable<K, V>::remove(HashTableIterator<K, V> &iter)
{
#ifndef NDEBUG
    assert(iter.is_valid());
    K old_k = iter.key();
#endif
    // TODO
    // Remember: we are using a mark to sign "deleted".
    entry(iter.index()).set_deleted(); //Marcamos la entrada como eliminada
    iter = end(); // Reasignamos el iterador al final de la tabla, de forma que se pueda usar de nuevo
    /*
    IMPORTANTE: sólo se deja marcado, con lo que NO se decrementa el contador de entradas usadas.
    */
    //
    assert(!iter.is_valid());
    assert(find(old_k) == end());
}

template <class K, class V>
size_t HashTable<K, V>::rehash()
{
    // TODO
    // Remember: rehash when load_factor > 0.5
    // Remember: we use a 2 factor to grown the current size.
    // Remember: a new hash function will be picked at random from the Universal Family.
    // Remember: reset the number of used entries to zero before inserting the old valid
    // entries in the new table.
    auto oldtable = table_;
    table_ = std::vector<HashTableEntry<K, V>>(2 * oldtable.size()); //Se crea una nueva tabla con el doble de tamaño
    hash_ = hash_->pick_at_new(table_.size()); //Se elige una nueva función hash para la nueva tabla
    used_entries_ = 0;

    //Reinsertamos todas las entradas válidas en la nueva tabla
    for(size_t i = 0; i < oldtable.size(); i++)
        if(oldtable[i].is_valid()){
            size_t idx = find_position(oldtable[i].key()); //calculamos la nueva posición de la clave
            table_[idx].set(oldtable[i].key(), oldtable[i].value());
            used_entries_++;
        }
    /*
    ·Duplica el tamaño de la tabla y selecciona una nueva función hash.
    ·Reinsertar todas las entradas válidas en la nueva tabla.
    ·Reinicia used_entries_ a 0 y lo actualiza durante la reinserción.
    */
    //
    assert(load_factor() <= 0.5);
    return size();
}

template <class K, class V>
HashTableEntry<K, V> const &HashTable<K, V>::entry(size_t idx) const
{
    assert(idx < size());
    // TODO: recode according to your representation.
    /*HashTableEntry<K, V> aux;
    return aux;*/
    return table_[idx]; //Get entry index
    //
}

template <class K, class V>
HashTableEntry<K, V> &HashTable<K, V>::entry(size_t idx)
{
    assert(idx < size());
    // TODO: recode according to your representation.
    /*HashTableEntry<K, V> aux;
    return aux;*/
    return table_[idx]; //same
    //
}
