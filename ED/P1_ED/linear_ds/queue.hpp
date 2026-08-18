/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <cstdlib>

#include <cdarray.hpp>

/**
 * @brief ADT Queue.
 * Models a queue of T.
 */
template <class T>
class Queue
{
public:
  /** @name Life cycle.*/
  /** @{*/

  /** @brief Create an empty Queue.
   * @post is_empty()
   */
  Queue();

  /** @brief Destroy a Queue.**/
  ~Queue()
  {
  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty() const;

  /** @brief Get the number of items in the queue.*/
  size_t size() const;

  /** @brief get the front item (the oldest one).
   * @pre not is_empty()
   */
  T const &front() const;

  /** @brief get the back item (the newest one).
   * @pre not is_empty()
   */
  T const &back() const;

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief Insert a new item.
   * @post back() == new_it
   * @post size()==(old.size()+1)
   */
  void enque(const T &new_it);

  /** @brief Remove the front item.
   * @pre not is_empty()
   * @post size()==(old.size()-1)
   */
  void deque();

  /** @} */

protected:
  // A CDArray is used to implement the queue.
  CDArray<T> data_;
};

#include <queue_imp.hpp>
