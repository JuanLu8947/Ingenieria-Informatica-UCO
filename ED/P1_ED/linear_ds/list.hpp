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
#include <functional>
#include <list_node.hpp>
#include <list_iterator.hpp>

/**
 * @brief ADT List.
 * Models a Double linked list[T] with iterators to edit.
 */
template <class T>
class List
{
public:
  /** @brief Define an iterator to edit the list.*/
  typedef ListIterator<T> iterator;

  /** @name Life cycle.*/
  /** @{*/

  /**
   * @brief Create a List.
   * @post is_empty()
   */
  List();

  /**
   * @brief Create a List unfolding from an input stream.
   *
   * The input format will be
   * '[' item1 item2 ... item_n ']' using space as token separator and item1
   * is the head.
   *
   * @param in is the input stream.
   * @warning if the input format is not correct a std::runtime_error with
   * what message "Wrong input format." will be raised.
   * @return A shared reference to the new list.
   */
  List(std::istream &in) noexcept(false);

  /** @brief Destroy a List.**/
  ~List();

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /**
   * @brief is the list empty?.
   * @return true if it is an empty list.
   */
  bool is_empty() const;

  /** @brief Get the number of items in the list.*/
  size_t size() const;

  /**
   * @brief Get the head item of the list.
   * @return the item at the head.
   * @pre !is_empty()
   */
  T const &front() const;

  /**
   * @brief Get the back item of the list.
   * @return the item at the back.
   * @pre !is_empty()
   */
  T const &back() const;

  /**
   * @brief Fold to an output stream.
   *
   * The format will be '[' item1 item2 item3 ... item_n ']'
   * using space as token separator and item1 is the head.
   *
   * @param out is the output stream.
   */
  void fold(std::ostream &out) const;

  /**
   * @brief Returns an iterator to the beginning.
   *
   * @return an iterator to the beginning.
   */
  iterator begin() const;

  /**
   * @brief Returns an iterator to the end.
   *
   * @return an iterator iterator to the end.
   */
  iterator end() const;

  /**
   * @brief Find an item in the list.
   * If the item is not found, the end iterator will be returned.
   * @param it is the value to be found.
   * @param from is the position from which to start searching.
   * @return an iterator to the first found position or end iterator if it was not found.
   * @post ret_val==end() || ret_val->item()==it
   */
  iterator find(T const &it, iterator const &from) const;

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief insert a new item before the position.
   * @param pos position in the list where inserting.
   * @param it is the item to insert.
   * @return an iterator points to the new item.
   * @post ret_v->item()==it
   * @post !old.is_empty() || (front()==it && back()==it)
   * @post old.is_empty() || ret_v->next()==pos
   * @post old.is_empty() || old.pos->prev()==ret_v->prev()
   * @post size()==(old.size()+1)
   */
  iterator insert(iterator const &pos, T const &it);

  /**
   * @brief Remove the item at a given position.
   * @pre pos is in a valid position [begin(), end())
   * @return an interator following the removed item.
   * @pre not is_empty()
   * @post ret_v == old pos->next()
   * @post ret_v->prev() == old pos->prev()
   * @post size()==(old.size()-1)
   */
  iterator remove(iterator const &pos);

  /**
   * @brief insert an item as the new list's head.
   * @param new_it is the item to insert.
   * @post front()==new_it
   * @post size()==(old.size()+1)
   */
  void push_front(T const &new_it);

  /**
   * @brief insert an item as the new list's back.
   * @param new_it is the item to insert.
   * @post front()==new_it
   * @post size()==(old.size()+1)
   */
  void push_back(T const &new_it);

  /**
   * @brief Remove the head.
   * @pre !is_empty()
   * @post size()==(old.size()-1)
   */
  void pop_front();

  /**
   * @brief Remove the back.
   * @pre !is_empty()
   * @post is_empty() || end()->prev() == old end()->prev()->prev()
   * @post size()==(old.size()-1)
   */
  void pop_back();

