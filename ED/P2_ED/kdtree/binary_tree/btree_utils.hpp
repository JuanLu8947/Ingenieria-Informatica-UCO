/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

/**
 * @file btree_utils.hpp
 */

#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include <btree.hpp>

/**
 * @brief Compute the height of a tree.
 * The tree's height is the longitude of the longest branch connecting the root
 * node with a leaf node, or -1 if the tree was empty.
 *
 * @param t is the tree.
 * @return the tree's height or -1 if it is a empty tree.
 * @pre t!=nullptr
 */
template <class T>
int compute_height(const BTree<T> &t);

/**
 * @brief Compute the number of nodes in the tree.
 *
 * @param t is the tree.
 * @return the number of nodes in the tree.
 * @pre t!=nullptr
 */
template <class T>
size_t compute_size(const BTree<T> &t);

/**
 * @brief Prefix processing of a binary tree
 * The template class Processor must have an closure interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, typename Processor>
bool prefix_process(const BTree<T> &tree, Processor &p);

/**
 * @brief Infix processing of a binary tree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool infix_process(const BTree<T> &tree, Processor &p);

/**
 * @brief Postfix processing of a binary tree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool postfix_process(const BTree<T> &tree, Processor &p);

/**
 * @brief Bread-first processing of a btree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool breadth_first_process(const BTree<T> &tree, Processor &p);

/**
 * @brief Output the items of a binary tree following a pre-fix order.
 * @param[in,out] out is the stream used to output data.
 * @param[in] tree is the binary tree to print.
 * @return the stream.
 */
template <class T>
std::ostream &print_prefix(std::ostream &out, const BTree<T> &tree);

/**
 * @brief Output the items of a binary tree following a in-fix order.
 * @param[in,out] out is the stream used to output data.
 * @param[in] tree is the binary tree to print.
 * @return the stream.
 */
template <class T>
std::ostream &print_infix(std::ostream &out, const BTree<T> &tree);

/**
 * @brief Output the items of a binary tree following a post-fix order.
 * @param[in,out] out is the stream used to output data.
 * @param[in] tree is the binary tree to print.
 * @return the stream.
 */
template <class T>
std::ostream &print_postfix(std::ostream &out, const BTree<T> &tree);

/**
 * @brief Output the items of a binary tree following a breadth first order.
 * @param[in,out] out is the stream used to output data.
 * @param[in] tree is the binary tree to print.
 * @return the stream.
 */
template <class T>
std::ostream &print_breadth_first(std::ostream &out,
                                  const BTree<T> &tree);

/**
 * @brief Search a item value in a binary tree following a pre-fix order.
 * @param[in] tree is the binary tree.
 * @param[in] it is the item's value to look for.
 * @param[out] count is the number of processed nodes.
 * @return True if the item was found.
 */
template <class T>
bool search_prefix(const BTree<T> &tree, const T &it, size_t &count);

/**
 * @brief Search a item value in a binary tree following a in-fix order.
 * @param[in] tree is the binary tree.
 * @param[in] it is the item's value to look for.
 * @param[out] count is the number of processed nodes.
 * @return True if the item was found.
 */
template <class T>
bool search_infix(const BTree<T> &tree, const T &it, size_t &count);

/**
 * @brief Search a item value in a binary tree following a post-fix order.
 * @param[in] tree is the binary tree.
 * @param[in] it is the item's value to look for.
 * @param[out] count is the number of processed nodes.
 * @return True if the item was found.
 */
template <class T>
bool search_postfix(const BTree<T> &tree, const T &it, size_t &count);

/**
 * @brief Search a item value in a binary tree following a breadth-first order.
 * @param[in] tree is the binary tree.
 * @param[in] it is the item's value to look for.
 * @param[out] count is the number of processed nodes.
 * @return True if the item was found.
 */
template <class T>
bool search_breadth_first(const BTree<T> &tree, const T &it, size_t &count);

/**
 * @brief Check is a binary tree is in order.
 * A binary tree is in order whether it is the empty tree or
 * when for each subtree, the root node is greater than all its proper left
 * descendants and less than all its proper right descendants.
 *
 * @param tree is the tree to be checked.
 * @return true if the input tree is in order.
 */
template <class T>
bool check_btree_in_order(const BTree<T> &tree);

/**
 * @brief Search a item into the tree.
 *
 * The input tree must be in order, a optimized search process can be used.
 *
 * @param tree is a in order binary tree.
 * @param v is the value to be found.
 * @pre check_btree_in_order(tree)
 * @return true if the value is in the tree.
 */
template <class T>
bool has_in_order(const BTree<T> &tree, T const &v);

/**
 * @brief Insert in order a value intro a binary tree.
 * @see check_btree_in_order to know what is mean this.
 * If the value is already in tree, nothing is inserted.
 *
 * @param tree is the tree where inserting.
 * @param v is the value to be inserted.
 *
 * @pre check_btree_in_order(tree)
 * @post has_in_order(tree, v)
 */
template <class T>
void insert_in_order(BTree<T> &&tree, T const &v);

#include "btree_utils_imp.hpp"