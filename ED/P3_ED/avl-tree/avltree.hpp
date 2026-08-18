/**
 * @file avltree.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <iostream>
#include <tuple>
#include <avltree_node.hpp>
#include <avltree_iterator.hpp>

/**
 * @brief ADT AVLTree.
 * A AVLTree is a binary tree that meets the next two invariants:
 * is_a_binary_search_tree()
 * is_a_balanced_tree()
 */
template <class T>
class AVLTree
{
public:
  /** @name Life cicle.*/
  /** @{*/

  /**
   * @brief Create an empty AVLTree.
   * @post is_empty()
   * @post !current_exists()
   * @post height()==-1
   */
  AVLTree();

  /**
   * @brief Create a leaf tree.
   * @param item is the value of the root's item.
   * @post !is_empty()
   * @post current_exists()
   * @post item()==item
   * @post current()==item
   * @post current_level()==0
   * @post height()==0
   */
  AVLTree(T const &item);

  /**
   * @brief Unfold an AVLTree from an input stream.
   * The input format will be:
   * '[]' for the empty tree.
   * '[ '<item>' '<left-subtree>' '<right-subtree>' ]'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @param in is the input stream.
   * @param parent is the parent node of the node to be unfolded.
   * @return The node unfolded on success.
   * @warning std::runtime_error("Wrong input format"),
   * std::runtime_error("It is not a binary search tree") or
   * std::runtime_error("It is not an avl bstree") will throw if an error
   * happened.
   */
  AVLTree(std::istream &in) noexcept(false);

  /** @brief Destroy a AVLTree.**/
  ~AVLTree();

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty() const;

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T const &item() const;

  /**
   * @brief Fold an AVLTree into an output stream.
   *  * The output format will be:
   * [ <item> <left> <right> ] or [] if it is a empty tree.
   * @param out is the output stream.
   * @return the output stream.
   */
  std::ostream &fold(std::ostream &out) const;

  /** @brief Is the cursor at a valid position?*/
  bool current_exists() const;

  /**
   * @brief Get the current's item.
   * @return The item save in current node.
   * @pre current_exist()
   */
  T const &current() const;

  /**
   * @brief Computes the current's level (depth) in the tree.
   * @return the level (depth) of current in the tree.
   * @pre current_exist()
   * @post Time analysis: O(H)
   */
  int current_level() const;

  /**
   * @brief Get the left subtree.
   * @pre !is_empty()
   */
  AVLTree<T> left() const;

  /**
   * @brief Get the right subtree.
   * @pre !is_empty()
   */
  AVLTree<T> right() const;

  /**
   * @brief Return the number of keys stored in the tree.
   * @return the tree's size.
   * @post Time analysis: O(N)
   */
  size_t size() const;

  /**
   * @brief Return the tree's height.
   * @return the tree's height.
   * @post Time analysis: O(1)
   */
  int height() const;

  /**
   * @brief Get balance factor of the tree.
   * @return the tree's balanced factor.
   * @post Time analysis: O(1)
   */
  int balance_factor() const;

  /**
   * @brief Has the tree this key?
   * @post !is_empty() || has==false;
   * @post !old.current_exists() || old.current()==current()
   */
  bool has(const T &k) const;

  /**
   * @brief Get an iterator at the begging of an in-order traversal of the tree.
   *
   * @return AVLTreeIterator<T>
   */
  AVLTreeIterator<T> begin() const;

  /**
   * @brief Get an iterator at the end of an in-order traversal of the tree.
   *
   * @return AVLTreeIterator<T>
   */
  AVLTreeIterator<T> end() const;

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief Create the Root node.
   * @param item is value of the root's item.
   * @post !is_empty()
   * @post current_exists()
   * @post item()==item
   * @post current()==item
   * @post current_level()==0
   * @post height()==0   */
  void create_root(T const &item);

  /**
   * @brief Search a key moving the cursor.
   * @post search==false || current()==k
   * @post search==true || !current_exits()
   */
  bool search(T const &k);

  /**
   * @brief Insert a new key in the tree.
   * @warning if k is already in the tree, only it is updated.
   * @post current_exists()
   * @post current()==k
   */
  void insert(T const &k);

  /**
   * @brief remove current from the tree.
   * @pre current_exists()
   * @post not current_exists()
   */
  void remove();

  /** @}*/

protected:
  /**
   * @brief Check the binary search tree invariant.
   * @return true if in-order traversal follow an ordered key sequence.
   * @post Time Analysis: O(N)
   */
  bool is_a_binary_search_tree() const;

