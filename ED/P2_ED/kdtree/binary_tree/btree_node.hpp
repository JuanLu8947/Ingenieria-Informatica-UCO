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

/** @brief a BTree's Node.*/
template <class T>
class BTNode
{
public:
    /** @brief Define a shared reference to a BTNode.
     *
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     *
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    using Ref = std::shared_ptr<BTNode<T>>;

    /** @name Life cycle.*/
    /** @{*/

    /**
     * @brief Create a BTNode using dynamic memory.
     * @param it the value save in the node.
     * @param left links to the left child.
     * @param right links to the right child.
     * @return a shared reference to the new node.
     */
    static Ref create(T const &it, const Ref &left = nullptr, const Ref &right = nullptr);

    /** @brief Destroy a BTNode. **/
    ~BTNode()
    {
    }

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T &item() const;

    /** @brief get the left child.*/
    Ref left() const;

    /** @brief get the right child.*/
    Ref right() const;
    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.
     *  @post item()==new_it
     */
    void set_item(const T &new_it);

    /** @brief Set the left child.*/
    void set_left(const Ref &new_child);

    /** @brief Set the right child. */
    void set_right(const Ref &new_child);

    /** }*/
protected:
    /**
     * @brief Create a BTNode.
     * @param it the value save in the node.
     * @param l links to the left child.
     * @param r links to the right child.
     * @post item()==it
     * @post left()==l
     * @post right()==r
     */
    BTNode(T const &it = T(), const Ref &l = nullptr, const Ref &r = nullptr);

    // TODO
    // Specify a representation.
    // Hint: use Ref typename for the link to child nodes.
    T item_;
    Ref left_;
    Ref right_;
    //similar repr as node
    //BinaryTree[T] -> BTNode[T]
    //
};

#include <btree_node_imp.hpp>