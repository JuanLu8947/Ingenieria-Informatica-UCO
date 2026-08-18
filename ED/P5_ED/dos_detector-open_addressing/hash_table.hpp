/**
 * @file hash_table.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <cstdlib>
#include <cstdint>
#include <vector>
#include <functional>
#include <utility>

#include <hash.hpp>
#include <hash_table_entry.hpp>

// Forward declarations
template <class K, class V>
class HashTableIterator;

/**
 * @brief Implement the HashTable[K,V] ADT.
 *
 * @tparam K are the keys.
 * @tparam V are the values.
 *
 * @invariant load_factor() <= 0.5
 */

template <class K, class V>
class HashTable
{
public:
  /** @brief Functional type to do "key to std::uint64_t" conversions.*/
  typedef std::function<std::uint64_t(const K &)> Key_to_uint64_t;

  /** @name Life cicle.*/
  /** @{*/

  /**
   * @brief Create a new HashTable.
   * @param m is the table size.
   * @param key_to_int is the converter from key values to int value.
   * @param hash is the hash function.
   * @post not is_valid()
   * @post size()==m
   */
  HashTable(size_t m, Key_to_uint64_t const &key_to_int,
            OACollisionResolution::Ref hash);

  /** @}*/

  /** @name Observers*/
  /** @{*/

  /**
   * @brief Get the table size.
   * @return the size of the table.
   */
  size_t size() const;

  /**
   * @brief Return the load factor of the table.
   * @return the load factor.
   */
  float load_factor() const;

  /**
   * @brief Find the table's entry with the given key.
   * @return an iterator at the table's entry with the given key or end() if not found.
   * @post 0<=ret_v<size()
   */
  HashTableIterator<K, V> find(K const &k) const;

  /**
   * @brief Get an iterator to the first valid table entry.
   *
   * @return the iterator to the first valid table entry.
   */
  HashTableIterator<K, V> begin() const;

  /**
   * @brief Get an iterator to the end of the table.
   *
   * @return the iterator to the end of the table.
   */
  HashTableIterator<K, V> end() const;

  /** @}*/

  /** @name Modifiers*/
  /** @{*/

  /**
   * @brief Insert a new entry or update the value of an existing entry.
   *
   * @return an iterator at the table's entry with the given key.
   * @post ret_v.is_valid()
   * @post ret_v.get_key()==k
   * @post ret_v.get_value()==v
   */
  HashTableIterator<K, V> insert(K const &k, V const &v);

  /**
   * @brief Remove the entry at the iterator position.
   * @pre iter.is_valid()
   * @post !iter.is_valid()
   * @post find(old iter.get_key())==end()
   */
  void remove(HashTableIterator<K, V> &iter);

  /**
   * @brief Get a table entry.
   *
   * @param idx is a table position.
   * @return return a reference to the entry at the table position.
   * @pre 0<=idx<size()
   */
  HashTableEntry<K, V> const &entry(size_t idx) const;

  /** @} */

protected:
  friend class HashTableIterator<K, V>;
  /**
   * @brief Find the table index where the key should be.
   * @return the table index where the key should be.
   * @post 0<=ret_v<size()
   */
  size_t find_position(K const &k) const;

  /**
   * @brief Get a table entry.
   *
   * @param idx is a table position.
   * @return return a reference to the entry at the table position.
   * @pre 0<=idx<size()
   */
  HashTableEntry<K, V> &entry(size_t idx);

  /**
   * @brief Generate a new table with doble size when load factor > 0.5
   * @return the table size (the old size if growing was not necessary).
   * @post load_factor()<=0.5
   */
  size_t rehash();

  Key_to_uint64_t key_to_int_;              /**< Convert key values to int.*/
  OACollisionResolution::Ref hash_;         /**< The hash function.*/
  std::vector<HashTableEntry<K, V>> table_; /**< The table.*/
  size_t used_entries_;                     /**< Counter for the used entries (valid and deleted).*/
};

#include <hash_table_imp.hpp>
