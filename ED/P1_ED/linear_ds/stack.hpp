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

#include "list.hpp"

/**
 * @brief ADT Stack.
 * Models a Stack using a simple list.
 */
template <class T>
class Stack
{
public:
  /** @name Life cycle.*/
  /** @{*/

  /** @brief Create an empty Stack.
   * @post is_empty()
   */
  Stack();

  /** @brief Destroy a Stack.**/
  ~Stack()
  {
  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty() const;

  /** @brief Get the number of items in the stack.*/
  size_t size() const;

  /** @brief get the top item.
   * @pre not is_empty()
   */
  T const &top() const;

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief Insert a new item.
   * @post top() == new_it
   * @post size() = old.size()+1
   */
  void push(const T &new_it);

  /** Remove the top item.
   * @pre not is_empty()
   * @post size() = old.size()-1
   */
  void pop();

  /** @} */

protected:
  List<T> l_;
};

#include <stack_imp.hpp>