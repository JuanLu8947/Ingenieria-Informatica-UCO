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
#include <hash_table.hpp>

/**
 * @brief A forward iterator to traverse the hash table.
 *
 * @tparam K
 * @tparam V
 */
template <class K, class V>
class HashTableIterator
{
public:
    /** @name Life cicle.*/
    /** @{*/

    HashTableIterator();

    /** @} */
    /** @name Observers*/
    /** @{*/

    /**
     * @brief the iterator is in a valid position of the table.
     *
     * @return true if the iterator is in a valid position.
     */
    bool is_valid() const;
    /**
     * @brief Compare two iterators.
     * @param other the other iterator.
     * @return true if the iterators are equal.
     */
    bool operator==(HashTableIterator const &other) const;

    /**
     * @brief Compare two iterators.
     *
     * @param other the other iterator.
     * @return true if the iterators are different.
     */
    bool operator!=(HashTableIterator const &other) const;

    /**
     * @brief Get the key object associated to the table's entry at the iterator's position.
     *
     * @return the key object.
     * @pre is_valid()
     */
    K const &key() const;

    /**
     * @brief Get the value object associated to the table's entry at the iterator's position.
     *
     * @return the value object.
     * @pre is_valid()
     */
    V const &value() const;

    /**
     * @brief Get table's index where the iterator is.
     *
     * @return the table index.
     */
    size_t index() const;

    /**
     * @brief Set the value object associated to the table's entry at the iterator's position.
     *
     * @param new_v is the new value object.
     * @pre is_valid()
     * @post get_value()==new_v
     */
    void set_value(V const &new_v) const;
    /** @} */

    /** @name Modifiers*/
    /** @{*/
    /**
     * @brief Move the iterator to the next valid position.
     *
     * @return the iterator.
     * @pre is_valid()
     */
    HashTableIterator &operator++();
    /**
     * @brief Move the iterator to the next valid position.
     *
     * @return HashTableIterator
     * @pre is_valid()
     */
    HashTableIterator operator++(int);
    /** @} */

protected:
    friend class HashTable<K, V>;

    /**
     * @brief Construct a new Hash Table Iterator object
     */
    HashTableIterator(HashTable<K, V> *ht, size_t idx);

    /**
     * @brief Get a const pointer to the hash table.
     *
     * @return the const pointer.
     */
    const HashTable<K, V> *table() const;

    /**
     * @brief Get a pointer to the hash table.
     *
     * @return the pointer.
     */

    HashTable<K, V> *table();

    // TODO
    // Hint: you need to store a pointer to the hash table and the current index.
    HashTable<K, V> *ht_;
    size_t idx_;
    //
};

#include <hash_table_iterator_imp.hpp>