  /**
   * @brief Check the balanced tree invariant.
   * A tree is balanced is empty or the left and right subtrees are balanced and
   * its balance factor is in {-1,0,1}.
   * @return true if left and right trees are balanced and this tree is balanced.
   */
  bool is_a_balanced_tree() const;

  /** @brief Create a AVLTree using a given node as root.*/
  AVLTree(typename AVLTNode<T>::Ref const &root_node);

  /**
   * @brief Attach a new subtree as left child.
   * @param subtree is the tree to be attached.
   * @post (subtree.is_empty() || left().item() == subtree.item())
   * @post (!subtree.is_empty() || left().is_empty())
   * @warning this method does not check invariants.
   */
  void set_left(AVLTree<T> &subtree);

  /**
   * @brief Attach a new subtree as right child.
   * @param subtree is the tree to be attached.
   * @post (subtree.is_empty() || right().item() == subtree.item())
   * @post (!subtree.is_empty() || right().is_empty())
   * @warning this method does not check invariants.
   */
  void set_right(AVLTree<T> &subtree);

  /**
   * @brief find the sucessor in order of current.
   * @pre current_exist()
   * @post current_exist() && !current_->has_left()
   * @post current()>old.current()
   */
  void find_inorder_sucessor();

  /**
   * @brief rotate to re-balanced a subtree.
   *
   * Rotate left (@a dir == 0)
   *
   *               P      ->    N
   *              / \          / \
   *             S   N        P   D
   *                /  \     / \
   *               C    D   S   C
   *
   * Rotate right (@a dir == 1)
   *
   *               P      ->    N
   *              / \          / \
   *             N   S        D   P
   *           /  \              / \
   *          D    C            C   S
   *
   * @param P is the root node of the subtree.
   * @param dir is the direction (0->left, 1->right) to rotate.
   * @return S, the new root node of the rotated subtree.
   * @pre P!=nullptr
   * @pre dir in {0,1}
   * @pre N==P->child(1-dir) != nullptr
   */
  typename AVLTNode<T>::Ref rotate(typename AVLTNode<T>::Ref &P, int dir);

  /**
   * @brief make a balanced tree.
   * Process from cursor's parent_ going up to the root doing rotations if needed.
   */
  void make_balanced();

  /**
   * @brief get the root node.
   * @return the root node.
   */
  typename AVLTNode<T>::Ref const &root_node() const;

  /**
   * @brief get the root node.
   * @return the root node.
   */
  typename AVLTNode<T>::Ref &root_node();

  /**
   * @brief set the root node.
   * @post new_root == root_node()
   */
  void set_root_node(typename AVLTNode<T>::Ref const &new_root);

  /**
   * @brief get the current node.
   * @return the current node.
   */
  typename AVLTNode<T>::Ref const &current_node() const;

  /**
   * @brief get the current node.
   * @return the current node.
   */
  typename AVLTNode<T>::Ref &current_node();

  /**
   * @brief Set the current node object
   *
   * @param new_c the new current node.
   */
  void set_current_node(typename AVLTNode<T>::Ref const &new_c);

  /**
   * @brief get the parent node.
   * @return the parent node.
   */
  typename AVLTNode<T>::Ref const &parent_node() const;

  /**
   * @brief get the parent node.
   * @return the parent node.
   */
  typename AVLTNode<T>::Ref &parent_node();

  /**
   * @brief Set the parent node object
   *
   * @param new_p the new parent.
   */
  void set_parent_node(typename AVLTNode<T>::Ref const &new_p);

  /**
   * @brief Check the chains from leaf nodes to the root node.
   */
  bool check_parent_chains() const;

  // TODO
  // Give a representation.
  typename AVLTNode<T>::Ref root_;
  typename AVLTNode<T>::Ref current_;
  typename AVLTNode<T>::Ref parent_;
  //
};

#ifdef __ONLY_BSTREE__
#include <vector>
/**
 * @brief create a perfectly balanced BSTree.
 * @param data are the keys to be stored.
 * @return the created tree.
 * @pre data.size()>0
 * @post for each subtree: |right()->size() - left()->size()|<=1
 */
template <class T>
AVLTree<T> create_perfectly_balanced_bstree(std::vector<T> &data);
#endif //__ONLY_BSTREE__

/**
 * @brief Compute the min,max branch length from root to any leaf.
 *
 * If the tree is empty, the min and max path lengths are -1.
 *
 * @param tree is the tree.
 * @return std::tuple<size_t, size_t> (min, max path lengths).
 * @pre tree != nullptr
 */
template <class T>
std::tuple<int, int>
compute_min_max_branch_length(AVLTree<T> const &tree);

#include <avltree_imp.hpp>