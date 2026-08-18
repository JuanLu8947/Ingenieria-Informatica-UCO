/**
 * @file hash_table_entry.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <utility>
#include <memory>

/**
 * @brief Models an entry of a hash table.
 *
 * An entry has three states: empty, valid, deleted.
 * The entry data is a <Key,Value> pair.
 *
 * The template parameters K and V must have
 * default constructors.
 */
template <class K, class V>
class HashTableEntry
{
public:
    /** @name Life cycle.*/
    /** @{*/
    /**
     * @brief Create an empty entry.
     * @warning template parameters K,V must have a default constructor.
     * @post is_empty()
     */
    HashTableEntry();

    /**
     * @brief Create a valid entry.
     * @param k is the key data of the pair.
     * @param v is the value data of the pair.
     * @post is_valid()
     * @post key()==k
     * @post value()==v
     */
    HashTableEntry(const K &k, const V &v);
    /** @}*/

    /** @name Observers.*/
    /** @{ */
    /**
     * @brief Check if the entry's state is Empty.
     * @return true if the entry's state is empty.
     */
    bool is_empty() const;
    /**
     * @brief Check if the entry's state is Deleted.
     * @return true if the entry's state is Deleted.
     */
    bool is_deleted() const;

    /**
     * @brief Check if the entry's state is Valid.
     * @return true if the entry's state is Valid.
     */
    bool is_valid() const;

    /**
     * @brief Get the key value of the entry.
     * @return the key value.
     * @pre !is_empty()
     */
    K const &key() const;

    /**
     * @brief Get the value data of the entry.
     * @return the value.
     * @pre !is_empty()
     */
    V const &value() const;

    /** @} */

    /** @name Modifiers.*/
    /** @{ */
    /**
     * @brief Set the pair <key,value>.
     * @post is_valid()
     * @post key()==k
     * @post value()==v
     */
    void set(const K &k, const V &v);

    /**
     * @brief Set the value data.
     * @param new_v is the new value data.
     * @pre is_valid()
     * @post value()==new_v
     */
    void set_value(const V &new_v);

    /**
     * @brief Set the state of the entry to Deleted.
     * @pre is_valid()
     * @post is_deleted()
     */
    void set_deleted();

    /** @} */

protected:
    /**
     * @brief The entry's states.
     */
    enum EntryState
    {
        EMPTY = 0,
        VALID = 1,
        DELETED = 2
    };

    // TODO
    // Hint: consider the use of std::pair to store the <K,V> pair.
    EntryState state_;
    std::pair<K, V> data_;
    //
};

#include <hash_table_entry_imp.hpp>
