/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <memory>
#include <iostream>

#include <btree_node.hpp>

/**
 * @brief ADT BTree.
 * Models a BTree of T.
 */
template <class T>
class BTree
{
public:
  /** @name Life cycle.*/
  /** @{*/

  /** @brief Create an empty BTree.
   * @post is_empty()
   */
  BTree();

  /** @brief Create Leaf BTree.
   * @post not is_empty()
   * @post left()->is_emtpy()
   * @post right()->is_emtpy()
   */
  BTree(const T &item);

  /**
   * @brief Copy constructor.
   */
  BTree(const BTree<T> &other);

  /**
   * @brief Move constructor.
   */
  BTree(BTree<T> &&other);

  /**
   * @brief Load a tree from a input stream.
   *
   * The input format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @return a reference to the tree created.
   * @warning runtime_error will throw if wrong input format was found.
   */
  BTree(std::istream &in) noexcept(false);

  /** @brief Destroy a BTree.**/
  ~BTree()
  {
  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the tree empty?.*/
  bool is_empty() const;

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T item() const;

  /**
   * @brief Get the left subtree.
   * @return a reference to the left subtree.
   * @pre !is_empty()
   */
  BTree<T> left() const;

  /**
   * @brief Get the right subtree.
   * @return a reference to the right subtree.
   * @pre !is_empty()
   */
  BTree<T> right() const;

  /**
   * @brief Fold a binary tree.
   *
   * The output format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @param out is the output stream.
   * @param tree is the tree.
   * @return the output stream.
   * @pre tree!=nullptr
   */
  std::ostream &fold(std::ostream &out) const;

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief create the root node.
   * @arg it is the item to be stored.
   * @pre is_empty()
   * @post !is_empty()
   * @post item()==it
   * @post left().is_empty()
   * @post right().is_empty()
   */
  void create_root(T const &it);

  /**
   * @brief set the root's item.
   * @pre not is_empty()
   */
  void set_item(const T &new_it);

  /**
   * @brief Attach a new subtree as left child of root.
   * @param new_left is the new left subtree.
   * @pre !is_empty()
   */
  void set_left(const BTree<T> &new_left);

  /**
   * @brief Attach a new subtree as right child of root.
   * @param new_right is the new right subtree.
   * @pre !is_empty()
   */
  void set_right(const BTree<T> &new_right);

  /**
   * @brief Assign operator (copy semantics)
   *
   * @param other the tree to be moved.
   * @return BTree<T>& moved tree.
   */
  BTree<T> &operator=(const BTree<T> &other);

  /**
   * @brief Assign operator (move semantics)
   *
   * @param other the tree to be moved.
   * @return BTree<T>& moved tree.
   */
  BTree<T> &operator=(BTree<T> &&other);

  /** @}*/

protected:
  /** @brief Create a BTree using a given node as root.
   * @param n is the root node.
   * @post root()==n
   */
  BTree(const typename BTNode<T>::Ref &n);

  /**
   * @brief Get the root node.
   * @return a reference to the root node or nullptr if it is empty.
   */
  typename BTNode<T>::Ref root() const;

  /** @brief set a new root node.
   * @param new_root is the new root node.
   * @post root()==new_root
   */
  void set_root(const typename BTNode<T>::Ref &new_root);

  /**
   * We represent the TAD Binary Tree as a root node chaining to two possible
   * left/right child nodes whose will be the root nodes of the respective
   * left/right subtrees.
   */
  typename BTNode<T>::Ref _root;
};

#include "btree_imp.hpp"