  /**
   * @brief Transfers elements from one list'range [first, last) to this list.
   *
   * No elements are copied or moved, only the internal pointers of the list
   * nodes are re-pointed. No iterators or references become invalidated,
   * the iterators to moved elements remain valid, but now refer into *this,
   * not into other.
   *
   * @param pos postion of this where transferring the nodes.
   * @param list2 the list from the nodes are transferred
   * @param first fist position in list2 of the range.
   * @param last last position in list2 of the range.
   */
  void splice(iterator const &pos, List<T> &list2,
              iterator const &first, iterator const &last);
  /**
   * @brief Transfers all elements from one list to this list.
   *
   * No elements are copied or moved, only the internal pointers of the list
   * nodes are re-pointed. No iterators or references become invalidated,
   * the iterators to moved elements remain valid, but now refer into *this,
   * not into other.
   *
   * @param pos postion of this where transferring the nodes.
   * @param list2 the list from the nodes are transferred.
   */
  void splice(iterator const &pos, List<T> &list2);

  /**
   * @brief Transfers one element from one list to this list.
   *
   * No elements are copied or moved, only the internal pointers of the list
   * nodes are re-pointed. No iterators or references become invalidated,
   * the iterators to moved elements remain valid, but now refer into *this,
   * not into other.
   *
   * @param pos position of this where transferring the nodes.
   * @param list2 the list from the nodes are transferred.
   * @param i position of the element to be transferred.
   */
  void splice(iterator const &pos, List<T> &list2, iterator const &i);

  /**
   * @brief merges other into this list.
   *
   * Both lists should be sorted. No elements are copied, and the container
   * other becomes empty after the merge.
   *
   * @tparam Compare comparison function object which returns ​true if the first argument is ordered before the second.
   *
   * The signature of the comparison function should be equivalent to
   * the following: bool cmp(const Type1& a, const Type2& b);
   *
   * @param other the list to be merged with this list.
   * @param cmp comparison object.
   */
  template <class Compare>
  void merge(List<T> &other, Compare cmp);

  /**
   * @brief Sorts the elements of the list.
   *
   * @tparam Compare comparison function object which returns ​true if the first argument is ordered before the second.
   *
   * The signature of the comparison function should be equivalent to
   * the following: bool cmp(const Type1& a, const Type2& b);
   *
   * @param cmp comparison object.
   *
   * @post time analysis: O(N Log N)
   */
  template <class Compare>
  void sort(Compare cmp);

  /** @}*/

protected:
  /**
   * @brief Hook a node to this list before pos.
   *
   * @param n the node to be hooked
   * @param pos the position where hooking the node.
   * @post size()=old.size()+1
   */
  void hook(typename DNode<T>::Ref n, typename DNode<T>::Ref pos);

  /**
   * @brief Unhook a node from the list.
   *
   * @param n the node to be unhooked.
   * @post size()==old.size()-1
   */
  void unhook(typename DNode<T>::Ref n);

  /**
   * @brief Get a reference to the dummy node.
   * The dummy node mark the "end" of the sequence and its linked with the
   * the head and the back of the list.
   * @return a reference to the head node.
   */
  typename DNode<T>::Ref dummy() const;

  /**
   * @brief Set the size of the list.
   */
  void set_size(size_t new_size);

  // TODO
  // Give a representation using a double linked list of nodes thats used
  // a dummy node to mark the "end" of the list.
  // Also we want a size() operation with O(1).
    //diseño TAD List[T]
    size_t size_;
    typename DNode<T>::Ref dummy_;
    /*
    es un miembro de la clase List que representa un puntero compartido (std::shared_ptr) a un nodo "dummy" en una lista doblemente enlazada. Aquí está el desglose:
     ·typename DNode<T>::Ref: Define un tipo de referencia compartida a un nodo de tipo DNode<T>.
     ·dummy_: Es una instancia de este tipo de referencia compartida que apunta a un nodo "dummy".
    */
  //
};

#include <list_imp.hpp>