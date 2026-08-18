/**
 * @file avltree_iterator.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <avltree_node.hpp>

template <class T>
class AVLTree; // Forward declaration

/**
 * @brief An iterator for a AVLTree.
 *
 * @tparam T
 */
template <class T>
class AVLTreeIterator
{

public:
    /** @name Life cicle.*/
    /** @{*/

    /**
     * @brief Construct a new AVLTreeIterator object
     *
     */
    AVLTreeIterator();

    /** @} */

    /** @name Observers*/

    /** @{*/

    /**
     * @brief Equalilty operator.
     *
     * @param other is a AVLTreeIterator to be compared.
     * @return true if this iterator is equal to other (pointing to the same node).
     */
    bool operator==(AVLTreeIterator<T> const &other) const;

    /**
     * @brief Inequality operator.
     *
     * @param other is a AVLTreeIterator to be compared.
     * @return true if this iterator is different to other (pointing to different nodes).
     */
    bool operator!=(AVLTreeIterator<T> const &other) const;

    /**
     * @brief Dereference operator.
     *
     * @return the item stored in the node pointed by this iterator.
     */
    T const &operator*() const;

    /**
     * @brief Dereference operator.
     *
     * @return the item stored in the node pointed by this iterator.
     */
    const T *operator->() const;

    /**
     * @brief Increment operator.
     *
     * @return AVLTreeIterator<T>&
     */
    AVLTreeIterator<T> &operator++();

    /**
     * @brief Increment operator (postfix).
     *
     * @return AVLTreeIterator<T>
     */
    AVLTreeIterator<T> operator++(int);

    /**
     * @brief Decrement operator.
     *
     * @return AVLTreeIterator<T>&
     */
    AVLTreeIterator<T> &operator--();

    /**
     * @brief Decrement operator (postfix).
     *
     * @return AVLTreeIterator<T>
     */
    AVLTreeIterator<T> operator--(int);

protected:
    // Allow AVLTree to create interators to traverse the tree.
    friend class AVLTree<T>;

    /**
     * @brief Get the node object pointed by this iterator.
     *
     * @return const AVLTNode<T>::Ref&
     */
    const typename AVLTNode<T>::Ref &node() const;

    /**
     * @brief Get the node object pointed by this iterator.
     *
     * @return AVLTNode<T>::Ref&
     */
    typename AVLTNode<T>::Ref &node();

    /**
     * @brief Construct a new AVLTreeIterator object
     *
     * @param node is the node to be pointed by this iterator.
     */
    AVLTreeIterator(const typename AVLTNode<T>::Ref &node);

    // TODO
    // Give a representation.
    typename AVLTNode<T>::Ref current_node_;
    //
};

#include <avltree_iterator_imp.hpp>
