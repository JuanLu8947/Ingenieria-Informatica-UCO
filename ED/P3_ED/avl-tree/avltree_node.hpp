/**
 * @file avltree_node.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <memory>

/**
 * @brief a AVLTree's Node.
 * Models a node of AVLTree.
 * @invariant height = 1 + max{ left's height, right's height }
 */
template <class T>
class AVLTNode
{
public:
    /** @brief Define a shared reference to a AVLTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    using Ref = std::shared_ptr<AVLTNode<T>>;

    /** @name Life cicle.*/
    /** @{*/

    /**
     * @brief Create a AVLTNode as a leaf node.
     * @param it is the node's item value.
     * @return a shared reference to node created.
     * @post left()==nullptr
     * @post height()==nullptr
     * @post parent()==nullptr
     */
    static typename AVLTNode<T>::Ref create(T const &it);

    /** @brief Destroy a AVLTNode. **/
    ~AVLTNode()
    {
    }

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T &item() const;

    /**
     * @brief Get the node's height.
     * @post time analysis: O(1).
     */
    int height() const;

    /**
     * @brief Get the balance factor of the node.
     * @post time analysis: O(1).
     */
    int balance_factor() const;

    /** @brief get the left child.
     * @post ret_v == child(0)
     */
    AVLTNode<T>::Ref const &left() const;

    /** @brief get the left child.
     * @post ret_v == child(0)
     */
    AVLTNode<T>::Ref &left();

    /** @brief get the right child.
     * @post ret_v == child(1)
     */
    AVLTNode<T>::Ref const &right() const;

    /** @brief get the right child.
     * @post ret_v == child(1)
     */
    AVLTNode<T>::Ref &right();

    /** @brief Get a child.
     * @param dir is the direction 0: left, 1:right.
     * @pre dir==0 || dir==1
     */
    AVLTNode<T>::Ref const &child(int dir) const;

    /** @brief Get a child.
     * @param dir is the direction 0: left, 1:right.
     * @pre dir==0 || dir==1
     */
    AVLTNode<T>::Ref &child(int dir);

    /** @brief get the parent.*/
    AVLTNode<T>::Ref const &parent() const;

    /** @brief get the parent.*/
    AVLTNode<T>::Ref &parent();

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /**
     * @brief Set the data item.
     * @post item() == new_it
     */
    void set_item(const T &new_it);

    /**
     * @brief Set the parent.
     * @post parent()==new_parent
     */
    void set_parent(Ref new_parent);

    /** @brief set a child.
     * @param dir is the direction 0: left, 1:right.
     * @pre dir==0 || dir==1
     * @post dir==0 || right()==new_child
     * @post dir==1 || left()==new_child
     * @post !new_child || new_child->parent()==This()
     */
    void set_child(int dir, AVLTNode<T>::Ref new_child);

    /**
     * @brief Set the left child.
     * @post left()==new_child
     * @post !new_child || new_child->parent()==This()
     */
    void set_left(AVLTNode<T>::Ref new_child);

    /**
     * @brief Set the right child.
     * @post right()==new_child
     * @post !new_child || new_child->parent()==This()
     */
    void set_right(Ref new_child);

    /**
     * @brief Update node's height.
     * @post Time analysis: O(1)
     */
    void update_height();

protected:
    /**
     * @brief Create a AVLTNode as a leaf node.
     * @param it is the node's item value.
     * @return a shared reference to node created.
     * @post parent()==nullptr
     * @post left()==nullptr
     * @post height()==nullptr
     */
    AVLTNode(T const &it);

    /**
     * @brief Check the AVLTNode invariant.
     * @return true if height() == 1 + max{ left's height, right's height }
     */
    bool check_height_invariant() const;

    AVLTNode<T>::Ref This_;        // A reference to this node.
    AVLTNode<T>::Ref This() const; // Get a reference to this node.

    // TODO
    // Give a representation.
    // Remember: to implement the AVLTNode for a BSTree we only need two links to the children and no height or balance factor support.
    // Remember: to implement the AVLTNode for a AVLTree add a link to the parent node and height and balance factor O(1) support.
    T item_;
    int height_;
    Ref parent_;
    Ref left_;
    Ref right_;
    //
};

#include <avltree_node_imp.hpp>
